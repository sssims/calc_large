/* Shane Sims
 * <EMAIL>
 */

#include <stdio.h>
#include "calc_large.h"

int main (void) 
{
   big_int bi_0 = new__big_int("59245223948729492347298347924378792742356235624562456245624564562380234502834750823475037450823457203847508234750834750823745023874534057203572083576028576025760284576028457608245760284576028457608245762045768");
   big_int bi_1 = new__big_int("2127432934723749237492479283729837498273423462356245624562456245624563456254610234858045708137450814750813745083475081347501834750813750183750839024561465109475601956013465104956109345610934765103957610345");

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

   free__big_int(product);
   free__big_int(bi_0);
   free__big_int(bi_1);
   free__big_int(bi_2);

   return 0;
}
