#include "../alib/binarytree.h"

void get_rid_of_Capital(char* line){
    int test1_p=0;
    int test2_p;
    bool testCapital = false;

    bool stop_test1 = true;
    bool unlock_checking = true;
    bool begin_real_check = false;

    while (line[test1_p] != '\0' && test1_p<strlen(line)){
        
		if(unlock_checking){
            if(line[test1_p] != ' '){
                test1_p++; //sang ngay vi tri tiep theo, thoat khoi space
                while (line[test1_p] != ' '){
                    test1_p++;
                }
                
                begin_real_check = true;
                unlock_checking  = false;
            }
        }

        if(begin_real_check && !unlock_checking){
            if( line[test1_p]>=65 && line[test1_p]<=90 ){
                test2_p = test1_p;
                test1_p--;

                if(line[test1_p] == ' '){

                    test1_p--;

                    while (1){
                        if(line[test1_p] != ' '){
                            if(line[test1_p] != '.'){
                                testCapital = true;
                                break;
                            }
                        }
                        test1_p--;
                    }

                    test1_p = test2_p;
                }else{
                    test1_p++;
                }
                
            }


            if(testCapital){
                while ( (line[test1_p] != ' ') && (line[test1_p] != '.') ){
                    printf("%c", line[test1_p]);
                    line[test1_p] = ' ';
                    test1_p++;
                }
                printf("\n\n");
                test1_p--;//ko can thiet but whatever
                testCapital = false;
            }
        }
        
        test1_p++;
    }
}

void get_rid_of_Capital2(char* line){
    int test1_p=0;
    int test2_p;
    bool testCapital = false;

    bool stop_test1 = true;
    bool unlock_checking = true;
    bool begin_real_check = false;

    while (line[test1_p] != '\0' && test1_p<strlen(line)){
        
		if(unlock_checking){
            if(line[test1_p] != ' '){
                test1_p++; //sang ngay vi tri tiep theo, thoat khoi space
                while (line[test1_p] != ' '){
                    test1_p++;
                }
                
                begin_real_check = true;
                unlock_checking  = false;
            }
        }

        if(begin_real_check && !unlock_checking){
            if( line[test1_p]>=65 && line[test1_p]<=90 ){

                test2_p = test1_p;
                test1_p--;

                if(line[test1_p] == ' '){

                    test1_p--;

                    while (1){
                        if(line[test1_p] != ' '){
                            if(line[test1_p] != '.'){
                                testCapital = true;
                                break;
                            }
                        }
                        test1_p--;
                    }

                }else{

                    char c = line[test1_p+2];
                    
                    if( !(c>=65 && c<=90) && !(c>=97 && c<=122) && !(c>=48 && c<=57) ){
                        line[test1_p+1] = '@';
                    }

                }

                test1_p = test2_p;
                
            }


            if(testCapital){
                while ( (line[test1_p] != ' ')  && (line[test1_p] != '.') ){
                    line[test1_p] = '@';
                    test1_p++;

                }
                

                test1_p--;//ko can thiet but whatever
                testCapital = false;
            }
        }
        
        test1_p++;
    }
}



int main () {


    char filename[] = "vanban.txt";
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    int so_dong_input=1;
    char c;
    char input[1000];
    int pointer = 0;

    while((c = fgetc(fp)) != EOF){
        input[pointer] = c;
        if(c == '\n'){//if new line
            c = fgetc(fp);//check next char
            pointer++; //move NEXT pointer !!!
            input[pointer] = c;

            if( (c>=65 && c<=90) || (c>=97 && c<=122)  || (c>=48 && c<=57)){//if not null
                so_dong_input++; //means having text
            }
        }
        pointer++;
	}
	fclose(fp);

    get_rid_of_Capital2(input);
    printf("%s\n", input);
        
    return(0);
}