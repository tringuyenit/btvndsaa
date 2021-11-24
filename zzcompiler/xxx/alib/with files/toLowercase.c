#include "../lib/tri.h"

int main () {
   int i = 0;
   char c;
   char* str = "TUTORIALS POINT";
   char *new="";
	
    while( str[i] ) {
        
        
        size_t len = strlen(new);
        char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
        strcpy(str2, new);

        c = tolower(str[i]);
        printf("%c",c);

        str2[len] = c;
        str2[len + 1] = '\0';

        free( str2 );

        i++;
    }
   
    printf("\n%s", new);



    
   return(0);
}