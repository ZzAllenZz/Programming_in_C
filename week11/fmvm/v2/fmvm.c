#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fmvm.h"

#define NULLKEY -1
#define ALPHABLET 26

/*Used to free one mvmcell in linked list */
void free_one_cell(mvmcell **cell);
/*Used to free the whole mvmcell's linked list */
void free_linked_list(mvmcell **head);
void array_init(mvmcell array[HASHSIZE]);
int hash_function(char *key);


mvm *mvm_init(void)
{
    mvm *m = (mvm *)calloc(1,sizeof(mvm));
    if(m==NULL){
        ON_ERROR("Failed to allocate for m...\n");
    }
    array_init(m->array);
    m->numkeys = 0;
    return m;
}

void array_init(mvmcell array[HASHSIZE])
{
    int i;
    for(i=0;i<HASHSIZE;i++){
        array[i].key = NULL;
        array[i].data = NULL;
        array[i].address = NULLKEY;
        array[i].next = NULL;
    }
}

int mvm_size(mvm* m)
{
    if(m ==NULL){
        return 0;
    }
    return m->numkeys;
}

/* Insert one key/value pair */
void mvm_insert(mvm* m, char* key, char* data)
{
    int address;
    mvmcell *new_cell;
    if( m==NULL ||key ==NULL || data == NULL) {
        return;
    }
    address = hash_function(key);
    if(m->array[address].address ==NULLKEY){
        m->array[address].address = address;
    }
    new_cell = (mvmcell*)malloc(sizeof(mvmcell));
    new_cell->data = (char *)malloc(sizeof(char)*strlen(data)+sizeof(char));
    new_cell->key = (char *)malloc(sizeof(char)*strlen(key)+sizeof(char));
    new_cell->address = address;

    strcpy(new_cell->key,key);
    strcpy(new_cell->data,data);
    new_cell->next = m->array[address].next;
    m->array[address].next =new_cell;
    m->numkeys++;
    return;
}


int hash_function(char *key)
{
    int len = strlen(key);
    int i;
    unsigned int pow =1;
    int address ;
    unsigned  int raw_address = 0;
    for(i=0;i<len;i++){

        if(key[i]>='A'&&key[i]<='Z'){
            raw_address += (unsigned int)(key[i]-'A')*pow;
        }else if(key[i]>='a'&&key[i]<='z'){
            raw_address += (unsigned int)(key[i]-'a')*pow;
        }else{
            raw_address += (unsigned int)(key[i])*pow;
        }
        pow *= ALPHABLET;
    }

    address = raw_address %HASHSIZE;

    return address;
}
/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m)
{
    mvmcell *temp;
    char *str;
    int offset = 0;
    int i;
    if(m == NULL){
        return NULL;
    }
    str = (char *)calloc(1,sizeof(char));
    for(i=0;i<HASHSIZE;i++){
        if(m->array[i].address != NULLKEY){
            temp = m->array[i].next;
            while(temp != NULL){
                str = (char *)realloc(str,(strlen(str)+strlen(temp->key)\
                +strlen(temp->data)+strlen("[]() "))*sizeof(char)+sizeof(char));
                offset += sprintf(str+offset,"[%s](%s) ",temp->key,temp->data);
                temp = temp->next;
            }
        }
    }
    return str;
}

/* Remove one key/value */
void mvm_delete(mvm* m, char* key)
{
    int address;
    mvmcell *current;
    mvmcell *temp;
    if(m ==NULL || key ==NULL){
        return;
    }
    address = hash_function(key);
    if(m->array[address].address == NULLKEY){
        return;
    }
    current = m->array[address].next;
    if(strcmp(current->key,key)==0){
        m->array[address].next =current->next;
        m->numkeys--;
        free_one_cell(&current);
        return;
    }
    while(current->next != NULL && strcmp(current->next->key,key)!=0){ /*cannot exchange*/
        current = current->next;
    }
    if(current->next == NULL){
        return;
    }
    temp = current->next;
    current->next = current->next->next;
    free_one_cell(&temp);
    m->numkeys--;
    return;
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
    int address;
    mvmcell *current;
    if(m==NULL||key==NULL){
        return NULL;
    }
    address = hash_function(key);
    if(m->array[address].address == NULLKEY){
        return NULL;
    }
    current = m->array[address].next;
    while(current !=NULL && strcmp(current->key,key) != 0){
        current =current->next;
    }
    if(current ==NULL){
        return NULL;
    }
    return current->data;

}

/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n)
{
    char **a;
    int index = 0;
    int address;
    mvmcell *current;
    if(m == NULL ||key == NULL || n == NULL){
        return NULL;
    }
    *n = 0;
    address = hash_function(key);
    if(m->array[address].address == NULLKEY){
        return NULL;
    }

    a = (char **)malloc(sizeof(char *));
    current = m->array[address].next;
    while(current != NULL){
        if(strcmp(current->key,key)==0){
            (*n)++;
            a = (char **)realloc(a,(*n)* sizeof(char *));
            a[index] = current->data;
            index++;
        }
        current = current->next;
    }
    return a;
}

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
/* Free & set p to NULL*/
void mvm_free(mvm** p)
{
    int i;
    mvm *a;
    if( p ==NULL || *p == NULL){
        return;
    }
    a = *p;
    for(i=0;i<HASHSIZE;i++){
        if(a->array[i].address != NULLKEY){
            free_linked_list(&(a->array[i].next));
        }
    }
    free(a);
    *p =NULL;
}

