#pragma once
#include "wlr_wrapper.h"

// Forward declaration
class Server;

class Output {
public:
    // Constructor takes the server and the raw wlroots output
    Output(Server *server, void *wlr_output);

    // Called every frame - renders everything to screen
    void on_frame();

    // Called when monitor requests a state change
    // like resolution change or window resize
    void on_request_state(void *event);

    // Called when monitor is disconnected
    void on_destroy();

    // The server that owns this output
    Server *server;

    // The actual wlroots output (monitor)
    void *wlr_output;

    // wlroots event listeners
    struct wl_listener frame;
    struct wl_listener request_state;
    struct wl_listener destroy;
};
