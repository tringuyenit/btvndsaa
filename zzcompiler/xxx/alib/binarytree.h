#include "tri.h"

typedef struct node
{
    char word[20];
    int so_lan_xhien;

    int line[10];
    int line_ele; // will be init zero, because ARRAY

    int y_axisssss[10];

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
            printf("(%d,%d)\n", root->line[0], root->y_axisssss[0]);
        }else{
            for(int count = 0; count<root->line_ele; count++){
                printf("(%d,%d) ", root->line[count], root->y_axisssss[count]);
            }
            printf("(%d,%d)", root->line[root->line_ele], root->y_axisssss[root->line_ele]); //cho dep:)))
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

struct node* insert(node *root, char* string, int line_num, int y_axis){
    
    if(root==NULL){
        root = new_node(string);
        root->line[root->line_ele] = line_num;
        root->y_axisssss[root->line_ele] = y_axis;
        return root;
    }else{

        if(strcmp(string, root->word) == 0){
            root->so_lan_xhien ++;

            root->line_ele ++;
            root->line[root->line_ele]       = line_num;
            root->y_axisssss[root->line_ele] = y_axis;
            return root;
        }//neu word = word node --> trung lap

        int result = compare_data(1, root, string); //compare data

        if(result == -1){
            root->right_child = insert(root->right_child, string, line_num, y_axis);
        }else{
            root->left_child  = insert(root->left_child, string, line_num, y_axis);
        }
    }
}
