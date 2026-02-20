#include "server.hpp"
#include "renderer/renderer.hpp"
#include "renderer/background.hpp"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    std::cout << "void_wm starting...\n\n";

    // Parse arguments
    // -s "command" launches an app when compositor starts
    char *startup_cmd = nullptr;
    int c;
    while ((c = getopt(argc, argv, "s:h")) != -1) {
        switch (c) {
            case 's':
                startup_cmd = optarg;
                break;
            case 'h':
            default:
                std::cout << "Usage: void_wm [-s startup_command]\n";
                return 0;
        }
    }

    // Detect GPU
    RendererInfo info = Renderer::detect();
    std::cout << "GPU      : " << info.gpu_name << "\n";
    std::cout << "Backend  : " << Renderer::backend_name(info.backend) << "\n\n";

    // Load background
    Background bg(info.backend);
    bg.load("src/assests/background/default.jpeg");

    // Start compositor
    Server server;
    if (!server.init()) {
        std::cerr << "Failed to init server\n";
        return 1;
    }

    // Launch startup app if provided
    if (startup_cmd) {
        std::cout << "Launching: " << startup_cmd << "\n";
        if (fork() == 0) {
            execl("/bin/sh", "/bin/sh", "-c", startup_cmd, (void*)nullptr);
        }
    }

    server.run();
    server.cleanup();
    return 0;
}
