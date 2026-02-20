#pragma once
#include "wlr_wrapper.h"
#include "output.hpp"
#include <string>
#include <wayland-server-core.h>

class Server {
public:
    bool init();
    void run();
    void cleanup();

    VoidWM_Display      *display;
    VoidWM_Backend      *backend;
    VoidWM_Renderer     *renderer;
    VoidWM_Allocator    *allocator;
    VoidWM_Scene        *scene;
    VoidWM_OutputLayout *output_layout;
    VoidWM_Seat         *seat;
    VoidWM_Cursor       *cursor;
    VoidWM_CursorMgr    *cursor_mgr;
    struct wl_listener new_output;
private:
    static void on_new_output(struct wl_listener *listener ,void*data);
};
