#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_message(char**magic) {
 *magic = malloc(11);
 strcpy(*magic, "Amazing C!");
}

int main() {
  char *ptr = NULL;
  get_message( &ptr );
  puts( ptr ); // equiv printf("%s\n", ptr);
}