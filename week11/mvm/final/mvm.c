#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mvm.h"

/*Used to free one mvmcell in linked list */
void free_one_cell(mvmcell **cell);
/*Used to free the whole mvmcell's linked list */
void free_linked_list(mvmcell **head);

mvm *mvm_init(void)
{
    mvm *m = (mvm *)malloc(sizeof(mvm));
    if(m==NULL){
        ON_ERROR("Failed to allocate for m...\n");
    }
    m->head = NULL; /*important! easy for further search and multisearch*/
    m->numkeys = 0;
    return m;
}

int mvm_size(mvm* m)
{
    if(m == NULL){
        return 0;
    }
    return m->numkeys;
}

/* Insert one key/value pair */
void mvm_insert(mvm* m, char* key, char* data)
{
    mvmcell *cell;
    if(m==NULL||key == NULL||data ==NULL){
        return;
    }
    cell = (mvmcell *)malloc(sizeof(mvmcell));
    /*Add one more sizeof(char) to avoid overflow*/
    cell->key = (char *)malloc(sizeof(char)*strlen(key)+sizeof(char));
    cell->data = (char *)malloc(sizeof(char)*strlen(data)+sizeof(char));

    strcpy(cell->key,key);
    strcpy(cell->data,data);
    cell->next = m->head;
    m->head = cell;
    m->numkeys++;
}

/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m)
{
    mvmcell *current;
    char *str;
    int offset = 0;
    if(m ==NULL){
        return NULL;
    }
    current = m->head;
    str = (char *)calloc(1,sizeof(char));
    while(current != NULL){
            str = (char *)realloc(str,(strlen(str)+strlen(current->key)\
            +strlen(current->data)+strlen("[]() "))*sizeof(char)+sizeof(char));
            offset += sprintf(str+offset,"[%s](%s) ",\
            current->key,current->data);
            current = current->next;
    }
    return str;
}

/* Remove one key/value */
void mvm_delete(mvm* m, char* key)
{
    mvmcell *current;
    mvmcell *temp;
    if(m==NULL || key ==NULL){
        return;
    }
    current = m->head;
    if(strcmp(current->key,key)==0){
        m->head = m->head->next;
        m->numkeys--;
        free_one_cell(&current);
        return;
    }
    /*Cannot exchange, make sure current->next is not NULL;*/
    while(current->next != NULL && strcmp(current->next->key,key)!=0){
        current = current->next;
    }
    if(current->next == NULL){
        return; /*No such key/value pair*/
    }
    temp = current->next;
    current->next = current->next->next;
    free_one_cell(&temp);
    m->numkeys--;
}

/*Used to free one mvmcell in linked list */
void free_one_cell(mvmcell **cell)
{
    mvmcell *temp;
    if(cell == NULL || *cell ==NULL){
        return;
    }
    temp = *cell;
    free(temp->data);
    free(temp->key);
    free(temp);
    *cell = NULL;
}

/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key)
{
    mvmcell *current;
    if(m==NULL||key==NULL){
        return NULL;
    }
    current = m->head;
    while(current != NULL && strcmp(current->key,key)!=0 ){
        current = current -> next;
    }
    if(current == NULL){
        return NULL;/*Cannot find such key/value pair*/
    }
    return current->data;
}


char** mvm_multisearch(mvm* m, char* key, int* n)
{
    char **a;
    int index = 0;
    mvmcell *current;
    if(m == NULL ||key == NULL || n == NULL){
        return NULL;
    }
    *n = 0;
    a = (char **)malloc(sizeof(char *));
    current = m->head;
    while(current !=NULL){
        if(strcmp(current->key,key)==0){
                (*n)++;
                a = (char **)realloc(a,(*n)* sizeof(char *));
                a[index] = current->data;
                index ++;      
        }
        current = current ->next;
    }
    return  a;
}

/*Used to free the whole mvmcell's linked list */
void free_linked_list(mvmcell **head)
{
    mvmcell *current;
    mvmcell *next;
    if(head == NULL||*head == NULL){
        return;
    }
    current = *head;
    while(current != NULL){
        next = current->next;
        free_one_cell(&current);
        current = next;
    }
    *head = NULL;
}

/* Free & set p to NULL */
void mvm_free(mvm** p)
{
    mvm *a;
    if( p ==NULL || *p == NULL){
        return;
    }
    a = *p;
    free_linked_list(&(a->head));
    free(a);
    *p =NULL;
}

