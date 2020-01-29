#include <stdlib.h>
#include <stdio.h>

#define CAPACITY (100)

int main(int argc,char**argv) {
  FILE* f = fopen( "mydata.csv", "r");
  if( f == NULL) {
    fprintf(stderr, "Could not open data file!\n");
    exit(1);
  }

  int data[CAPACITY];
  int nread = 0;

  while(nread < CAPACITY ) {
     int result = fscanf(f , "%d,%d", data + nread *2 , data + nread*2 +1);
     if(result == 2) { nread += 2; continue; }
     if(result == 1) { fprintf(stderr,"Read only one value !?"); exit(2);}
     if(result < 1) break;
  }
  printf("Number of items read: %d\n", nread);
  return 0;
}
