#include <stdio.h>
#include <unistd.h>

int main( int argc, char** argv) {
  char buffer[4096];
  
  ssize_t result = read( 0 , buffer, sizeof(buffer) -1 );

  printf("result is %d", (int) result);
  if( result == -1 ) {
    fprintf(stderr,"Could not read from stdin!\n");
    exit(1);
  }
  buffer[ result ] = '\0';

  printf("and you gave me:%s\n", buffer );
  puts(buffer);
  return 0;
}
