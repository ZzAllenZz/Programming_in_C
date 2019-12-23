#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "set.h"

set* set_init(void)
{
    set *s = (set *)calloc(1,sizeof(set));
    s->ua = arr_init();
    s->sz = 0;
    return s;
}

/* Create new set, copied from another */
set* set_copy(set* s)
{
    int i;
    set *new_set ;
    if(s ==NULL){
        return NULL;
    }
    new_set = set_init();
    new_set->sz = s->sz;
    for(i=0;i<s->sz;i++){
        arr_set(new_set->ua,i,s->ua->data[i]);
    }
    return new_set;
}

/* Create new set, copied from an array of length n*/
set* set_fromarray(arrtype* a, int n)
{
    int i;
    int j;
    int k;
    int size = n;
    set *new_set ;
    new_set = set_init();
    if(a ==NULL){
        return new_set;
    }
    for (i=0;i<n-1;i++) {
        for(j=i+1;j<n;j++){
            if(a[i]==a[j]){
                for(k = j;k<n-1;k++){
                    a[j] = a[j+1];
                }
                size--;
            }
        }
    }
    new_set->sz =size;
    for(i=0;i<size;i++){
        arr_set(new_set->ua,i,a[i]);
    }

    return new_set;
}

/* Add one element into the set */
void set_insert(set* s, arrtype l)
{
    int i;
    int size;
    if(s ==NULL){
        s = set_init();
        s->ua->data[0] = l;
        s->sz++;
        return;
    }
    if(s->sz==0){
        s->ua->data[0] = l;
        s->sz++;
        return;
    }
    size= s->sz;

    for(i=0;i<size;i++){
        if(s->ua->data[i] ==l){
            return;
        }
    }
    arr_set(s->ua,s->sz,l);
    s->sz++;
}

/* Return size of the set */
int set_size(set* s)
{
    if(s == NULL){
        return 0;
    }
    return s->sz;
}

/* Returns true if l is in the array, false elsewise */
int set_contains(set* s, arrtype l)
{
    int i;
    if(s==NULL||s->sz==0){
        return 0;
    }
    for(i=0;i<s->sz;i++){
        if(s->ua->data[i] == l){
            return 1;
        }
    }
    return 0;
}

/* Remove l from the set (if it's in) */
void set_remove(set* s, arrtype l)
{
    int i;
    int j;
    if(s== NULL||s->sz==0){
        return;
    }
    for(i=0;i<s->sz;i++){
        if(s->ua->data[i]== l){
            for(j=i;j<s->sz-1;j++){
                s->ua->data[j] = s->ua->data[j+1];
            }
            s->sz--;
            return ;
        }
    }
    return ;
}

/* Remove one element from the set - there's no
   particular order for the elements, so any will do */
arrtype set_removeone(set* s){
    int size;
    if(s==NULL ||s->sz == 0){
        ON_ERROR("Empty Set cannot remove one!\n");
    }
    size = s->sz;
    s->sz--;
    return s->ua->data[size-1];
}
/* Operations on 2 sets */
/* Create a new set, containing all elements from s1 & s2 */
set* set_union(set* s1, set* s2){
    set *new_set;
    int i;
    if(s1==NULL &&s2 == NULL){
        return set_init();
    }
    if(s1 ==NULL){
        new_set = set_copy(s2);
        return new_set;
    }
    if(s2== NULL){
        new_set = set_copy(s1);
        return new_set;
    }
    new_set = set_copy(s1);
    for(i=0;i<s2->sz;i++){
        set_insert(new_set,s2->ua->data[i]);
    }
    return new_set;
}

/* Create a new set, containing all elements in both s1 & s2 */
set* set_intersection(set* s1, set* s2)
{
    set *new_set;
    int i;
    if(s1 == NULL ||s2 ==NULL){
        return set_init();
    }
    new_set = set_init();
    for(i=0;i<s2->sz;i++){
        if(set_contains(s1,s2->ua->data[i])==1){
            set_insert(new_set,s2->ua->data[i]);
        }
    }
    return new_set;
}

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void set_free(set** s)
{
    if(s !=NULL){
        set *a = *s;
        arr_free(&(a->ua));
        free(a);
        *s = NULL;
    }

    return;
}

