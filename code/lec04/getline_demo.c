#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {

  char * buffer = NULL;
  size_t buf_capacity = 0;

  while( 1 ) {
    ssize_t result = getline( & buffer, & buf_capacity, stdin );
    if( result == -1 ) break;

    printf("buffer is at %p, capacity is %d, result= %d\n",
              buffer, (int) buf_capacity, (int) result);
    
    // what if result is zero?
    // what if there is no newline
    if(result >0 && buffer[ result - 1] == '\n') {
      buffer [ result -1 ] = '\0';
    }
    
    
    printf("Buffer contents: %s", buffer );
 }
 free( buffer);
 buffer = NULL;

 return 0;
}
