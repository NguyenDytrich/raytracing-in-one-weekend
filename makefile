compile: object
	gcc -o main \
		./build/*.o

object:
	@rm -rf build
	@mkdir build
	gcc -c -o ./build/vec3.o src/vec3.c
	gcc -c -o ./build/color.o src/color.c
	gcc -c -o ./build/progress.o src/progress.c
	gcc -c -o ./build/main.o src/main.c
	gcc -c -o ./build/collision.o src/collision.c
	gcc -c -o ./build/mymem.o src/mymem.c
