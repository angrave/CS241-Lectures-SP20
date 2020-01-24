#include <stdio.h>

int main(int argc, char** argv) {
#if 0
    for(int i = 0 ; i < argc; i++ ) {
    printf( "%d : %p : %s \n", i , *(argv + i), argv[i] );
  }
#endif 
  while( *argv ) {
    printf("%s\n", *argv);
    argv ++;
  }
  return 0; // Success
}
