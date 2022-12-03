 #ifndef ASSIGNMENT4_H
#define ASSIGNMENT4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lib/queue.h"
#include "lib/BTnode.h"


/* Question 1 */

// returns the size of the queue
int queue_size(queue_str_t* q);

// checks if the two queues are equal
bool queue_equal(queue_str_t* q1, queue_str_t* q2);

// returns the concatenation of all strings in the queue
// For example, if we add to the queue "a ", then "_b", and then "@ C2D"
// the function returns the string "a _b@ C2D".
char* queue_str_to_string(queue_str_t* q);


/* Question 2 */

// finds the a node satisfying pred
// if there are several such nodes, the function may return any of them
// if such node not found, returns NULL
BTnode_t* find(BTnode_t* root, bool (*pred)(int));

// appies f to each node of the tree
void map(BTnode_t* root, int (*f)(int));

// computes the sum of all leaves of the tree
int sum_of_leaves(const BTnode_t* root);


/* Question 3 */

// gets a node in a binary tree
// returns the next node in the preorder traversal of the tree
BTnode_t* next_preorder(BTnode_t* node);


#endif
