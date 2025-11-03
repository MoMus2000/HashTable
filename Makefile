.PHONY: all run clean
all:
	mkdir -p build
	gcc -o build/server server.c

run:
	./build/server

clean:
	rm -f ./build/server

