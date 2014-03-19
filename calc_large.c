/* Shane Sims
 *
 * C source for calc_large
 *
 * KNOWN ISSUES
 *    - Leading 0's: only remove at print? or periodically remove?
 *       - Must be more often than at print b/c of prepend. 
 *         Call to prepend fatal if leading zeroes exist. 
 *       - Trying to guarentee no leading zeroes when returning 
 *         from function calls.
 *    - Handling 1 digit numbers troublesome.
 *       - Problem comes from having default value 0.
 *         Must append a digit then erase the zero to acheive
 *         expected value. 
 *       - Fix could be to have new__big_int() take an int *
 *         instead of char *. 
 *            - However, this would make calling new__big_int with
 *              a literal impossible. A client would have to fill an
 *              int * then pass it to new__big_int. The ability to call
 *              new__big_int with a string literal is nice.
 *            
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

void kill_lead_zeroes__big_int(big_int num)
{
   if(num->length == 1)
      return;

   digit handle = num->front;

   while(handle->actual == 0) {
      digit temp = handle;
      handle = handle->next;
      free(temp);   
      num->length--;
      if(num->length == 1) 
         break;
   }

   num->front = handle;
   num->front->previous = NULL;

   return;
}

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
   kill_lead_zeroes__big_int(num);

   digit handle = num->front;
   for(int count = 0; count < num->length; count++) {
      printf("%d", handle->actual);
      handle = handle->next;
   }
   return;
}

void free__big_int(big_int num)
{
   digit handle = num->front;
   for(int count = 0; count < num->length; count++) {
      digit temp = handle;
      handle = handle->next;
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
   zero->actual = (int)(*num_string++ - 48);
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
   big_int sum = new__big_int("0");
   digit handle_0 = num_0->rear;
   digit handle_1 = num_1->rear;

   /* Deal with first digit */
   int curr_digit = handle_0->actual + handle_1->actual;
   int carry = 0;

   handle_0 = handle_0->previous;
   handle_1 = handle_1->previous;

   if(curr_digit >= 10) {
      carry = 1;
      curr_digit = curr_digit % 10;
   }

   append_digit(sum, curr_digit);
   kill_lead_zeroes__big_int(sum);
   /* Deal with second and further digits */

   while(1) {
      if(handle_0 == NULL && handle_1 == NULL) break;
      if(handle_0 == NULL) {
         curr_digit = handle_1->actual + carry;
         handle_1 = handle_1->previous;
      } else if(handle_1 == NULL) {
         curr_digit = handle_0->actual + carry;
         handle_0 = handle_0->previous;
      } else { 
         curr_digit = handle_0->actual + handle_1->actual + carry;
         handle_0 = handle_0->previous;
         handle_1 = handle_1->previous;
      }
      if(curr_digit >= 10) {
         carry = 1;
         curr_digit = curr_digit % 10;
      } else {
         carry = 0;
      }
      prepend_digit(sum, curr_digit);
   }

   if(carry == 1)
      prepend_digit(sum, 1);
 
   return sum;
}

big_int mult__big_int(big_int num_0, big_int num_1)
{
   big_int full_product = new__big_int("0");
   big_int line_product = new__big_int("0");
   digit handle_0 = num_0->rear;
   digit handle_1 = num_1->rear;
  
   /* Deal with first digit */ 
   int curr_product = handle_0->actual * handle_1->actual;
   int curr_digit   = curr_product % 10;
   int carry        = (curr_product - curr_digit) / 10;
   int line         = 0;

   append_digit(line_product, curr_digit);
   kill_lead_zeroes__big_int(line_product);

   handle_1 = handle_1->previous;

   /* Deal with second and further digits */

   while(1) {
      if(handle_1 == NULL) {
         handle_0 = handle_0->previous;
         handle_1 = num_1->rear;

         if(carry != 0) 
            prepend_digit(line_product, carry);

         carry = 0;
         line++;

         big_int temp = add__big_int(full_product, line_product);
         free__big_int(full_product);
         free__big_int(line_product);
         full_product = temp;

         if(handle_0 == NULL) break;

         line_product = new__big_int("0"); 
         for(int i = 0; i < line - 1; i++) {
            prepend_digit(line_product, 0);
         } 
      }
      curr_product = (handle_0->actual * handle_1->actual) + carry;
      curr_digit   = curr_product % 10;
      carry        = (curr_product - curr_digit) / 10;
       
      prepend_digit(line_product, curr_digit);

      handle_1 = handle_1->previous;
   }

   return full_product;
}

