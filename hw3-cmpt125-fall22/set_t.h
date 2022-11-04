#ifndef ASSIGNMENT3_SET_H
#define ASSIGNMENT3_SET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Question 4 */

typedef struct {
  int length;
  int* inner;
} set_t;

// creates an empty set
set_t* set_create_empty();

// returns the size of the set A
int set_size(set_t* A);

// the function gets a pointer to the set A and a number x
// and adds x to the set. If x was already in the set,
// the function has no effect on A.
void set_insert(set_t* A, int x);

// gets a pointer to the set A and a number x, and removes x from A.
// Assumption: x belongs to A.
void set_remove(set_t* A, int x);

// gets a pointer to the set A and a number x.
// returns true if x belongs to A, and returns false otherwise.
bool set_contains(set_t* A, int x);

// gets a set A and a function f, and appies f to all elements of A.
// Note that after applying f some values might become duplicates,
// in which case you need to remove the duplicates.
// The function returns the size of the obtained set A.
int set_map(set_t* A, int (*f)(int));

// frees the set and all its inner data field
void set_free(set_t* A);


#endif
