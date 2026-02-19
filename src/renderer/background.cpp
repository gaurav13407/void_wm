#include "background.hpp"
#include <iostream>
#include <fstream>

Background::Background(RenderBackend backend) {
    this->backend  = backend;
    this->loaded   = false;
    this->pixels   = nullptr;
    this->width    = 0;
    this->height   = 0;
    this->channels = 0;
    this->color_r  = 0.05f;
    this->color_g  = 0.05f;
    this->color_b  = 0.10f;
}

bool Background::load(const std::string &path) {
    std::ifstream f(path);
    if (!f.good()) {
        std::cerr << "Background: file not found: " << path << "\n";
        return false;
    }
    f.close();

    std::cout << "Background: loading image: " << path << "\n";
    std::cout << "Background: using backend: ";

    switch (backend) {
        case RenderBackend::VULKAN:
            std::cout << "Vulkan (GPU)\n";
            break;
        case RenderBackend::GLES2:
            std::cout << "OpenGL ES 2 (GPU)\n";
            break;
        case RenderBackend::PIXMAN:
            std::cout << "Pixman (CPU)\n";
            break;
    }

    loaded = true;
    return true;
}

void Background::set_color(float r, float g, float b) {
    this->color_r = r;
    this->color_g = g;
    this->color_b = b;
    std::cout << "Background: solid color set ("
              << r << ", " << g << ", " << b << ")\n";
}

bool Background::is_loaded() const {
    return loaded;
}
