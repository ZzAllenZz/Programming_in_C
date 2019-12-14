/*
 *This programme uses hashing technique to fast searching;
 *
 *Two key points for this hashing:
 *1.the initial hash table size is 3 and
 *  when ratio(numkeys/table_size)>=0.6,resize(double it);
 *2.Using Separate Chaining to solve collision;
 *
 * Note:
 * 1.In the structure of mvm,there is a mvmcell *array;
 * 2.After malloc, each cell in this array is a mvmcell, not a mvmcell pointer;
 * 3.In order to easy coding and convenient operation, this cell did not
 *   store any key/value pair(treat each cell in array only as a head!);
 * 4.Anytime we get a new address, we insert a new mvmcell into m->array[address].next;
 *   (insert new items at heads);
 * 5.This inserting method is similar to the first question.
 * 6.structure seems like following:
 * mvm
 * -------------
 * |table_size |
 * |numkeys    |                                 mvmcell
 * |array      |------->-------------           -----------------
 * -------------        |     |*next|---------->|data|key| *next|----->NULL
 *                      |     |*next|---->NULL  -----------------
 *                            .
 *                            .
 *                            .
 *                      |     |*next|---->NULL
 *                      -------------
 *
 * Findings:
 * 1.link fmvm to homophones, we get, for map_one, every searching time is around 1.15;
 *   for map_two, every searching time is around 3.2, this is because
 *   we use multiple_search in map_two;
 * 2. the size of hash table extends from 3 to 350899;
 * */

/* Error that can't be ignored */
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

/*Hash table size begins from 3, and is always a prime */
#define DEFUALT_SIZE 3
/*NULLKEY means this address has not been used*/
#define NULLKEY -1
/*Used for calculating hash*/
#define ALPHABLET 26
/*when ratio beyonds 60%, resize hash table*/
#define RESIZE_THRESHOLD 0.6
/*Used to double size*/
#define DOUBLE 2


struct mvmcell {
   char* key;
   char* data;
   int address;
   struct mvmcell *next;
};
typedef struct mvmcell mvmcell;

struct mvm {
   mvmcell *array;
   int table_size;
   int numkeys;
};
typedef struct mvm mvm;


/*Previous Function, No changes*/
mvm* mvm_init(void);
/* Number of key/value pairs stored */
int mvm_size(mvm* m);
/* The size of current hash table */
int mvm_table_size(mvm *m);
/* Insert one key/value pair */
void mvm_insert(mvm* m, char* key, char* data);
/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m);
/* Remove one key/value */
void mvm_delete(mvm* m, char* key);
/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key);
/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n);
/* Free & set p to NULL */
void mvm_free(mvm** p);

/*New Functions added*/

void resize_hash(mvm *m);
void transfer_mvmcell(mvmcell *temp,mvm *new_m);
int find_next_prime(int current_size);
int hash_function(char *key,int table_size);

int mvm_table_size(mvm *m);
void array_init(mvmcell *array,int table_size);

/*Used to free one mvmcell in linked list */
void free_one_cell(mvmcell **cell);
/*Used to free the whole mvmcell's linked list */
void free_linked_list(mvmcell **head);




