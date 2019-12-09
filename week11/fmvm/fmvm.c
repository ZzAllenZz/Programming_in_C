#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "fmvm.h"

#define NULLKEY -1
#define ALPHABLET 26

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
    mvmcell *temp;
    if( m==NULL ||key ==NULL || data == NULL) {
        return;
    }
    address = hash_function(key);
    if(m->array[address].address == NULLKEY){
        m->array[address].data = (char *)malloc(sizeof(char)*strlen(data)+sizeof(char));
        m->array[address].key= (char *)malloc(sizeof(char)*strlen(key)+sizeof(char));
        m->array[address].address = address;
        strcpy(m->array[address].key,key);
        strcpy(m->array[address].data,data);
        m->numkeys++;
        return;
    }
    new_cell = (mvmcell*)malloc(sizeof(mvmcell));
    new_cell->data = (char *)malloc(sizeof(char)*strlen(data)+sizeof(char));
    new_cell->key = (char *)malloc(sizeof(char)*strlen(key)+sizeof(char));
    new_cell->address = address;
    new_cell->next = NULL;
    strcpy(new_cell->key,key);
    strcpy(new_cell->data,data);
    m->numkeys++;
    if(m->array[address].next == NULL ){
        m->array[address].next = new_cell;
    }else{
        temp = m->array[address].next;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_cell;
    }
}


int hash_function(char *key)
{
    int len = strlen(key);
    int i;
    int address = 0;
    for(i=0;i<len;i++){
        address += (key[i]-96)*(int)pow((double)ALPHABLET,(double)i);

    }

    address = address %HASHSIZE;

    return address;
}
/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m)
{
    mvmcell *temp;
    char *str = (char *)calloc(1,sizeof(char));
    int offset = 0;
    int i;
    if(m == NULL){
        return NULL;
    }

    for(i=0;i<HASHSIZE;i++){
        if(m->array[i].address != NULLKEY){
            str = (char *)realloc(str,(strlen(str)+strlen(m->array[i].key)+strlen(m->array[i].data)\
            +strlen("[]() "))*sizeof(char)+sizeof(char));
            offset += sprintf(str+offset,"[%s](%s) ",m->array[i].key,m->array[i].data);
            temp = m->array[i].next;
            while(temp!=NULL){
                str = (char *)realloc(str,(strlen(str)+strlen(temp->key)+strlen(temp->data)\
                +strlen("[]() "))*sizeof(char)+sizeof(char));
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
    mvmcell *temp;
    if(m ==NULL || key ==NULL){
        return;
    }
    address = hash_function(key);
    if(m->array[address].address == NULLKEY){
        return;
    }
    m->numkeys--;
    if(strcmp(m->array[address].key,key)==0){
        free(m->array[address].key);
        free(m->array[address].data);
        if(m->array[address].next==NULL){
            m->array[address].address = NULLKEY;
            return;
        }
        temp = m->array[address].next;
        m->array[address].next = m->array[address].next->next;
        m->array[address].key = m->array[address].next->key;
        m->array[address].data = m->array[address].next->data;
        free(temp);
        return;
    }




}

/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key)
{
    if(m!=NULL&&key!=NULL){
        int address;
        int count =0;
        address = hash_function(key);
        while(strcmp(m->array[address].key,key)!=0 && count <= m->numkeys){
                address = (address+1)%HASHSIZE;
                count++;
        }
        if(count> m->numkeys){
            return  NULL;
        }
        return m->array[address].data;
    }
    return NULL;
}

/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n)
{
    if(m !=NULL&& key!=NULL&&n != NULL){
        char **a;
        int i= 0;
        int address;
        int count = 0;

        *n = 0;
        a = (char **)calloc(2000, sizeof(char *));
        for(i=0;i<2000;i++){
            a[i] =(char *) calloc(1000, sizeof(char));
        }
        address = hash_function(key);
        i=0;
        while(count<=HASHSIZE){
            if(strcmp(m->array[address].key,key)==0){
                strcpy(a[i],m->array[address].data);
                i++;
                (*n)++;
            }
            address = (address+1) % HASHSIZE;
            count++;
        }
        return  a;
    }
    return NULL;
}

/*void free_linked_list(mvmcell *head)
{
    if(head !=NULL){
        mvmcell *current = head;
        mvmcell *previous = NULL;
        while(current->next != NULL){
            previous = current;
            current = current->next;
            free(previous->next);
            free(previous->key);
            free(previous->data);
        }
        free(previous);
        free(current);
    }
}*/
/* Free & set p to NULL*/
void mvm_free(mvm** p)
{
/*    free_linked_list((*p)->head);
    free((*p)->head);
    free(*p);*/
    *p =NULL;
}

