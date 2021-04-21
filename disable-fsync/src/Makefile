VERSION=0.2
SOURCES=configure  Makefile  disable-fsync  disable-fsync.c

all: disable-fsync.so

disable-fsync.so: disable-fsync.c
	clang -Wall -fPIC -shared -o disable-fsync.so disable-fsync.c -lc -ldl

install:
	install -m 0755 disable-fsync /usr/bin
	install -m 0644 disable-fsync.so /usr/lib

dist:
	mkdir disable-fsync-$(VERSION)
	cp $(SOURCES) disable-fsync-$(VERSION)
	tar -czf disable-fsync-$(VERSION).tar.gz disable-fsync-$(VERSION)
	rm -r disable-fsync-$(VERSION)
