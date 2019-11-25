
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
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
Node *combine_smallest(Node **list_head);
int main(void)
{
    Node *list_head;
    Node *tree_head;
    Node *temp;
    Node *result;
    list_head = read_file("sample.txt");

    temp = list_head;
    while(temp != NULL){
        printf("%c occurs %d times\n",temp->c,temp->weight);
        temp = temp->next;
    }

    result = combine_smallest(&list_head);
    printf("%c %c\n",result->left->c,result->right->c);

    temp = list_head;
    while(temp != NULL){
        printf("%c occurs %d times\n",temp->c,temp->weight);
        temp = temp->next;
    }

    return 0;
}

Node *read_file(char *filename)
{
    FILE *fp;
    Node *list_head = (Node *)calloc(1,sizeof(Node));
    Node *p = list_head->next;
    Node *temp;
    char i;
    int flag = 0;

    fp = fopen(filename,"r");
    if(fp==NULL){
        printf("Cannot open the file\n");
        exit(EXIT_FAILURE);
    }

    while((i = getc(fp) ) != EOF){
        while(flag==0 && p !=NULL){
            if(p->c == i){
                p->weight++;
                flag=1;
            }
            p = p->next;
        }

        if(flag ==0){
            p = list_head->next;
            temp= make_node(i);
            list_head->next = temp;
            temp->next=p;
        }
        p= list_head->next;
        flag=0;
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
Node *combine_smallest(Node **list_head)
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
        *list_head = (*list_head)->next;
    }else{
        while(p->next->weight != second_smallest){
            p=p->next;
        }
        n2 = p->next;
        p->next = p->next->next;
    }

    p=*list_head;
    result = (Node *)calloc(1, sizeof(Node));/*subtree node*/
    result->weight = n1->weight+n2->weight;
    result->left = n1;
    result->right = n2;
    result->next= p; /*insert subtree node into linked list, and also insert as a new head*/
    *list_head = result;

    return result;

}