
COMPYLE_ARGS := -Wall

all: bin/main.out

bin:
	mkdir bin
obj:
	mkdir obj

obj/resource-manager.o: ResourceManager.cpp ResourceManager.h obj
	g++ ${COMPYLE_ARGS}  -o obj/resource-manager.o -c ResourceManager.cpp
obj/resource-loader.o: ResourceLoader.cpp ResourceLoader.h obj
	g++ ${COMPYLE_ARGS}  -o obj/resource-loader.o -c ResourceLoader.cpp
obj/resource-handler.o: ResourceHandler.cpp ResourceHandler.h obj
	g++ ${COMPYLE_ARGS}  -o obj/resource-handler.o -c ResourceHandler.cpp
obj/hash.o: hash.cpp hash.h obj
	g++ ${COMPYLE_ARGS}  -o obj/hash.o -c hash.cpp
	
clean:
	rm -rf bin
	rm -rf obj

bin/main.out: test/main.cpp obj/resource-manager.o obj/resource-loader.o obj/test-loader.o obj/resource-handler.o obj/hash.o bin
	g++ ${COMPYLE_ARGS}  -o bin/main.out test/main.cpp obj/resource-loader.o obj/test-loader.o obj/resource-manager.o obj/resource-handler.o obj/hash.o
obj/test-loader.o: test/TestLoader.cpp test/TestLoader.h obj
	g++ ${COMPYLE_ARGS}  -o obj/test-loader.o -c test/TestLoader.cpp