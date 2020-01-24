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

