#include "server.hpp"
#include <iostream>

bool Server::init() {
    display = wm_display_create();
    if (!display) {
        std::cerr << "Failed to create display\n";
        return false;
    }

    backend = wm_backend_create(display);
    if (!backend) {
        std::cerr << "Failed to create backend\n";
        return false;
    }

    renderer = wm_renderer_create(backend);
    if (!renderer) {
        std::cerr << "Failed to create renderer\n";
        return false;
    }
    wm_renderer_init_display(renderer, display);

    allocator = wm_allocator_create(backend, renderer);
    if (!allocator) {
        std::cerr << "Failed to create allocator\n";
        return false;
    }

    wm_init_compositor(display, renderer);

    output_layout = wm_output_layout_create(display);
    scene         = wm_scene_create();
    seat          = wm_seat_create(display);
    cursor        = wm_cursor_create();
    cursor_mgr    = wm_cursor_mgr_create();

    std::cout << "Server initialized successfully\n";
    return true;
}

void Server::run() {
    const char *socket = wm_display_add_socket(display);
    if (!socket) {
        std::cerr << "Failed to create socket\n";
        return;
    }

    if (!wm_backend_start(backend)) {
        std::cerr << "Failed to start backend\n";
        return;
    }

    setenv("WAYLAND_DISPLAY", socket, true);
    std::cout << "void_wm running on WAYLAND_DISPLAY=" << socket << "\n";
    wm_display_run(display);
}

void Server::cleanup() {
    wm_display_destroy(display);
    std::cout << "Server cleaned up\n";
}
