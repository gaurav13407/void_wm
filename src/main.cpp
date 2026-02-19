#include "renderer/renderer.hpp"
#include "renderer/background.hpp"
#include <iostream>

int main() {
    std::cout << "Testing renderer detection...\n\n";

    RendererInfo info = Renderer::detect();

    std::cout << "GPU Name     : " << info.gpu_name << "\n";
    std::cout << "Has GPU      : " << (info.has_gpu ? "yes" : "no") << "\n";
    std::cout << "Has Vulkan   : " << (info.has_vulkan ? "yes" : "no") << "\n";
    std::cout << "Has GLES2    : " << (info.has_gles2 ? "yes" : "no") << "\n";
    std::cout << "Best Backend : " 
              << Renderer::backend_name(info.backend) << "\n\n";

    // Test background
    std::cout << "Testing background...\n\n";
    Background bg(info.backend);

    // Test solid color
    bg.set_color(0.05f, 0.05f, 0.10f);

    // Test loading a fake path to see error handling
    bg.load("/tmp/test.jpg");

    // Test loading nothing - check fallback
    std::cout << "Image loaded : " 
              << (bg.is_loaded() ? "yes" : "no") << "\n";

    return 0;
}
