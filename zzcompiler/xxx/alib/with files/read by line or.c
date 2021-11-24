#include "../tri.h"

int main(){

    char * filename = "../completed/vanban.txt"; 
	FILE * fp = fopen(filename, "r");
    if ((fp = fopen("../completed/vanban.txt", "r")) == NULL) {
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

    return 0;
}

int main(){
    char c[1000];
    FILE *fptr;

    if ((fptr = fopen("fileNAME", "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    // reads text until newline is encountered
    fscanf(fptr, "%[^lalalala]", c);
    printf("Data from the file:\n%s", c);
    fclose(fptr);
}