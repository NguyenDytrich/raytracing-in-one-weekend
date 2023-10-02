compile: object
	gcc -o main \
		./build/main.o \
		./build/vec3.o \
		./build/color.o \
		./build/progress.o \
		./build/collision.o

object:
	@rm -rf build
	@mkdir build
	gcc -c -o ./build/vec3.o src/vec3.c
	gcc -c -o ./build/color.o src/color.c
	gcc -c -o ./build/progress.o src/progress.c
	gcc -c -o ./build/main.o src/main.c
	gcc -c -o ./build/collision.o src/collision.c
