
PREFIX?=$(DESTDIR)/usr
BINDIR?=$(PREFIX)/bin

debug:
	mkdir -p build/debug
	cd build/debug && cmake -DCMAKE_BUILD_TYPE=Debug ../.. && $(MAKE)

release:
	mkdir -p build/release
	cd build/release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && $(MAKE)

install: release
	sudo cp build/release/k810-led $(BINDIR)/

uninstall:
	sudo rm -f $(BINDIR)/k810-led
	
clean:
	rm -rf build
