#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mvm.h"

/*question:
 * 1.the max size of data and key?
 * 2.the max map? because print str and multiplesearch str !!!
 * */
mvm *mvm_init(void)
{
    mvm *m = (mvm *)calloc(1,sizeof(mvm));
    m->head = NULL; /*important!*/
    m->numkeys = 0;
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
    mvmcell *cell = (mvmcell *)calloc(1,sizeof(mvmcell));
    if(m==NULL||key == NULL||data ==NULL){
        return;
    }
    /*before strcpy, we must malloc or calloc to cell->data etc!*/
    cell->data = calloc(10, sizeof(char));
    cell->key = calloc(10, sizeof(char));
    strcpy(cell->key,key);
    strcpy(cell->data,data);
    cell->next = m->head;
    m->head = cell;
    m->numkeys++;
}

/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m)
{
    if(m != NULL){
        mvmcell *temp = m->head;
        char *str = (char *)malloc(100*sizeof(char));
        int offset = 0;
        while(temp != NULL){

           offset += sprintf(str+offset,"[%s](%s) ",temp->key,temp->data);
            temp = temp->next;
        }
        return str;
    }
    return  NULL;

}

/* Remove one key/value */
void mvm_delete(mvm* m, char* key)
{
    if(m!=NULL&& key != NULL){
        mvmcell *temp = m->head;
        if(strcmp(temp->key,key)==0){

            m->head = m->head->next;
            m->numkeys--;
            return;
        }

        while(temp->next != NULL && strcmp(temp->next->key,key)!=0){ /*why cannot exchange*/

            /*why we cannot exchange?
             * reason: we must firstly judge whether temp->next is null,
             * if it is null, strcmp(temp->next->key,key) is crashed!
             * */
            temp = temp->next;
        }
        if(temp->next == NULL){
            return;
        }
        temp->next = temp->next->next;
        m->numkeys--;
    }
}

/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key)
{
    if(m!=NULL&&key!=NULL){
        mvmcell *temp = m->head;

        while(temp != NULL && strcmp(temp->key,key)!=0 ){/*why???*/
            temp = temp ->next;

        }

        if(temp == NULL){

            return NULL;
        }


        return temp->data;
    }
    return NULL;
}

/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n)
{
    if(m !=NULL&& key!=NULL&&n != NULL){
        char **a;
        int i= 0;
        int index = 0;
        mvmcell *temp = m->head;
        *n = 0;
        a = (char **)calloc(20, sizeof(char *));
        for(i=0;i<20;i++){
            a[i] =(char *) calloc(10, sizeof(char));
        }
        while(temp!=NULL){
            if(strcmp(temp->key,key)==0){
                strcpy(a[index],temp->data);
                index ++;
                (*n)++;
            }
            temp = temp ->next;
        }
        return  a;
    }
    return NULL;
}

/* Free & set p to NULL */
void mvm_free(mvm** p)
{
    *p =NULL;
}

