# void_wm

> A fast, minimal Wayland compositor built from scratch using wlroots.
> Built for power users who want full control over their desktop.

## Dependencies

### Build tools
- meson
- ninja
- pkg-config
- gcc

### Libraries
- wayland >= 1.24.0
- wayland-protocols >= 1.47
- wlroots = 0.20
- libdrm >= 2.4.129
- pixman >= 0.46.0
- libxkbcommon
- libinput
- libseat
- EGL / OpenGL ES 2

## Installation

### Ubuntu 24.04
Ubuntu's packages are too old so dependencies must be built from source.
Run the helper script first:
```bash
./install-deps.sh
```
Then follow the printed instructions to build each dependency from source in order.

### Arch Linux (easiest)
```bash
sudo pacman -S wlroots wayland wayland-protocols libxkbcommon libinput
```

### Fedora
```bash
sudo dnf install wlroots-devel wayland-devel wayland-protocols-devel libxkbcommon-devel
```

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
- Alt + F1 = cycle windows
- Alt + Escape = quit

## Roadmap
- [ ] Super+Q to close window
- [ ] Super+Enter to open terminal
- [ ] Window borders with custom colors
- [ ] Tiling layout
- [ ] Gaps between windows
- [ ] Config file
- [ ] Workspaces
- [ ] Animations

## License
MIT
