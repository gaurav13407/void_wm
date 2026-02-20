#include "output.hpp"
#include "server.hpp"
#include "wlr_wrapper.h"
#include <iostream>
#include <time.h>


Output::Output(Server *server, void *wlr_output) {
    this->server     = server;
    this->wlr_output = wlr_output;

    std::cout << "Output: new monitor connected\n";

    // Tell wlroots to use our renderer for this output
    wm_output_init_render(wlr_output, server->allocator, server->renderer);

    // Enable the output and set preferred resolution
    wm_output_set_mode(wlr_output);
    wm_output_enable(wlr_output);
    wm_output_commit(wlr_output);

    // Add to output layout so wlroots knows screen arrangement
    wm_output_layout_add_auto(server->output_layout, wlr_output);

    // Create scene output - connects scene graph to this monitor
    wm_scene_output_create(server->scene, wlr_output);

    std::cout << "Output: monitor initialized\n";
}
void Output::on_frame() {
    // Get the scene output for this monitor
    void *scene_output = wm_scene_get_scene_output(
        server->scene, wlr_output);

    if (!scene_output) {
        return;
    }

    // This is the key call - renders entire scene to GPU
    // background + windows + cursor all drawn here
    wm_scene_output_commit(scene_output);

    // Tell clients the frame is done
    // Apps use this to sync their animations
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    wm_scene_output_send_frame_done(scene_output, &now);
}
void Output::on_request_state(void *event) {
    // Monitor requested a state change
    // like resolution or refresh rate change
    wm_output_commit_state(wlr_output, event);
}

void Output::on_destroy() {
    std::cout << "Output: monitor disconnected\n";

    // Remove listeners
    wl_list_remove(&frame.link);
    wl_list_remove(&request_state.link);
    wl_list_remove(&destroy.link);

    delete this;
}
static void handle_frame(struct wl_listener *listener, void *data) {
    Output *output = wl_container_of(listener, output, frame);
    output->on_frame();
}

static void handle_request_state(struct wl_listener *listener, void *data) {
    Output *output = wl_container_of(listener, output, request_state);
    output->on_request_state(data);
}

static void handle_destroy(struct wl_listener *listener, void *data) {
    Output *output = wl_container_of(listener, output, destroy);
    output->on_destroy();
}
