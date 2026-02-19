#pragma once 
#include <string>
enum class RenderBackend{
    GLES2,
    VULKAN,
    PIXMAN
};

// This hold info about what the system has 
 
struct RendererInfo{
    RenderBackend backend;
    std::string gpu_name;
    bool has_gpu;
    bool has_vulkan;
    bool has_gles2;
};

class Renderer{
    public:
        static RendererInfo detect();
        static std::string backend_name(RenderBackend b);
};
