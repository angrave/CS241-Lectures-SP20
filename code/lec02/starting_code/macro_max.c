#include <stdio.h>

#define max(a,b) a<b ? a : b

int main(int argc, char**argv) {
  int result = max(10,5) + 1; 

  printf("Result:%d \n", result);
}
