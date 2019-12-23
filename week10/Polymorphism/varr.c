#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "varr.h"

/* Default physical size of array -
   no need to share this */
#define ARRDEFSZ 32

/* Creates the empty array */
arr* arr_init(int elementsize)
{
    arr * new_one = (arr *)calloc(1,sizeof(arr));
    if(new_one==NULL){
        ON_ERROR("Creation of Array Failed..\n");
    }
    new_one->elsz = elementsize;
    new_one->pz = ARRDEFSZ;
    new_one->data = calloc(ARRDEFSZ,sizeof(elementsize));
    if(new_one->data == NULL){
        ON_ERROR("Creation of Array Failed..\n");
    }
    return  new_one;
}

/* Similar to l[n] = i, safely resizing if required */
/* data from v is copied into array */
void arr_set(arr *l, int n, void* v)
{
    if (n < 0){
        ON_ERROR("Array accessed with negative index ...\n");
    }
    if(n >= l->pz){
        l->data = realloc(l->data, l->elsz*(1+n));
        if(l->data == NULL){
            ON_ERROR("Resize of Array Failed.\n");
        }
        l->pz = n+1;
    }

    memcpy(((char *)l->data+n*l->elsz),v, l->elsz);

}

/* Similar to = l[n] */
/* pointer into array is returned */
void* arr_get(arr *l, int n)
{
    if((n >= l->pz) || (n < 0)){
        ON_ERROR("Array read out of bounds\n");
    }
    return ((char *)l->data+ l->elsz*n);
}

/* Clears all space used, and sets pointer to NULL */
void arr_free(arr **l)
{
    arr *temp = *l;
    free(temp->data);
    free(temp);
    *l = NULL;
}

