
COMPYLE_ARGS := -g -std=c++17 -Wall

all: config test

config:
	mkdir -p bin
	mkdir -p obj

resource-manager:
	g++ ${COMPYLE_ARGS}  -o obj/resource-manager.o -c ResourceManager.cpp
resource-loader:
	g++ ${COMPYLE_ARGS}  -o obj/resource-loader.o -c ResourceLoader.cpp
resource-handler:
	g++ ${COMPYLE_ARGS}  -o obj/resource-handler.o -c ResourceHandler.cpp
	
clean:
	rm -rf bin/*
	rm -rf obj/*
	rmdir bin
	rmdir obj

test: resource-manager resource-loader test-loader resource-handler
	g++ ${COMPYLE_ARGS}  -o bin/resource-manager.exe test/main.cpp obj/resource-loader.o obj/test-loader.o obj/resource-manager.o obj/resource-handler.o
test-loader:
	g++ ${COMPYLE_ARGS}  -o obj/test-loader.o -c test/TestLoader.cpp