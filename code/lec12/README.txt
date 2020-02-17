The graphic Mandelbrot demos use SDL2.

run ../build_sdl2.sh 

to download and install SDL2 to ${HOME}/localinstall/

To test your installation this directory include sdl_test 

make sdl_test
./sdl_test

On Linux, you will need to add the lib directory so the dynamic libraries can be loaded at runtime-
export LD_LIBRARY_PATH=${HOME}/localinstall/lib/

If running on a remote Linux but with a local display, use the "-Y" option

ssh -Y linux.ews.illinois.edu

to connect using X Windows.  You will also need to install an X server on your local machine e.g. Quartz for OSX
