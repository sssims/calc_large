/* Shane Sims
 *
 * C source for calc_large
 *
 * KNOWN ISSUES
 *    - Leading 0's: only remove at print? or periodically remove?
 *       - Must be more often than at print b/c of prepend. 
 *         Call to prepend fatal if leading zeroes exist. 
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
   digit new_d = malloc(sizeof(struct digit_struct));
   new_d->actual = appendage;
   new_d->next = NULL;
   new_d->previous = num->rear;
   num->rear->next = new_d;
   num->rear = new_d;
   num->length++;

   return;
}

void prepend_digit(big_int num, int prependage)
// !!!! NOT WORKING. TOO FIX !!!!!!!!
{
   digit new_d = malloc(sizeof(struct digit_struct));
   new_d->actual = prependage;
   new_d->previous = NULL;
   new_d->next = num->front;
   num->front->previous = new_d;
   num->front = new_d;
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

   digit zero = malloc(sizeof(struct digit_struct));
   zero->actual = 0;
   zero->next = NULL;
   zero->previous = NULL;

   new_bi->front = zero;
   new_bi->rear  = zero;
   new_bi->length++;
 
   while(*num_string != '\0') {
      append_digit(new_bi, (int)(*num_string++) - 48);
   }

   return new_bi; 
}

big_int add__big_int(big_int num_0, big_int num_1)
{
   big_int sum = malloc(sizeof(struct big_int__struct));
   digit handle_0 = num_0->rear;
   digit handle_1 = num_1->rear;

   return sum;
}




