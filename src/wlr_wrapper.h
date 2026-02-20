#pragma once

/* This is a pure C header - safe to include from both C and C++ */
/* It hides all wlroots types behind void pointers for C++ */
#include <wayland-server-core.h>
#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif

/* Opaque pointers - C++ sees void* not wlroots types */
typedef void VoidWM_Display;
typedef void VoidWM_Backend;
typedef void VoidWM_Renderer;
typedef void VoidWM_Allocator;
typedef void VoidWM_Scene;
typedef void VoidWM_OutputLayout;
typedef void VoidWM_XdgShell;
typedef void VoidWM_Cursor;
typedef void VoidWM_Seat;
typedef void VoidWM_CursorMgr;
typedef void VoidWM_SceneLayout;

/* Server functions callable from C++ */
VoidWM_Display*      wm_display_create(void);
VoidWM_Backend*      wm_backend_create(VoidWM_Display *display);
VoidWM_Renderer*     wm_renderer_create(VoidWM_Backend *backend);
VoidWM_Allocator*    wm_allocator_create(VoidWM_Backend *b, VoidWM_Renderer *r);
VoidWM_Scene*        wm_scene_create(void);
VoidWM_OutputLayout* wm_output_layout_create(VoidWM_Display *display);
VoidWM_Seat*         wm_seat_create(VoidWM_Display *display);
VoidWM_Cursor*       wm_cursor_create(void);
VoidWM_CursorMgr*    wm_cursor_mgr_create(void);

void wm_init_compositor(VoidWM_Display *display, VoidWM_Renderer *renderer);
void wm_renderer_init_display(VoidWM_Renderer *r, VoidWM_Display *d);
int  wm_backend_start(VoidWM_Backend *backend);
void wm_display_run(VoidWM_Display *display);
void wm_display_destroy(VoidWM_Display *display);
const char* wm_display_add_socket(VoidWM_Display *display);


void  wm_output_init_render(void *output, void *allocator, void *renderer);
void  wm_output_set_mode(void *output);
void  wm_output_enable(void *output);
void  wm_output_commit(void *output);
void  wm_output_commit_state(void *output, void *event);
void  wm_output_layout_add_auto(void *layout, void *output);
void* wm_scene_output_create(void *scene, void *output);
void* wm_scene_get_scene_output(void *scene, void *output);
void  wm_scene_output_commit(void *scene_output);
void  wm_scene_output_send_frame_done(void *scene_output, struct timespec *now);

void wm_signal_add_new_output(void *backend, struct wl_listener *listener);
void wm_signal_add_frame(void *output, struct wl_listener *listener);
void wm_signal_add_request_state(void *output, struct wl_listener *listener);
#ifdef __cplusplus
}
#endif
