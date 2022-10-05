#ifndef ASSIGNMENT1_H
#define ASSIGNMENT1_H

#include <stdbool.h>

/* Question 1 */

// gets two integers x and y
// returns the number of even integers between x and y, including them.
long count_even(long x, long y);


/* Question 2 */

// gets an array of ints of length n
// returns the most frequent element in the array
// if there is more than one such element, the function may return any of them
// assumption: n>0
int most_frequent(const int* arr, int n);


/* Question 3 */

// checks if the given input is a palindrome of odd length
bool is_odd_palindrome(const char* str);


/* Question 4 */

// the function gets a string and returns the length of the longest
// substring that is a palindrome of odd length.
int longest_odd_subpalindrome(const char* str);


/* Question 5 */

// gets a string representing a positive integer
// and a digit between 1 and 9
// the function returns the string representing
// the result of the division with remainder
char* str_div_by_digit(const char* num, int digit);

#endif
