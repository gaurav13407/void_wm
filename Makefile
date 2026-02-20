CXX      = g++
CC       = gcc
CXXFLAGS = -std=gnu++17 -Wall -g
CXXFLAGS += -I/usr/local/include/wlroots-0.20
CXXFLAGS += -I/usr/local/include
CXXFLAGS += -I/usr/local/include/libdrm
CXXFLAGS += -I/usr/local/include/pixman-1

CFLAGS   = -Wall -g -DWLR_USE_UNSTABLE
CFLAGS  += -I/usr/local/include/wlroots-0.20
CFLAGS  += -I/usr/local/include
CFLAGS  += -I/usr/local/include/libdrm
CFLAGS  += -I/usr/local/include/pixman-1

LDFLAGS  = -L/usr/local/lib/x86_64-linux-gnu
LDFLAGS += -lwlroots-0.20
LDFLAGS += -lwayland-server
LDFLAGS += -lxkbcommon
LDFLAGS += -lm

CPPSRC = src/main.cpp \
         src/server.cpp \
         src/renderer/renderer.cpp \
         src/renderer/background.cpp

CSRC   = src/wlr_wrapper.c

OUT = void_wm

all:
	$(CC)  $(CFLAGS)   -c $(CSRC)   -o src/wlr_wrapper.o
	$(CXX) $(CXXFLAGS) $(CPPSRC) src/wlr_wrapper.o $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT) src/wlr_wrapper.o
