
#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include<string.h>

#define MAXSIZE 20
#define LEFT    8
#define  RIGHT  9
typedef struct node{
    char c;
    int weight;
    int huff_code[MAXSIZE];
    int length;

    struct node *next;
    struct node *left;
    struct node *right;
} Node;


Node *make_node(char c);
Node *read_file(char *filename);
void combine_smallest(Node **list_head);
void build_tree(Node **list_head);
char *print_tree(Node *tree_list);
void huff_coding(Node *tree_head, int length);
void show_result(Node *tree_head,int *count);

int main(void)
{
    Node *list_head;
    Node *tree_head;
    Node *temp;
    int *count  =(int *)calloc(1, sizeof(int));
    *count = 0;
    list_head = read_file("sample2.txt");

    temp = list_head;
    while(temp != NULL){
        printf("%c occurs %d times\n",temp->c,temp->weight);
        temp = temp->next;
    }

    build_tree(&list_head);
    tree_head = list_head;
    /*
    printf("%c %c\n",tree_head->left->c,tree_head->right->c);
    printf("root left:%c , root right %c\n",tree_head->left->c,tree_head->right->left->left->left->c);
    */
    huff_coding(tree_head,0);
    /*
    printf("char is %c , length is %d\n",tree_head->right->left->left->left->c,tree_head->right->left->left->left->length);
    for(i=0;i<tree_head->right->left->left->left->length;i++){

        printf("%d\n ",tree_head->right->left->left->left->huff_code[i]);
    }
    */
    show_result(tree_head,count);
    printf("%d bytes\n",*count);


    return 0;
}

Node *read_file(char *filename)
{
    FILE *fp;
    Node *list_head = (Node *)calloc(1,sizeof(Node));
    Node *p = list_head->next;
    Node *temp;
    char i;
    int flag = 0; /*0 means not exist, 1 means exist*/

    fp = fopen(filename,"r");
    if(fp==NULL){
        printf("Cannot open the file\n");
        exit(EXIT_FAILURE);
    }

    while((i = getc(fp) ) != EOF){
        if(i>=' '&&i <= '~'){ /*only care about visible char*/
            while(flag==0 && p !=NULL){
                if(p->c == i){
                    p->weight++; /*frequency ++*/
                    flag=1;
                }
                p = p->next;
            }

            if(flag ==0){
                /*insert a new node*/
                p = list_head->next;
                temp= make_node(i);
                list_head->next = temp;
                temp->next=p;
            }
            /*reset*/
            p= list_head->next;
            flag=0;
        }
    }
    return list_head->next; /* list_head is no meaning*/
}

Node *make_node(char c)
{
    Node *n = (Node *)calloc(1,sizeof(Node));
    n->c = c;
    n->weight=1;
    return n;
}

/*include
 * find two smallest char;
 * delete this two;
 * generate a subtree and insert it into list_head;
 * */
void combine_smallest(Node **list_head)
{
    Node *p = *list_head;
    Node *pre = NULL;
    Node *n1;
    Node *n2;
    Node *result;
    int smallest = (*list_head)->weight;
    int second_smallest;
    /*find smallest*/
    while(p != NULL){
        if(p->weight< smallest){
            smallest = p->weight;
        }
        p = p->next;
    }
    /*for smallest node*/
    p=*list_head;
    if(smallest==p->weight){
        n1= *list_head;
        *list_head = (*list_head)->next; /*delete n1*/
    }else{
        while(p->next->weight != smallest){
            p=p->next;
        }
        n1 = p->next;
        p->next = p->next->next; /*delete n1*/
    }
    /*for second smallest node*/
    p=*list_head;
    second_smallest = (*list_head)->weight;
    while(p != NULL){
        if(p->weight< second_smallest){
            second_smallest = p->weight;
        }
        p = p->next;
    }
    p=*list_head;
    if(second_smallest==p->weight){
        n2= *list_head;
        *list_head = (*list_head)->next; /*delete*/
    }else{
        while(p->next->weight != second_smallest){
            p=p->next;
        }
        n2 = p->next;
        p->next = p->next->next;/*delete*/
    }

    p=*list_head;
    result = (Node *)calloc(1, sizeof(Node));/*subtree node*/
    result->weight = n1->weight+n2->weight;
    result->left = n1;
    result->right = n2;
    result->next= p; /*insert subtree node into linked list, and also insert as a new head*/
    *list_head = result;

}

void build_tree(Node **list_head)
{
    while((*list_head)->next !=NULL){
        combine_smallest(list_head);
    }
}


char *print_tree(Node *tree_list)
{
    char *str = (char *)calloc(MAXSIZE, sizeof(char));

    if(str == NULL){
        printf("failed to allocate....");
        exit(EXIT_FAILURE);
    }
    if(tree_list == NULL){
        strcmp(str,"*");
        return str;
    }
    sprintf(str,"%c (%s) (%s)",tree_list->c,print_tree(tree_list->left),print_tree(tree_list->right));

    return str;
}

void huff_coding(Node *tree_head, int length)
{
    static int a[MAXSIZE];
    int i;
    if(tree_head->left == NULL &&tree_head->right == NULL){
        tree_head->length = length;
        for(i=0;i<length;i++){
            tree_head->huff_code[i] = a[i]-LEFT;
        }
        return;
    }
    a[length] = LEFT;
    huff_coding(tree_head->left,length+1);
    a[length] = RIGHT;
    huff_coding(tree_head->right,length+1);
    a[length] = 0;
}

void show_result(Node *tree_head,int *count)
{
    int i;
    if(tree_head->left==NULL &&tree_head->right==NULL){
        printf("\'%c\' :\t",tree_head->c);
        for(i=0;i<tree_head->length;i++){
            printf("%d",tree_head->huff_code[i]);
        }
        printf("\t(\t%d *\t%d)\n",tree_head->length,tree_head->weight);
        *count += tree_head->weight*tree_head->length;
        return;
    }
    show_result(tree_head->left,count);
    show_result(tree_head->right,count);
}