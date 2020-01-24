#include <stdio.h>

int contains_at(char*);


int main(int argc, char** argv) {
  int result = contains_at("Test");
  
  if(result) puts("Contains an @");
  else puts("No @ found");
  return 0;
}

int contains_at(char* ptr) {
  char c;
  while( (c = *ptr) ) {
    
    if( c == '@' ) return 1;
    ptr ++;
  }
  return 0;
}
