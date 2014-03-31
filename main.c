/* Shane Sims
 * <EMAIL>
 */

#include <stdio.h>
#include "calc_large.h"

int main (int argc, char **argv) 
{
   if(argc != 3) {
      fprintf(stderr,"Provide 2 integers for big_int arithmatic\n");
      return 1;
   }

   big_int bi_0 = new__big_int(argv[1]);
   big_int bi_1 = new__big_int(argv[2]);

   printf("bi_0 = ");
   print__big_int(bi_0);
   printf("\n");
   printf("bi_1 = ");
   print__big_int(bi_1);
   printf("\n\n");

   big_int sum = add__big_int(bi_0, bi_1);
    
   printf("sum = ");
   print__big_int(sum);
   printf("\n\n");

   free__big_int(sum);

   big_int product = mult__big_int(bi_0, bi_1);

   printf("product = ");
   print__big_int(product);
   printf("\n\n");

   free__big_int(product);

   printf("compare ");
   print__big_int(bi_0);
   printf(" and ");
   print__big_int(bi_1);
   printf(" = %d\n\n", cmp__big_int(bi_0, bi_1));

   big_int diff = sub__big_int(bi_0, bi_1);

   printf("difference = ");
   print__big_int(diff);
   printf("\n\n");
 
   free__big_int(diff);

   big_int mod = mod__big_int(bi_0, bi_1);

   printf("modulo = ");
   print__big_int(mod);
   printf("\n\n");

   free__big_int(mod);
 
   big_int quo = div__big_int(bi_0, bi_1);

   printf("quotient = ");
   print__big_int(quo);
   printf("\n\n");
 
   free__big_int(quo);

   free__big_int(bi_0);
   free__big_int(bi_1);

   return 0;
}
