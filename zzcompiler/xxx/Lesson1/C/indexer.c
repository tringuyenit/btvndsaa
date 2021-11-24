#include "../../../alib/binarytree.h" //included tri.h

void get_rid_of_Capital(char* line){
    int test1_p=0;
    int test2_p;
    bool testCapital = false;

    bool stop_test1 = true;
    bool unlock_checking = true;
    bool begin_real_check = false;

    while (line[test1_p] != '\0' && test1_p<strlen(line)){
        
        //ko xu li cau dau tien, chi bat dau xu li tu cau thu 2, vi cau dau tien viet hoa
		if(unlock_checking){
            
            if(line[test1_p] != ' '){

                test1_p++; //sang ngay vi tri tiep theo, thoat khoi space
                while (line[test1_p] != ' '){//tim space thu 2, meaning tim second word
                    test1_p++;//nhay sang ngay char tiep theo(char dau tien cua second word)
                }
                
                //bat dau check khi da tim dc second word
                begin_real_check = true;//begin checking "fuction"
                unlock_checking  = false;//stop this "fuction"
            }
        }

        //bat dau check NEU tim dc second word
        if(begin_real_check && !unlock_checking){

            if( line[test1_p]>=65 && line[test1_p]<=90 ){

                test2_p = test1_p;
                test1_p--;

                if(line[test1_p] == ' ' || line[test1_p] == '\t' || line[test1_p] == '\n'){

                    test1_p--;

                    while (1){
                        if(line[test1_p] != ' '){
                            if(line[test1_p] != '.'){
                                testCapital = true;
                                break;
                            }else{
                                break;
                            }
                            
                        }
                        test1_p--;
                    }

                }else{

                    char c = line[test1_p+2];

                    if( !(c>=65 && c<=90) && !(c>=97 && c<=122) && !(c>=48 && c<=57) ){
                        line[test1_p+1] = '$';//5555555
                    }

                }

                test1_p = test2_p;
                
            }

            if(testCapital){

                while ( (line[test1_p] != ' ')  && (line[test1_p] != '.')  && (line[test1_p] != '\n') && (line[test1_p] != '\t')){
                    //999999999999999999999999999 BO DI 2 dieu kien cuoi
                    line[test1_p] = '$';//5555555
                    test1_p++;

                }
                
                test1_p--;//ko can thiet but whatever
                testCapital = false;
            }
        }
        
        test1_p++;
    }
}

