#include "renderer.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>


//Check if a File Exists on the System 

static bool file_exists(const std::string &path){
    return std::filesystem::exists(path);
}
//Linux exposes GPU info in /sys/class/drm 
//We need vendor ID to known what GPU brand it is 
static std::string detect_gpu_name(){
    std::string drm_path="/sys/class/drm";

    if(!file_exists(drm_path)){
        return "Unknown GPU";
    }

    for (const auto &entry: std::filesystem::directory_iterator(drm_path)){
        std::string vendor_path=entry.path().string() + "/device/vendor"; 

        if(file_exists(vendor_path)){
            std::ifstream f(vendor_path);
            std::string vendor;
            f >> vendor; 

            // These are PCI vendor IDs for GPU makers  
            if (vendor == "0x10de") return "NVIDIA GPU";
            if(vendor == "0x1002") return "AMD GPU";
            if(vendor == "0x8086") return "Intel GPU";
        }
    }
    return "Unknown GPU";
}

// Vulkan driver install ICD files here 
static bool detect_vulkan(){
    return file_exists("/usr/share/vulkan/icd.d") || 
    file_exists("/etc/vulkan/icd.d");
}

// GLES2 needs libEGL to be present 
static bool detect_gles2(){
    return file_exists("/usr/lib/x86_64-linux-gnu/libEGL.so") || 
        file_exists("/usr/local/lib/libEGL.so") || 
        file_exists("/usr/lib/libEGL.so");
}

// Main detection function- puts it all together 
RendererInfo Renderer::detect(){
    RendererInfo info; 

    info.gpu_name = detect_gpu_name();
    info.has_gpu =(info.gpu_name!="Unknown GPU");
    info.has_vulkan=detect_vulkan();
    info.has_gles2=detect_gles2(); 

    //Pick the best backend avaailable 
    if(info.has_gpu && info.has_vulkan){
        info.backend= RenderBackend::VULKAN;
    }else if (info.has_gpu && info.has_gles2) {
        info.backend=RenderBackend::GLES2;
    } else{
        // No Gpu Found - fall back to CPU rendering 
        info.backend=RenderBackend::PIXMAN;
    }
    return info;
}

// Just convert the enum to redable string 
std::string Renderer::backend_name(RenderBackend b){
    switch (b) {
        case RenderBackend::VULKAN: return "Vulkan (GPU)";
        case RenderBackend::GLES2: return "OpenGL ES 2(GPU)";
        case RenderBackend::PIXMAN: return "Pixman (CPU fallback)";
        default:                    return "Unknown";
    }
}
