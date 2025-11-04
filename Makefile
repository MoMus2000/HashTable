.PHONY: all run clean

.PHONY: all run clean

all:
	mkdir -p build
	gcc -o build/server server.c \
	    -I ./libuv/include \
	    -L ./libuv/.libs -luv

run:
	DYLD_LIBRARY_PATH=./libuv/.libs ./build/server

clean:
	rm -f ./build/*


node:
	gcc -o build/llist linked_list.c && ./build/llist

tree:
	gcc -o build/tree tree.c && ./build/tree

