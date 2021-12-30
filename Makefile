
debug:
	mkdir -p build/debug
	cd build/debug && cmake ../.. && $(MAKE)

clean:
	rm -rf build
