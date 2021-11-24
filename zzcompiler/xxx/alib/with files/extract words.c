#include "../tri.h"

int main(){

	FILE * fp;
    if ((fp = fopen("fileNAME", "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

	char c; 
	int count = 0; 
	while((c = fgetc(fp)) != EOF) 
	{ 
		if(c == ' ' || c == '\n') 
		{ 
			printf("\n"); 
			++count; 
		} 
		else 
		{ 
			printf("%c", c); 
		} 
	} 
	fclose(fp); 
 
	printf("This file has %d words in it.", count);

    return 0;
}