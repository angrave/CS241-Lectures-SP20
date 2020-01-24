#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  printf("%p %p\n", main, malloc);

  return 0;
}
