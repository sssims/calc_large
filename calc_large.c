/* Shane Sims
 *
 * C source for calc_large
 *
 * NOTES -- None of the following effect the client.
 *
 *    - Leading 0's: only remove at print? or periodically remove?
 *       - Must be more often than at print b/c of prepend. 
 *         Call to prepend fatal if leading zeroes exist. 
 *       - Guarentee no leading zeroes when returning 
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

#define POSITIVE 0
#define NEGATIVE 1

typedef struct digit_struct * digit;

struct digit_struct {
   int actual;
   digit next;
   digit previous;
};

struct big_int__struct {
   int sign;
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

big_int new__big_int(char * num_string)
{
   if(strcmp("", num_string) == 0 || num_string == NULL) {
      return NULL;
   }

   big_int new_bi = malloc(sizeof(struct big_int__struct)); 
   new_bi->length = 0;  

   if(*num_string == '-') {
      num_string++;
      new_bi->sign = NEGATIVE;
   } else if(*num_string == '+') {
      num_string++;
      new_bi->sign = POSITIVE;
   } else {
      new_bi->sign = POSITIVE;
   }

   digit first_digit = malloc(sizeof(struct digit_struct));
   first_digit->actual = (int)(*num_string++ - 48);
   first_digit->next = NULL;
   first_digit->previous = NULL;

   new_bi->front = first_digit;
   new_bi->rear  = first_digit;
   new_bi->length++;
 
   while(*num_string != '\0') {
      append_digit(new_bi, (int)(*num_string++) - 48);
   }

   return new_bi; 
}

void print__big_int(big_int num)
{
   kill_lead_zeroes__big_int(num);

   digit handle = num->front;
   if(num->sign == NEGATIVE) {
      printf("-");
   }
   for(int count = 0; count < num->length; count++) {
      printf("%d", handle->actual);
      handle = handle->next;
   }
   return;
}

big_int add_abs__big_int(big_int num_0, big_int num_1)
/* Function adds the absolute value of (abs) num_0 to abs num_1.
 * This function ignores all negative signs, use accordingly. 
 * Use add__big_int() to add two big_ints safely.
 */
{
   big_int sum = new__big_int("0");
   digit handle_0 = num_0->rear;
   digit handle_1 = num_1->rear;

   /* Deal with first digit */
   int carry = 0;
   int curr_digit = handle_0->actual + handle_1->actual;

   if(curr_digit >= 10) {
      carry = 1;
      curr_digit = curr_digit % 10;
   }

   append_digit(sum, curr_digit);
   kill_lead_zeroes__big_int(sum);

   handle_0 = handle_0->previous;
   handle_1 = handle_1->previous;

   /* Deal with further digits */
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

big_int sub_abs__big_int(big_int num_0, big_int num_1)
/* subtracts absolute value of (abs) num_1 from abs num_0. Gives abs result.
 *
 * This function ignores all negative signs. Use accordingly. 
 * Use sub__big_int() two subtract 2 big_ints safely.
 */
{
   big_int diff = new__big_int("0");
 
   digit handle_0, handle_1;
 
   handle_0 = num_0->rear;
   handle_1 = num_1->rear;

   /* Deal with first digit */
   int carry, curr_digit;
   
   if(handle_0->actual >= handle_1->actual) {
      curr_digit = handle_0->actual - handle_1->actual;
      carry = 0;
   } else {
      curr_digit = 10 - (handle_1->actual - handle_0->actual);
      carry = 1;
   }
   
   append_digit(diff, curr_digit);
   kill_lead_zeroes__big_int(diff);

   handle_0 = handle_0->previous;
   handle_1 = handle_1->previous;

   /* Deal with further digits */
   while(1) {
      if(handle_0 == NULL) break;
      if(handle_1 == NULL) {
         curr_digit = handle_0->actual - carry;
         carry = 0;
         handle_0 = handle_0->previous;
      } else {
         if(handle_0->actual >= handle_1->actual + carry) {
            curr_digit = handle_0->actual - (handle_1->actual + carry);
            carry = 0;
         } else {
            curr_digit = 10 - ((handle_1->actual + carry) - handle_0->actual);
            carry = 1;
         }
         handle_0 = handle_0->previous;
         handle_1 = handle_1->previous;
      }
      prepend_digit(diff, curr_digit);
   }
   return diff; 
}

big_int add__big_int(big_int num_0, big_int num_1)
{
   big_int sum = NULL;   

   if(num_0->sign == POSITIVE && num_1->sign == POSITIVE) {
      sum = add_abs__big_int(num_0, num_1);
   } else if(num_0->sign == NEGATIVE && num_1->sign == NEGATIVE) {
      sum = add_abs__big_int(num_0, num_1);
      sum->sign = NEGATIVE;
   } else if(num_0->sign == POSITIVE && num_1->sign == NEGATIVE) {
      /* calculate which absolute value is greater. sub_actual smaller from greater */
      /* Also if negative number has greater absolute value -> sum is negative */
      num_1->sign = POSITIVE;
      if(cmp__big_int(num_0, num_1) >= 0) {
         sum = sub_abs__big_int(num_0, num_1);
         sum->sign = POSITIVE;
      } else {
         sum = sub_abs__big_int(num_1, num_0);
         sum->sign = NEGATIVE;
      }
      num_1->sign = NEGATIVE;
   } else if(num_0->sign == NEGATIVE && num_1->sign == POSITIVE) {
      num_0->sign = POSITIVE;
      if(cmp__big_int(num_0, num_1) > 0) {
         sum = sub_abs__big_int(num_0, num_1);
         sum->sign = NEGATIVE;
      } else {
         sum = sub_abs__big_int(num_1, num_0);
         sum->sign = POSITIVE;
      }
      num_0->sign = NEGATIVE;
   } else {
      fprintf(stderr,"FATAL ERROR: UNEXPECTED BEHAVIOR IN ADD__BIG_INT()\n");
   } 

   return sum;
}

big_int sub__big_int(big_int num_0, big_int num_1)
{
   big_int diff = NULL;   

   if(num_0->sign == POSITIVE && num_1->sign == POSITIVE) {
      if(cmp__big_int(num_0, num_1) >= 0) {
         diff = sub_abs__big_int(num_0, num_1);
         diff->sign = POSITIVE;
      } else {
         diff = sub_abs__big_int(num_1, num_0);
         diff->sign = NEGATIVE;
      }
   } else if(num_0->sign == NEGATIVE && num_1->sign == NEGATIVE) {
      if(cmp__big_int(num_0, num_1) < 0) {
         diff = sub_abs__big_int(num_0, num_1);
         diff->sign = NEGATIVE;
      } else {
         diff = sub_abs__big_int(num_1, num_0);
         diff->sign = POSITIVE;
      }
   } else if(num_0->sign == POSITIVE && num_1->sign == NEGATIVE) {
         diff = add_abs__big_int(num_0, num_1);
         diff->sign = POSITIVE;
   } else if(num_0->sign == NEGATIVE && num_1->sign == POSITIVE) {
         diff = add_abs__big_int(num_0, num_1);
         diff->sign = NEGATIVE;
   } else {
      fprintf(stderr,"FATAL ERROR: UNEXPECTED BEHAVIOR IN SUM__BIG_INT()\n");
   } 

   return diff;
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

   /* Deal with further digits */

   while(1) {
      if(handle_1 == NULL) {
         handle_0 = handle_0->previous;
         handle_1 = num_1->rear;

         if(carry != 0) {
            prepend_digit(line_product, carry);
            carry = 0;
         }

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

   if(num_0->sign == POSITIVE && num_1->sign == POSITIVE)      full_product->sign = POSITIVE;
   else if(num_0->sign == POSITIVE && num_1->sign == NEGATIVE) full_product->sign = NEGATIVE;
   else if(num_0->sign == NEGATIVE && num_1->sign == POSITIVE) full_product->sign = NEGATIVE;
   else if(num_0->sign == NEGATIVE && num_1->sign == NEGATIVE) full_product->sign = POSITIVE;

   return full_product;
}

big_int div__big_int(big_int divend, big_int divsor)
/* quotient only guaranteed to be correct if divisor divides evenly into dividend */
{ 
   if(cmp__big_int(divend, divsor) < 0) {
      return new__big_int("0");
   }

   big_int handle   = new__big_int("0");
   big_int quotient = new__big_int("0");
   big_int one      = new__big_int("1");

   int neg_marker_0 = 0, neg_marker_1 = 0;

   if(divend->sign == NEGATIVE) {
      divend->sign = POSITIVE;
      neg_marker_0 = 1;
   }
   if(divsor->sign == NEGATIVE) {
      divsor->sign = POSITIVE;
      neg_marker_1 = 1;
   }

   while(cmp__big_int(divend, handle) > 0) {
      big_int temp_0 = handle;
      big_int temp_1 = quotient;

      handle   = add__big_int(handle, divsor);
      quotient = add__big_int(quotient, one);
 
      free__big_int(temp_0);
      free__big_int(temp_1);
   }

   if(neg_marker_0) divend->sign = NEGATIVE;
   if(neg_marker_1) divsor->sign = NEGATIVE;

   if(neg_marker_0 && !neg_marker_1) quotient->sign = NEGATIVE;
   if(!neg_marker_0 && neg_marker_1) quotient->sign = NEGATIVE;

   free__big_int(one);
   free__big_int(handle);
 
   return quotient;
}

big_int mod__big_int(big_int divend, big_int divsor)
{
   big_int handle = new__big_int("0");
 
   if(divend->sign == POSITIVE) { 
      while(cmp__big_int(divend, handle) > 0) {
         big_int temp = handle;
         handle = add_abs__big_int(temp, divsor); 
         free__big_int(temp);
      }
   } else {
      while(cmp__big_int(divend, handle) < 0) {
         big_int temp = handle;
         handle = add_abs__big_int(handle, divsor);
         handle->sign = NEGATIVE;
         free__big_int(temp);
      }
      big_int temp = handle;
      handle = sub_abs__big_int(handle, divsor);
      handle->sign = NEGATIVE;
      free(temp);
   }

   big_int mod = sub__big_int(handle, divend);
   free__big_int(handle);
   
   return mod;
}

int cmp__big_int(big_int num_0, big_int num_1)
{
   /* test signs. If different signs -> positive num is larger */
   if(num_0->sign == POSITIVE && num_1->sign == NEGATIVE) {
      return 1;
   } else if(num_0->sign == NEGATIVE && num_1->sign == POSITIVE) {
      return -1;
   }

   /* can take sign from either big_num as they guaranteed same sign here */ 
   int sign = num_0->sign;

   /* test lengths. If different lengths -> (if negative -> shorter number is greater) *
    *                                       (if positive -> longer  number is greater) */
   if(num_0->length > num_1->length) {
      if(sign == POSITIVE) return 1;
      else                 return -1;
   } else if(num_0->length < num_1->length) {
      if(sign == POSITIVE) return -1;
      else                 return 1;
   }

   /* If here in function -> both nums are same sign and same length */
   
   /* Starting at fronts, step through nums until digits are different */

   digit handle_0 = num_0->front;
   digit handle_1 = num_1->front;

   while(handle_0 != NULL && handle_1 != NULL) {
      if(handle_0->actual > handle_1->actual) {
         if(sign == POSITIVE) return 1;
         else                 return -1;
      } else if(handle_0->actual < handle_1->actual) {
         if(sign == POSITIVE) return -1;
         else                 return 1;
      }
      handle_0 = handle_0->next;
      handle_1 = handle_1->next;
   }

   /* no digits were found to be different -> nums are equal */
   return 0;
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

