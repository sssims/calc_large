/* Shane Sims
 *
 * C source for calc_large
 *
 * KNOWN ISSUES
 *    - Leading 0's: only remove at print? or periodically remove?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc_large.h"

typedef struct digit_struct * digit;

struct digit_struct {
   int actual;
   digit next;
   digit previous;
};

struct big_int__struct {
   int length;
   digit front;
   digit rear;
};

void append_digit(big_int num, int appendage)
{
   digit new_d = malloc(sizeof(digit));
   new_d->actual = appendage;
   new_d->next = NULL;
   new_d->previous = num->rear;
   num->rear->next = new_d;
   num->rear = new_d;
   num->length++;

   return;
}

void print__big_int(big_int num)
{
   digit print_handle = num->front;
   for(int count = 0; count < num->length; count++) {
      printf("%d", print_handle->actual);
      print_handle = print_handle->next;
   }
   printf("\n");
   return;
}

void free__big_int(big_int num)
{
   digit free_handle = num->front;
   for(int count = 0; count < num->length; count++) {
      digit temp = free_handle;
      free_handle = free_handle->next;
      free(temp);
   }
   free(num);
   return;
}

big_int new__big_int(char * num_string)
{
   if(strcmp("", num_string) == 0 || num_string == NULL) {
      return NULL;
   }

   big_int new_bi = malloc(sizeof(struct big_int__struct)); 
   new_bi->length = 0;  

   digit zero = malloc(sizeof(digit));
   zero->actual = 0;
   zero->next = NULL;
   zero->previous = NULL;

   new_bi->front = zero;
   new_bi->rear  = zero;
   new_bi->length++;

   while(*num_string != '\0') {
      /* subtract ASCII offset here */
      append_digit(new_bi, (int)(*num_string++) - 48);
   }
   print__big_int(new_bi);
 
   return new_bi; 
}
