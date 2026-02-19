PKG_CONFIG?=pkg-config

PKGS="wlroots-0.20" wayland-server xkbcommon
CFLAGS_PKG_CONFIG!=$(PKG_CONFIG) --cflags $(PKGS)
CFLAGS+=$(CFLAGS_PKG_CONFIG)
LIBS!=$(PKG_CONFIG) --libs $(PKGS)

all: void_wm

void_wm.o: void_wm.c
	$(CC) -c $< -g -Werror $(CFLAGS) -I. -DWLR_USE_UNSTABLE -o $@
void_wm: void_wm.o
	$(CC) $^ -g -Werror $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -f void_wm void_wm.o

.PHONY: all clean
