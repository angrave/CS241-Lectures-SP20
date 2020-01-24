
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

