all: release

debug:
	cmake -S . -B build/Debug -D CMAKE_BUILD_TYPE=Debug
	cmake --build build/Debug

release:
	cmake -S . -B build/Release -D CMAKE_BUILD_TYPE=Release
	cmake --build build/Release

test: release
	./build/Release/test/nonsense_tests

clean:
	rm -rf build
