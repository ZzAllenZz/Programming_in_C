#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fmvm.h"

mvm *mvm_init(void)
{
    mvm *m = (mvm *)calloc(1,sizeof(mvm));
    if(m==NULL){
        ON_ERROR("Failed to allocate for m...\n");
    }
    m->table_size = DEFUALT_SIZE;
    m->array = (mvmcell *)malloc(m->table_size*sizeof(mvmcell));
    array_init(m->array,m->table_size);
    m->numkeys = 0;
    return m;
}

void array_init(mvmcell *array,int table_size)
{
    int i;
    
    for(i=0;i<table_size;i++){
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

int mvm_table_size(mvm *m)
{
    if(m==NULL){
        return 0;
    }
    return m->table_size;
}

/* Insert one key/value pair */
void mvm_insert(mvm* m, char* key, char* data)
{
    int address;
    mvmcell *new_cell;
    if( m==NULL ||key ==NULL || data == NULL) {
        return;
    }
    address = hash_function(key,m->table_size);
    if(m->array[address].address ==NULLKEY){
        m->array[address].address = address;
    }
    new_cell = (mvmcell*)malloc(sizeof(mvmcell));
    new_cell->key = (char *)malloc(sizeof(char)*strlen(key)+sizeof(char));
    new_cell->data = (char *)malloc(sizeof(char)*strlen(data)+sizeof(char));
    if(new_cell->data== NULL || new_cell->key == NULL){
        ON_ERROR("Failed to allocate...\n");
    }
    new_cell->address = address;
    strcpy(new_cell->key,key);
    strcpy(new_cell->data,data);
    new_cell->next = m->array[address].next;
    m->array[address].next =new_cell;
    m->numkeys++;
    if((double)m->numkeys/m->table_size >= RESIZE_THRESHOLD){
        resize_hash(m);
    }
}


int hash_function(char *key,int table_size)
{
    int len = strlen(key),i,address;
    unsigned int pow =1;
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
    address = raw_address % table_size;
    return address;
}

int find_next_prime(int current_size)
{
    int flag = 1;
    int prime = current_size;
    int i;
    while (flag == 1){
        flag = 0;
        prime++;
        for(i=2;i<prime/2;i++){
            if(prime % i == 0){
                flag =1;
            }
        }
    }
    return prime;
}

/*Main idea:
 *1.Create a new_m, and copy the data from m->array to new_m->array;
 *2.Free m->array;
 *3.Let m->array points to new_m->array's location;
 * */
void resize_hash(mvm *m)
{
    mvm *new_m;
    int i;
    mvmcell *temp;
    new_m = (mvm *)malloc(sizeof(mvm));
    if(new_m==NULL){
        ON_ERROR("Failed to allocate for new_m...\n");
    }
    new_m->table_size = find_next_prime(m->table_size*DOUBLE);
    new_m->array = (mvmcell *)malloc(sizeof(mvmcell)*new_m->table_size);
    if(new_m->array==NULL){
        ON_ERROR("Failed to allocate for new_m->array...\n");
    }
    new_m->numkeys = 0;
    array_init(new_m->array,new_m->table_size);
    for(i=0;i<m->table_size;i++){
        if(m->array[i].address != NULLKEY){
            temp = m->array[i].next;
            while(temp != NULL){
                transfer_mvmcell(temp,new_m);
                temp = temp->next;
            }
            temp = m->array[i].next;
            free_linked_list(&temp); /*free current sub-linked list*/
        }
    }
    m->numkeys =  new_m->numkeys;
    m->table_size = new_m->table_size;
    free(m->array);
    m->array = new_m->array;
    free(new_m);
}
/*Transfer m's mvmcell's data into new_m
 * it include:
 * 1.address;
 * 2.data;
 * 3.key;
 * */
void transfer_mvmcell(mvmcell *temp,mvm *new_m)
{
    int new_address;
    mvmcell* new_cell;
    new_address = hash_function(temp->key,new_m->table_size);
    if(new_m->array[new_address].address == NULLKEY){
        new_m->array[new_address].address = new_address;
    }
    new_cell = (mvmcell*)malloc(sizeof(mvmcell));
    if(new_cell == NULL ){
        ON_ERROR("Failed to allocate for new_cell...\n");
    }
    new_cell->data = (char *)malloc(sizeof(char)*strlen(temp->data)+sizeof(char));
    new_cell->key = (char *)malloc(sizeof(char)*strlen(temp->key)+sizeof(char));
    if(new_cell->data== NULL || new_cell->key == NULL){
        ON_ERROR("Failed to allocate...\n");
    }
    strcpy(new_cell->key,temp->key);
    strcpy(new_cell->data,temp->data);

    new_cell->address = new_address;
    new_cell->next = new_m->array[new_address].next;
    new_m->array[new_address].next =new_cell;
    new_m->numkeys++;
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
    for(i=0;i<m->table_size;i++){
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
    address = hash_function(key,m->table_size);
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
    while(current->next != NULL && strcmp(current->next->key,key)!=0){
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


/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key)
{
    int address;
    mvmcell *current;
    if(m==NULL||key==NULL){
        return NULL;
    }
    address = hash_function(key,m->table_size);
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
    address = hash_function(key,m->table_size);
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
    for(i=0;i<a->table_size;i++){
        if(a->array[i].address != NULLKEY){
            free_linked_list(&(a->array[i].next));
        }
    }
    free(a->array);
    free(a);
    *p =NULL;
}

