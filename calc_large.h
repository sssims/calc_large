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

void free__big_int(big_int num);
/* frees memory allocated to a big_int. Always free a big_int when finished with it. */
