#define STB_IMAGE_IMPLEMENTATION
#include "background.hpp"
#include <iostream>
#include <fstream>
#include "stb_image.h"
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

Background::~Background(){
    if(pixels !=nullptr){
        stbi_image_free(pixels);
        pixels=nullptr;
    }
}

bool Background::load(const std::string &path) {
    // Check file exists first
    std::ifstream f(path);
    if (!f.good()) {
        std::cerr << "Background: file not found: " << path << "\n";
        return false;
    }
    f.close();

    // Free any previously loaded image
    if (pixels != nullptr) {
        stbi_image_free(pixels);
        pixels = nullptr;
    }

    // Load image from disk into CPU memory
    // stbi_load returns raw RGBA pixel data
    pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);

    if (pixels == nullptr) {
        std::cerr << "Background: failed to decode image: " << path << "\n";
        std::cerr << "Reason: " << stbi_failure_reason() << "\n";
        return false;
    }

    loaded = true;

    // Print info so we can see it worked
    std::cout << "Background: image loaded successfully!\n";
    std::cout << "  Path     : " << path << "\n";
    std::cout << "  Width    : " << width << "px\n";
    std::cout << "  Height   : " << height << "px\n";
    std::cout << "  Channels : " << channels << "\n";
    std::cout << "  Backend  : " << "\n";

    switch (backend) {
        case RenderBackend::VULKAN:
            std::cout << "  Renderer : Vulkan (GPU)\n";
            break;
        case RenderBackend::GLES2:
            std::cout << "  Renderer : OpenGL ES 2 (GPU)\n";
            break;
        case RenderBackend::PIXMAN:
            std::cout << "  Renderer : Pixman (CPU)\n";
            break;
    }

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
