/* Shane Sims
 * <EMAIL>
 * 
 * calc_large
 * 
 * <DESCRIPTION>
 */

typedef struct big_int__struct * big_int;
/* big_int is the ADT created for this large number calculated. */

big_int new__big_int(char * num_string);
/* creates a new big_int with value equal num_string, returns NULL on error. */

void print__big_int(big_int num);
/* prints the big_int num to stdout. No newline is printed */

big_int add__big_int(big_int num_0, big_int num_1);
/* adds and returns two big_ints; the function does not free the operands */

void free__big_int(big_int num);
/* frees memory allocated to a big_int. Always free a big_int when finished with it. */

