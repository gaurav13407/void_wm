#include "server.hpp"
#include "renderer/renderer.hpp"
#include "renderer/background.hpp"
#include <iostream>

int main() {
    std::cout << "void_wm starting...\n\n";

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

    server.run();
    server.cleanup();
    return 0;
}
