#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "calc_large.h"

big_int lowest_devisor(big_int num)
{ 
   int length = 0;

   big_int zero = new__big_int("0");
   big_int one  = new__big_int("1");
   big_int i    = new__big_int("2");
   while(cmp__big_int(i, num) < 0) {
      big_int mod = mod__big_int(num, i);
      if(cmp__big_int(mod, zero) == 0) {
         free__big_int(zero);
         free__big_int(one);
         free__big_int(mod);
         return i;
      }
      free__big_int(mod);

      big_int temp = i;
      i = add__big_int(i, one);
      free(temp);

      if(get_length__big_int(i) != length) {
         length = get_length__big_int(i);
         printf("%d\n", length);
      }
   }
   free__big_int(one);
   free__big_int(i);

   return zero;
}

int main(int argc, char **argv)
{
   if(argc != 2) {
      fprintf(stderr, "supply 1 number to find largest prime factor\n");
      exit(1);
   }
   big_int result = new__big_int(argv[1]);

   big_int zero = new__big_int("0");

   while(cmp__big_int(lowest_devisor(result), zero) != 0) {
      big_int factor = lowest_devisor(result);
      print__big_int(factor);
      printf("\n");
      big_int temp = result;
      result = div__big_int(result, factor);  
      printf("----\n");
      free(temp);
   }
   print__big_int(result);
   printf("\n");
   return 0;
}
