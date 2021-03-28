C++      := clang++
C++FLAGS := -std=c++2a

all: build-main

build-main: build-directory build/main

build-directory:
	mkdir -p build

clean:
	rm -f build/main

build/main: main.cxx
	$(C++) -o "$@" $< $(C++FLAGS)
