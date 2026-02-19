# void_wm

A custom Wayland compositor built from scratch using wlroots 0.20.
Built on Ubuntu 24.04 as a foundation for a Hyprland-like compositor.

## Dependencies built from source
- wayland 1.24.0
- libdrm 2.4.129
- pixman 0.46.0
- wayland-protocols 1.47
- wlroots 0.20.0

## Build
```bash
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:/usr/local/lib/x86_64-linux-gnu/pkgconfig:$PKG_CONFIG_PATH
make
```

## Run
```bash
./void_wm -s alacritty
```

## Controls
- Alt + Left Click drag = move windows
- Alt + Right Click drag = resize windows
- Alt + Escape = quit
# void_wm
