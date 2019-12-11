/* Multi-Value Map ADT : via Linked List
   Both key & data are strings (char*) 
   Multiple Keys may be stored
   New data is inserted at the front of the list:
   O(1) insertion
   O(n) search
   O(n) deletion
*/

/* Error that can't be ignored */
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
#define HASHSIZE 314377
struct mvmcell {
   char* key;
   char* data;
   int address;
   struct mvmcell *next;
};
typedef struct mvmcell mvmcell;

struct mvm {
   mvmcell array[HASHSIZE];
   int numkeys;
};
typedef struct mvm mvm;



mvm* mvm_init(void);
/* Number of key/value pairs stored */
int mvm_size(mvm* m);
/* Insert one key/value pair */
void mvm_insert(mvm* m, char* key, char* data,int *time);
/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m);
/* Remove one key/value */
void mvm_delete(mvm* m, char* key);
/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key,int *time);
/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n,int *time);
/* Free & set p to NULL */
void mvm_free(mvm** p);
