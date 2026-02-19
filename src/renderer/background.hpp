#pragma once
#include <string>
#include "renderer.hpp"

class Background {
public:
    Background(RenderBackend backend);

    bool load(const std::string &path);
    void set_color(float r, float g, float b);
    bool is_loaded() const;

private:
    RenderBackend backend;
    bool loaded;

    unsigned char *pixels;
    int width;
    int height;
    int channels;

    float color_r;
    float color_g;
    float color_b;
};
