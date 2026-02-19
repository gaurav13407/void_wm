#!/bin/bash
# void_wm dependency installer
# Supports: Ubuntu/Debian, Arch, Fedora, openSUSE

set -e

# Detect package manager
if command -v pacman &> /dev/null; then
    DISTRO="arch"
elif command -v apt &> /dev/null; then
    DISTRO="debian"
elif command -v dnf &> /dev/null; then
    DISTRO="fedora"
elif command -v zypper &> /dev/null; then
    DISTRO="opensuse"
else
    echo "Unsupported distro. Please install dependencies manually."
    echo "See README.md for the full list."
    exit 1
fi

echo "Detected: $DISTRO"
echo "Installing void_wm dependencies..."

case $DISTRO in
    arch)
        sudo pacman -S --needed \
            base-devel \
            meson \
            ninja \
            pkg-config \
            wlroots \
            wayland \
            wayland-protocols \
            libxkbcommon \
            libinput \
            seatd \
            pixman \
            libdrm \
            mesa \
            vulkan-icd-loader \
            glslang
        echo "All dependencies installed! You can build now."
        ;;

    debian)
        sudo apt install -y \
            build-essential \
            meson \
            ninja-build \
            pkg-config \
            libxkbcommon-dev \
            libpixman-1-dev \
            libdrm-dev \
            libgbm-dev \
            libinput-dev \
            libseat-dev \
            libffi-dev \
            libexpat1-dev \
            libegl-dev \
            libgles-dev \
            libvulkan-dev \
            glslang-tools \
            libxcb-dri3-dev \
            libxcb-present-dev \
            libxcb-composite0-dev \
            libxcb-render-util0-dev \
            libxcb-ewmh-dev \
            libxcb-icccm4-dev \
            libxcb-res0-dev \
            libx11-xcb-dev \
            libxfixes-dev \
            wayland-protocols

        echo ""
        echo "WARNING: Ubuntu/Debian ships old packages."
        echo "You must build these from source in this order:"
        echo "  1. wayland >= 1.24.0"
        echo "  2. libdrm >= 2.4.129"
        echo "  3. pixman >= 0.46.0"
        echo "  4. wayland-protocols >= 1.47"
        echo "  5. wlroots 0.20"
        echo ""
        echo "After building, add this to your ~/.bashrc or ~/.zshrc:"
        echo 'export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:/usr/local/lib/x86_64-linux-gnu/pkgconfig:$PKG_CONFIG_PATH'
        ;;

    fedora)
        sudo dnf install -y \
            @development-tools \
            meson \
            ninja-build \
            pkg-config \
            wlroots-devel \
            wayland-devel \
            wayland-protocols-devel \
            libxkbcommon-devel \
            libinput-devel \
            libseat-devel \
            pixman-devel \
            libdrm-devel \
            mesa-libEGL-devel \
            mesa-libGLES-devel \
            vulkan-loader-devel \
            glslang
        echo "All dependencies installed! You can build now."
        ;;

    opensuse)
        sudo zypper install -y \
            meson \
            ninja \
            pkg-config \
            wlroots-devel \
            wayland-devel \
            wayland-protocols-devel \
            libxkbcommon-devel \
            libinput-devel \
            pixman-devel \
            libdrm-devel \
            Mesa-libEGL-devel \
            vulkan-devel \
            glslang
        echo "All dependencies installed! You can build now."
        ;;
esac

echo ""
echo "Now build void_wm:"
echo "  make"
echo "  ./void_wm -s alacritty"
