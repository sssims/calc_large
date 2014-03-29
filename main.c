/* Shane Sims
 * <EMAIL>
 */

#include <stdio.h>
#include "calc_large.h"

int main (void) 
{
   big_int bi_0 = new__big_int("45");
   big_int bi_1 = new__big_int("-17");

   big_int bi_2 = add__big_int(bi_0, bi_1);
    
   print__big_int(bi_0);
   printf("\n+\n");
   print__big_int(bi_1);
   printf("\n=\n");
   print__big_int(bi_2);
   printf("\n\n");


   big_int product = mult__big_int(bi_0, bi_1);

   print__big_int(bi_0);
   printf("\n*\n");
   print__big_int(bi_1);
   printf("\n=\n");
   print__big_int(product);
   printf("\n");

   printf("comp ");
   print__big_int(bi_0);
   printf(" and ");
   print__big_int(bi_1);
   printf(" = %d\n", cmp__big_int(bi_0, bi_1));

   free__big_int(product);
   free__big_int(bi_0);
   free__big_int(bi_1);
   free__big_int(bi_2);

   return 0;
}
