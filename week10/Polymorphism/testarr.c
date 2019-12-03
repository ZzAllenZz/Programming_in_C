#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "arr.h"

int main(void)
{

   arr *a;
   printf("Basic Array Tests ... Start\n");
   /* Set up empty array */
   a = arr_init();
   assert(a != NULL);

   /* Some simple sets & gets */

   /* Like a[0]  = 1 */
   arr_set(a, 0, 1);
   assert(arr_get(a, 0) == 1);
   /* Like a[1]  = 2 */
   arr_set(a, 1, 2);
   assert(arr_get(a, 1) == 2);
   /* Force a resize/realloc (depending on initial size) */
   arr_set(a, 32, 17);
   assert(arr_get(a, 32) == 17);
   /* Huge (re)alloc */
   /*arr_set(a, 512000, 3);
   assert(arr_get(a, 512000) == 3);
    */
   arr_set(a,52,100);
    printf("the array[52] :%d ",arr_get(a,52));
    printf("the array[31]: %d",arr_get(a,31));
    printf("the array[51]: %d",arr_get(a,51));
   /* Free it all */
   arr_free(&a);
   assert(a==NULL);
   printf("Basic Array Tests ... Stop\n");

   return 0;
}
