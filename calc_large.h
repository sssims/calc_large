/* Shane Sims
 * <EMAIL>
 * 
 * calc_large
 *
 * NOTES:
 *   Almost all functionality of this ADT assumes valid input. It is NOT safe to assume
 * these functions will error out safely if given bad input.  
 * 
 * <DESCRIPTION>
 */

typedef struct big_int__struct * big_int;
/* big_int is the ADT created for this large number calculated. */

big_int new__big_int(char * num_string);
/* creates a new big_int with value equal num_string. Returns NULL if error is caught.
 * First character can be a '-' or a '+' to indicate sign. If no sign is indicated the big_int
   will be positive */

void print__big_int(big_int num);
/* prints the big_int to stdout. No newline is printed */

big_int add__big_int(big_int num_0, big_int num_1);
/* adds two big_ints and returns sum; allocates space for sum; does not free operands */

big_int sub__big_int(big_int num_0, big_int num_1);
/* subtracts big_int num_1 from big_int num_0 and returns difference; allocates space for difference; does not free operands */

big_int mult__big_int(big_int num_0, big_int num_1);
/* multiplies two big_ints and returns product; allocates space for product; does not free operands */

big_int div__big_int(big_int num_0, big_int num_1);
/* divides two big_ints and returns quotient; allocates space for quotient; does not free operands*/

int cmp__big_int(big_int num_0, big_int num_1);
/* compares two big_ints value; returns 0 if equal, 1 if num_0 > num_1, and -1 if num_0 < num_1; does not free operands */

void free__big_int(big_int num);
/* frees memory allocated to a big_int. Always free a big_int when finished with it. */

