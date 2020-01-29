
#include <unistd.h>
#include <stdio.h>

int main() {
   int var = 10;

 
   fork();
   fork();
   fork();

   printf("My variable is %d and it is stored at %p \n", var, &var);
   return 0;
}
