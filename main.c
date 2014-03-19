/* Shane Sims
 * <EMAIL>
 */

#include <stdio.h>
#include "calc_large.h"

int main (void) 
{
   big_int bi_0 = new__big_int("3048570348503475013050347508132475083247501834750");
   big_int bi_1 = new__big_int("20386028356708237560823576082357608275362038567");

   big_int bi_2 = add__big_int(bi_0, bi_1);
    
   print__big_int(bi_0);
   printf("\n+\n");
   print__big_int(bi_1);
   printf("\n=\n");
   print__big_int(bi_2);
   printf("\n");



   free__big_int(bi_0);
   free__big_int(bi_1);
   free__big_int(bi_2);

   return 0;
}
