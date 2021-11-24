#include "../alib/tri.h"

typedef struct node
{
    char word[20];
    int so_lan_xhien;

    int line[10];
    int line_ele; // will be init zero, because ARRAY

    struct node *right_child;
    struct node *left_child;
}node;

int inorder_count = 1;
void inorder(struct node *root){
    if(root!=NULL) // checking if the root is not null
    {
        
        inorder(root->left_child); // visiting left child

        //////PRINTING DATA AT NODE

        //count space for can le
        printf("(%2d)  ", inorder_count);
        inorder_count++;
        int can_le = 15 - strlen(root->word);
        //canle
        printf("\' %s \'", root->word); 
        for(int x = 0; x<can_le; x++){
            printf(" ");
        }
        //lan xuat hien
        printf("%d  :  ", root->so_lan_xhien);
        //cac dong da xuat hien
        if(root->line_ele == 0){
            printf("%d\n", root->line[0]);
        }else{
            for(int count = 0; count<root->line_ele; count++){
                printf("%d,", root->line[count]);
            }
            printf("%d", root->line[root->line_ele]); //cho dep:)))
            printf("\n");
        }
        

        inorder(root->right_child);// visiting right child   
    }
}

struct node* find_minimum(node *root){
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}

struct node* new_node(char* string)
{
    node* p;
    p = (node*)malloc(sizeof(node));
    
    p->line_ele = 0;
    p->so_lan_xhien = 1;
    strcpy(p->word, string);
    
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

int compare_data(int string_or_int, node *root, char* string){
    // 1         :  string
    // 2 or else :  int

    int choice = string_or_int;

    if(choice == 1){
        return strcmp(root->word, string);
    }else{
        printf("Using compare INT !!!!\n"); //note for other uses
        return 0;
    }

}

struct node* insert(node *root, char* string, int line_num){
    
    if(root==NULL){
        root = new_node(string);
        root->line[root->line_ele] = line_num;
        return root;
    }else{

        if(strcmp(string, root->word) == 0){
            root->so_lan_xhien ++;

            root->line_ele ++;
            root->line[root->line_ele] = line_num;
            return root;
        }//neu word = word node --> trung lap

        int result = compare_data(1, root, string); //compare data

        if(result == -1){
            root->right_child = insert(root->right_child, string, line_num);
        }else{
            root->left_child  = insert(root->left_child, string, line_num);
        }
    }
}

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
                        line[test1_p+1] = ' ';
                    }

                }

                test1_p = test2_p;
                
            }

            if(testCapital){

                while ( (line[test1_p] != ' ')  && (line[test1_p] != '.') ){
                    line[test1_p] = ' ';
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
    //////READ DATA
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

    //input and count real number of lines
    while((c = fgetc(fp)) != EOF){
        input[pointer] = c;
        if(c == '\n'){//if new line
            c = fgetc(fp);//check next char
            pointer++; //move NEXT pointer !!!
            input[pointer] = c;

            if( (c>=65 && c<=90) || (c>=97 && c<=122)  || (c>=48 && c<=57) ){//if not null
                so_dong_input++; //means having text
            }
        }
        pointer++;
	}
	fclose(fp);
    
    //loai bo tu co chu in hoa
    get_rid_of_Capital(input);
    

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
    char blacklist[] = "stopw.txt";
    if ((fp = fopen(blacklist, "r")) == NULL) {
        printf("Error! opening file");
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

            if((c>=65 && c<=90) || (c>=97 && c<=122) || (c>=48 && c<=57)){//if not null
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
    char delimit_black[]=" \t\r\n\v\f().,";
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
    while (input[input_p] != EOF && strlen(input)){

        if(input[input_p] != '\n'){
            each_line_input[line_num][line_p] = input[input_p];
            line_p++;
        }else{
            each_line_input[line_num][line_p] = '\0';
            
            line_p=0;
            line_num++;
        }

        input_p++;
    }

    line_num = 0; // set back to zero

    //////PROCESS WORDS
    for(line_num; line_num<so_dong_input; line_num++){

        bool check_black_list = true;
        bool check_black_list2 = true; // actually check alphabet

        char *string[50];
        char *string2[50];
        char delimit[]=" 0123456789\t\r\n\v\f().,";
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

            //inserting
            if(check_black_list){

                if(create_root == false){
                    create_root = true;
                    root = new_node(string[i]);
                }else{
                    insert(root, string[i], (line_num+1)); //line_num +1 because real LINE, not ARRAY index
                }
            }

            i++;
            string[i]=strtok(NULL,delimit);
        }

    }
    
    
    inorder(root);
    return 0;
}