CC=clang
CFLAGS = -pthread -I ${HOME}/localinstall/include/
LDFLAGS = -lm -lSDL2 -L ${HOME}/localinstall/lib

all : matrix stacks sdl_test mandel0 mandel1 mandel2 mandel3 

sdl_test : sdl_test.c
	echo "*** You need SDL2 installed in ${HOME}/localinstall/"
	echo "*** run ../build_sdl2.sh to download and install"
	echo 'And,    export LD_LIBRARY_PATH=${HOME}/localinstall/lib/'
	$(CC) $(CFLAGS) $(LDFLAGS) sdl_test.c -o $@

mandel0 :mandelbrot-no-thread.c sdl_test
	$(CC) $(CFLAGS)  $(LDFLAGS) mandelbrot-no-thread.c -o $@

mandel1 : mandelbrot-attempt1.c sdl_test
	$(CC) $(CFLAGS) $(LDFLAGS) mandelbrot-attempt1.c -o $@

mandel2 : mandelbrot-attempt2.c sdl_test
	$(CC) $(CFLAGS) $(LDFLAGS) mandelbrot-attempt2.c -o $@

mandel3 : mandelbrot-task.c sdl_test
	$(CC) $(CFLAGS) $(LDFLAGS) mandelbrot-task.c -o $@
	
matrix : matrix.c 
	$(CC)  $(CFLAGS) matrix.c -o $@

stacks : stacks.c
	$(CC)  $(CFLAGS) stacks.c -o $@

clean :
	rm mandel0 mandel1 mandel2 mandel3 stacks matrix sdl_test 2>/dev/null || true
	

