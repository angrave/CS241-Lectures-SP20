#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {

  char * buffer = NULL;
  size_t buf_capacity = 0;
  while(1) {
   ssize_t result = getline( &buffer, &buf_capacity, stdin);
   printf("result is %d at %p. Contents=%s", (int)result,buffer, buffer );
}
  return 0;
}