int main(){

    printf("\n----------------------------------------");
    printf("\n     NGUYEN DUC TRI  -  20194862\n");
    printf("----------------------------------------\n\n");
    //////READ DATA

    char filename[] = "../completed/vanban.txt";
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Error! opening %s", filename);
        exit(1);
    }

    int so_dong_input=1;
    char c;

    char input_tmp2[2000]; //load from file
    char input_tmp [2000]; //load from file
    char input     [2000];// use in program
    
    int pointer = 0;

    //input and count real number of lines
    while((c = fgetc(fp)) != EOF){

        input_tmp[pointer] = c;
        
        if(c == '\n'){//if new line

            c = fgetc(fp);//check next char

            pointer++; //move NEXT pointer !!!
            input_tmp[pointer] = c;
        }
        pointer++;
	}
	fclose(fp);

    //loai bo tu co chu in hoa
    get_rid_of_Capital(input_tmp);

    //count number of lines and also replicate to real 'input' string to work with
    pointer = 0;
    while(input_tmp[pointer] != '\0' && pointer<strlen(input_tmp)){
        
        char c = input_tmp[pointer];
        input[pointer] = c;
        
        if(c == '\n'){//if new line

            // if( input_tmp[pointer+1] != '\n' && input_tmp[pointer+1] >= 0){//if not null(aka line with nothing)
            //     so_dong_input++; //means having text
            // } 999999999999999999999999999

            so_dong_input++; //means having text

        }

        pointer++;
	}
    

    //creating array of input lines
    char** each_line_input = (char**) malloc((so_dong_input+1)*sizeof(char*));
    for(int i = 0; i<so_dong_input; i++){
        each_line_input[i] = (char* ) malloc(200*sizeof(char)); //assuming each line 200 chars long
    }

    char** each_line_input2 = (char**) malloc((so_dong_input+1)*sizeof(char*));
    for(int i = 0; i<so_dong_input; i++){
        each_line_input2[i] = (char* ) malloc(200*sizeof(char)); //assuming each line 200 chars long
    }


    ////////READ BLACK LIST
    char blacklist[] = "../completed/stopw.txt";
    if ((fp = fopen(blacklist, "r")) == NULL) {
        printf("Error! opening %s", blacklist);
        exit(1);
    }

    int so_dong_black_list=1;
    char input_black[1000];
    pointer = 0;

	while((c = fgetc(fp)) != EOF) {

        input_black[pointer] = c;

        if(c == '\n'){//if new line

            c = fgetc(fp);//check next char
            pointer++; //move NEXT pointer !!!
            input_black[pointer] = c;

            if( c != '\n' ){//if not null(aka lines with nothing)
                so_dong_black_list++; //means having text
            }
        }

        pointer++;
	}
	fclose(fp);


    ///////STORE BLACK LIST IN ARRAY

    //creating black list array
    char** black_words = (char**) malloc(so_dong_black_list*sizeof(char*));
    for(int i = 0; i<so_dong_black_list; i++){
        black_words[i] = (char* ) malloc(20*sizeof(char)); //assuming each word 20 chars long
    }

    //put stop words in black_words array
    char *string_black[20];
    char delimit_black[]=" \t\r\n\v\f().,"; //WARNING vs real blacklist
    int i = 0, j = 0;

    string_black[i]=strtok(input_black,delimit_black);
    while(string_black[i]!=NULL && i<so_dong_black_list){

        // to lowercase
        for(int x=0; x<=strlen(string_black[i]); x++){
            if( string_black[i][x]>=65 && string_black[i][x]<=90 ){
                string_black[i][x]=string_black[i][x] + 32;
            }
        }

        //store in array
        strcpy(black_words[i], string_black[i]);

        i++;
        string_black[i]=strtok(NULL,delimit_black);
    }
    

    ////////MOTHER LINE PROCESS
    node* root;// xu li cong kenh : status string of ROOT
    bool create_root = false;
    
    //extracting lines in to line-array(each_line_input) that malloc above
    int line_num = 0, input_p = 0, line_p = 0;
    while (input[input_p] != EOF && strlen(input) && line_num<so_dong_input){

        if(input[input_p] != '\n'){

            //aphabet filter
            char c = input[input_p];
            if(!(c>=65 && c<=90) && !(c>=97 && c<=122) && !(c>=48 && c<=57) && c!='.' && c!=' ' && c>=0){
                each_line_input[line_num][line_p] = ' '; //5555555
            }else{
                each_line_input[line_num][line_p] = input[input_p];
            }
            
            line_p++;
        }else{
            // if(input[input_p+1] != '\n'){//get rid of lines with only '\n'
            //     each_line_input[line_num][line_p] = '\0';
            //     line_p=0;
            //     line_num++;
            // } 999999999999999999999999999

            each_line_input[line_num][line_p] = '\0';
            line_p=0;
            line_num++;
        }

        input_p++;
    }


    //last line process
    int count = 0;
    char last_line_tmp[200];
    while (each_line_input[so_dong_input-1][count] >= 0){
        last_line_tmp[count] = each_line_input[so_dong_input-1][count];
        count++;
    }
    strcpy(each_line_input[so_dong_input-1], last_line_tmp);
    

    //////TEST
    // for(int a = 0; a<so_dong_input; a++){
    //     printf("%d : %s\n", (a+1), each_line_input[a]);
    // }

    // exit(0);
    // printf("%d\n",strlen(each_line_input[so_dong_input-1]));
    // printf("%d", each_line_input[so_dong_input-1][67]);
    // printf("\n\n");
    

    line_num = 0; // set back to zero

    //////PROCESS WORDS
    for(line_num; line_num<so_dong_input; line_num++){

        bool check_black_list = true;
        bool check_black_list2 = true; // actually check alphabet

        int count_y_axis = 1;
        char *string[50];
        char *string2[50];
        char delimit[]=" \t\r\n\v\f.";
        i = 0, j = 0;
        int num_word_in_line = 0;// for counting words in line, to REMOVE the LAST sh!t word

        string[i]=strtok(each_line_input[line_num],delimit);
        while(string[i]!=NULL){ //z-1 removing the last word (or smt..)
            
            // to lowercase
            for(int x=0; x<=strlen(string[i]); x++){

                if( string[i][x]>=65 && string[i][x]<=90 ){
                    string[i][x]=string[i][x] + 32;
                }

            }

            //check black list
            for(int y = 0; y<so_dong_black_list; y++){//because black_words array is 20

                if(strcmp(string[i], black_words[y]) == 0){
                    check_black_list = false;//shit!!
                    break;
                }

                check_black_list = true;//ko sao :)
            }

            // if(!check_black_list){
            //     printf("DCM %s\n", string[i]);
            // }

            //inserting
            if(check_black_list){
                if(create_root == false){
                    create_root = true;
                    root = new_node(string[i]);
                }else{
                    char tmp = string[i][0];
                    if( (tmp>=65 && tmp<=90) || (tmp>=97 && tmp<=122) ){
                        // printf("%s %d\n", string[i], count_y_axis);
                        insert(root, string[i], (line_num+1), count_y_axis); //line_num +1 because real LINE, not ARRAY index
                    }
                    
                }
            }

            i++;
            string[i]=strtok(NULL,delimit);
            count_y_axis++;
        }

    }
    
    inorder(root);
    return 0;
}