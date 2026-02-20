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
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_scene.h>
#include <time.h>
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
void wm_output_init_render(void *output, void *allocator, void *renderer) {
    wlr_output_init_render(
        (struct wlr_output*)output,
        (struct wlr_allocator*)allocator,
        (struct wlr_renderer*)renderer);
}

void wm_output_set_mode(void *output) {
    struct wlr_output *o = (struct wlr_output*)output;
    struct wlr_output_mode *mode = wlr_output_preferred_mode(o);
    if (mode) {
        struct wlr_output_state state;
        wlr_output_state_init(&state);
        wlr_output_state_set_mode(&state, mode);
        wlr_output_state_set_enabled(&state, true);
        wlr_output_commit_state(o, &state);
        wlr_output_state_finish(&state);
    }
}

void wm_output_enable(void *output) {
    // mode setting handles enable now in wlroots 0.20
}

void wm_output_commit(void *output) {
    // handled in set_mode for wlroots 0.20
}

void wm_output_commit_state(void *output, void *event) {
    struct wlr_output_event_request_state *e =
        (struct wlr_output_event_request_state*)event;
    wlr_output_commit_state((struct wlr_output*)output, e->state);
}

void wm_output_layout_add_auto(void *layout, void *output) {
    wlr_output_layout_add_auto(
        (struct wlr_output_layout*)layout,
        (struct wlr_output*)output);
}

void* wm_scene_output_create(void *scene, void *output) {
    return (void*)wlr_scene_output_create(
        (struct wlr_scene*)scene,
        (struct wlr_output*)output);
}

void* wm_scene_get_scene_output(void *scene, void *output) {
    return (void*)wlr_scene_get_scene_output(
        (struct wlr_scene*)scene,
        (struct wlr_output*)output);
}

void wm_scene_output_commit(void *scene_output) {
    wlr_scene_output_commit(
        (struct wlr_scene_output*)scene_output, NULL);
}

void wm_scene_output_send_frame_done(void *scene_output, struct timespec *now) {
    wlr_scene_output_send_frame_done(
        (struct wlr_scene_output*)scene_output, now);
}
void wm_signal_add_new_output(void *backend, struct wl_listener *listener) {
    wl_signal_add(&((struct wlr_backend*)backend)->events.new_output, listener);
}

void wm_signal_add_frame(void *output, struct wl_listener *listener) {
    wl_signal_add(&((struct wlr_output*)output)->events.frame, listener);
}

void wm_signal_add_request_state(void *output, struct wl_listener *listener) {
    wl_signal_add(
        &((struct wlr_output*)output)->events.request_state, listener);
}
