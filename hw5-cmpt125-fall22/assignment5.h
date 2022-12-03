#ifndef ASSIGNMENT5_H
#define ASSIGNMENT5_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lib/BTnode.h"
#include "lib/BST.h"


/* Question 1 */


// the function gets a string str, and a char delim
// and returns the number of tokens in the string separated by delim
int count_tokens(const char* str, char delim);

// the function gets a string str, and a char delim
// and returns the array of tokens in the string separated by delim
// the length of the array can be computed using count_tokens
char** get_tokens(const char* str, char delim);


/* Question 2 */

//  the function gets a string str, and an array of n chars: c[0…n-1].
// and returns an array of n strings consisting of the str
// concatenated with c[0], c[1]... c[n-1].
// the returned array and the strings are all be  allocated on the heap
char** append_chars(const char* str, int n, char* chars);


/* Question 3 */

// the function  gets a string phone_number
// and returns the number of distinct words that
// can be constructed from this phone_number
// assumption: strlen(phone_number) is between 1 and 12
int count_words(const char* phone_number);


// the function gets a string phone_number
// and returns the array of distinct words that
// can be constructed from this phone_number
// the legnth of the array can be computed using count_words
// assumption: strlen(phone_number) is between 1 and 12
char** get_words(const char* phone_number);


/* Question 4 */

// the function gets a binary search tree
// and returns the maximal number in it
int get_max(BST_t* tree);

// the function gets a binary search tree
// and returns the median number in it
int get_median(BST_t* tree);

#endif
