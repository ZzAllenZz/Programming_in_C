
#include<stdio.h>
#include<stdlib.h>

#define HASHSIZE 12
#define NULLKEY  -1
typedef struct {
    int *array;
    int size;
} HashTable;

void init_hashtable(HashTable *H);
void insert_hash(HashTable *H,int key);
int search_hash(HashTable *H, int key, int *addr);
int hash_function(int key);

int main(void)
{
    HashTable *H = (HashTable *)malloc(sizeof(HashTable));
    int *addr = (int *)malloc(sizeof(int));
    int insert_key;
    int search_key;
    int search_result;

    unsigned int what;
    int how;

    unsigned int a = 1000;
    int b = -1;

    a = (unsigned int) b;
    printf("a is %u",a);
    return 0;
    what = 1;
    printf("what is %d\n",what);
    what = -12;
    printf("what is %d\n",what);
    printf("what is %u\n",what);
/*    what +=15;*/
    printf("what is %d\n",what);
    printf("what is %u\n",what);


     how  = -15;
    printf("how is %d\n",how);

    how = what %7;
    printf("how is %d\n",how);

    init_hashtable(H);
    printf("-----store in hashtable-----\n");
    printf("enter the data you want to store(-1 for exit!):\n");
    while(1){
        scanf("%d",&insert_key);
        if(insert_key==-1){
            break;
        }
        insert_hash(H,insert_key);
    }

    printf("store finished\n");
    printf("enter the key you want to search:\n");
    while(1){
        scanf("%d",&search_key);
        if(search_key==-1){
            break;
        }
        search_result = search_hash(H,search_key,addr);
        if(search_result==1){
            printf("find key,address is  %d\n",*addr);
        }else{
            printf("cannot find the key!\n");
        }
    }
    return 1;
}

/*初始化HashTable*/
void init_hashtable(HashTable *H)
{
    int i;
    H->array = (int *)malloc(HASHSIZE*sizeof(int));
    if(!H){
        printf("Failed to allocate....\n");
        exit(EXIT_FAILURE);
    }
    H->size = HASHSIZE;
    for(i=0;i<HASHSIZE;i++){
        H->array[i] =NULLKEY;
    }
}

/*散列函数（哈希函数）----除留余数法*/
int hash_function(int key)
{
    return key % HASHSIZE;
}

/*插入关键字key到哈希表中*/
void insert_hash(HashTable *H,int key)
{
    int addr;
    addr = hash_function(key);
    while(H->array[addr] != NULLKEY){ /*如果不为NULLKEY,则说明出现了冲突*/
        addr = (addr+1) % HASHSIZE; /*线性探测法*/
    }
    H->array[addr] = key;
}

/*寻找关键字*/
int search_hash(HashTable *H, int key, int *addr)
{
    *addr = hash_function(key);
    while(H->array[*addr] != key){

        *addr = (*addr+1) % HASHSIZE; /*线性探测法*/
        if(H->array[*addr] == NULLKEY || *addr == hash_function(key)){
            /*if  *addr == hash_function(key),说明绕了一圈，还没找到，所以不存在！*/
            return 0;
        }
    }
    return 1;/*存在！*/
}