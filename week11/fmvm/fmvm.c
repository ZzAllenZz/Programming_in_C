#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "fmvm.h"
#define HASHSIZE 101
#define NULLKEY -1
#define ALPHABLET 26
/*question:
 * 1.the max size of data and key?
 * 2.the max map? because print str and multiplesearch str !!!
 * */
int hash_function(char *key);

mvm *mvm_init(void)
{
    mvm *m = (mvm *)calloc(1,sizeof(mvm));
    int i;
    m->array = (mvmcell *)malloc(HASHSIZE*sizeof(mvmcell));
    m->numkeys = 0;
    for(i=0;i<HASHSIZE;i++){
        m->array[i].key = (char *)calloc(50,sizeof(char));
        m->array[i].data = (char *)calloc(50,sizeof(char));
        m->array[i].address = NULLKEY;
    }
    return m;
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
    if(m!=NULL&&key !=NULL && data != NULL){
       int address;
       address = hash_function(key);
       while(strcmp(m->array[address].key,key)==0){
            address = (address+ 1)%HASHSIZE;
       }
       strcpy(m->array[address].key,key);
       strcpy(m->array[address].data,data);
       m->array[address].address = address;
       m->numkeys++;
    }
}

int hash_function(char *key)
{
    int len = strlen(key);
    int i;
    int address = 0;
    for(i=0;i<len;i++){
        address += (key[i]-'a')*(int)pow((double)ALPHABLET,(double)i);

    }

    address = address %HASHSIZE;

    return address;
}
/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m)
{
    if(m != NULL){
        int i;
        int offset = 0;
        int count = 0;
        int address;
        char *str = (char *)malloc(10000*sizeof(char));
        for(i=0;i<HASHSIZE;i++){
            if(m->array[i].address != NULLKEY){

                address = m->array[i].address;
                offset += sprintf(str+offset,"[%s](%s) ",m->array[address].key,m->array[address].data);
                count++;

            }
            if(count == m->numkeys){
                return  str;
            }

        }

        return str;
    }
    return  NULL;

}

/* Remove one key/value */
void mvm_delete(mvm* m, char* key)
{
    if(m!=NULL&& key != NULL){
        int address;
        int count = 0;
        address = hash_function(key);
        while(strcmp(m->array[address].key,key)!=0&& count <=HASHSIZE){
            address = (address+1)%HASHSIZE;
            count++;
        }
        if(count >HASHSIZE){
            return;
        }
        free(m->array[address].key);
        free(m->array[address].data);
        m->numkeys--;
        m->array->address = NULLKEY;
        m->array[address].data = (char *)calloc(50,sizeof(char));
        m->array[address].key = (char *)calloc(50,sizeof(char));
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

