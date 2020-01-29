#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char* user = getenv("USER");
  char* secret = getenv("SECRET");
  if( user == NULL || secret == NULL) {
    fprintf(stderr,"Please ensure USER and SECRET environment variables are set!\n");
    exit(1);
  }
  puts(user);
  puts(secret);
  return 0;
}
