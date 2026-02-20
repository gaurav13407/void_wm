/* Pure C file - can include wlroots freely */
#include <wayland-server-core.h>
#include <wlr/backend.h>
#include <wlr/render/allocator.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_subcompositor.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_scene.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_seat.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_xcursor_manager.h>
#include <wlr/util/log.h>

#include "wlr_wrapper.h"

VoidWM_Display* wm_display_create(void) {
    return (VoidWM_Display*)wl_display_create();
}

VoidWM_Backend* wm_backend_create(VoidWM_Display *display) {
    struct wl_display *d = (struct wl_display*)display;
    return (VoidWM_Backend*)wlr_backend_autocreate(
        wl_display_get_event_loop(d), NULL);
}

VoidWM_Renderer* wm_renderer_create(VoidWM_Backend *backend) {
    return (VoidWM_Renderer*)wlr_renderer_autocreate(
        (struct wlr_backend*)backend);
}

VoidWM_Allocator* wm_allocator_create(VoidWM_Backend *b, VoidWM_Renderer *r) {
    return (VoidWM_Allocator*)wlr_allocator_autocreate(
        (struct wlr_backend*)b, (struct wlr_renderer*)r);
}

VoidWM_Scene* wm_scene_create(void) {
    return (VoidWM_Scene*)wlr_scene_create();
}

VoidWM_OutputLayout* wm_output_layout_create(VoidWM_Display *display) {
    return (VoidWM_OutputLayout*)wlr_output_layout_create(
        (struct wl_display*)display);
}

VoidWM_Seat* wm_seat_create(VoidWM_Display *display) {
    return (VoidWM_Seat*)wlr_seat_create(
        (struct wl_display*)display, "seat0");
}

VoidWM_Cursor* wm_cursor_create(void) {
    return (VoidWM_Cursor*)wlr_cursor_create();
}

VoidWM_CursorMgr* wm_cursor_mgr_create(void) {
    return (VoidWM_CursorMgr*)wlr_xcursor_manager_create(NULL, 24);
}

void wm_init_compositor(VoidWM_Display *display, VoidWM_Renderer *renderer) {
    wlr_compositor_create(
        (struct wl_display*)display, 5, (struct wlr_renderer*)renderer);
    wlr_subcompositor_create((struct wl_display*)display);
    wlr_data_device_manager_create((struct wl_display*)display);
}

void wm_renderer_init_display(VoidWM_Renderer *r, VoidWM_Display *d) {
    wlr_renderer_init_wl_display(
        (struct wlr_renderer*)r, (struct wl_display*)d);
}

int wm_backend_start(VoidWM_Backend *backend) {
    return wlr_backend_start((struct wlr_backend*)backend);
}

void wm_display_run(VoidWM_Display *display) {
    wl_display_run((struct wl_display*)display);
}

void wm_display_destroy(VoidWM_Display *display) {
    wl_display_destroy((struct wl_display*)display);
}

const char* wm_display_add_socket(VoidWM_Display *display) {
    return wl_display_add_socket_auto((struct wl_display*)display);
}
