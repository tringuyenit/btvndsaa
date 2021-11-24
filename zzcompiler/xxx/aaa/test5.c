#include "../alib/tri.h"

int main(){
    int count_y_axis = 1;
    char qqq[] = "tri nguyen           dep trai\n";
    char *string[50];
    char *string2[50];
    char delimit[]=" \t\r\n\v\f";
    int i = 0, j = 0;
    int num_word_in_line = 0;// for counting words in line, to REMOVE the LAST sh!t word

    string[i]=strtok(qqq,delimit);
    while(string[i]!=NULL){ //z-1 removing the last word (or smt..)

        i++;
        string[i]=strtok(NULL,delimit);
        count_y_axis++;
    }
    count_y_axis--;
    printf("%d\n", count_y_axis);
    return 0;
}