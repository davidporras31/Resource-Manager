all: config test

config:
	mkdir -p bin
	mkdir -p obj

resource-manager:
	g++ -std=c++17 -o obj/resource-manager.o -c ResourceManager.cpp
resource-loader:
	g++ -std=c++17 -o obj/resource-loader.o -c ResourceLoader.cpp
	
clean:
	rm -rf bin/*
	rm -rf obj/*
	rmdir bin
	rmdir obj

test: resource-manager resource-loader test-loader
	g++ -std=c++17 -o bin/resource-manager.exe test/main.cpp obj/resource-loader.o obj/test-loader.o obj/resource-manager.o
test-loader:
	g++ -std=c++17 -o obj/test-loader.o -c test/TestLoader.cpp