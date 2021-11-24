#include "../lib/tri.h"

int main () {

    char *str = "blablabla";
    char c = 'H';

    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';

    printf( "%s\n", str2 ); /* prints "blablablaH" */

    free( str2 );
    return(0);
}