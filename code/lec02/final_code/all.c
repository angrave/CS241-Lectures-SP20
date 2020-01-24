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
int strcmp(const char *s1, const char *s2) {
    while(*s1 != 0 && *s2 != 0) {
       if(*s1 != *s2) return 1; // TODO FIX
       s1++;
       s2++;
    }
    if( *s1 == 0 && *s2 ==0) return 0;
    return 1; // TODO FIX ME
}

if( ! strcmp( s, "yes") )

#include <stdio.h>

int contains_at(char*);


int main(int argc, char** argv) {
  int result = contains_at(NULL);
  if(result) printf("Contains an @");
  else printf("No @ found");
  return 0;
}

int contains_at(char* ptr) {
  while( * ptr ) { 
    if( * ptr  == '@' ) { return 1; } // SUCCESS
    ptr ++;
  }
  return 0;
}
#include <stdio.h>

#define max(a,b) ((a)>(b) ? (a) : (b) )

int main(int argc, char**argv) {
  int result = max(10,5) + 1; 
//int result = 10>5 ? 10 : 5 +1;
  printf("Result:%d \n", result);
}
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  printf("%p %p\n", main, malloc);

  return 0;
}
#include <stdio.h>

int main(int argc, char** argv) {
#if 0
    for(int i = 0 ; i < argc; i++ ) {
    printf( "%d : %p : %s \n", i , *(argv + i), argv[i] );
  }
#endif 
  while( *argv ) {
    printf("%s\n", *argv);
    argv ++;
  }
  return 0; // Success
}
#include <stdio.h>

int f1(int, int*);


 int abc = 5;

 int main() { f1( 10, &abc); return 0;}

 int f1(int v1, int* v2) {
    printf("&v1 is %p \n", &v1);

    printf("&v2 is %p \n", &v2);

    printf(" v2 is %p \n",v2);
    return 0;
}

