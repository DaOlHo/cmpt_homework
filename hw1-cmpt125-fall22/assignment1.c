#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment1.h"

long count_even(long x, long y) {
  long diff = (x - y);
  diff = ((diff >> 31) | 1) * diff; // abs

  // O(1) equation to find amount of even numbers
  long even_count = (diff / 2) + (diff % 2);
  if (x % 2 == 0 && y % 2 == 0) even_count += 1; // Account for both being even

  return even_count;
}  

int compar(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

int most_frequent(const int* arr, int n) {
  int sorted_arr[n];

  // Deep copy array so it can be sorted
  for (int i = 0; i < n; i++) {
    sorted_arr[i] = arr[i];
  }

  qsort(sorted_arr, n, sizeof(sorted_arr[0]), compar);

  int top_num = 0;
  int top_count = 0;

  int current_num = 0;
  int current_count = 0;

  for (int i = 0; i < n; i++) {
    if (sorted_arr[i] != current_num) {
      if (top_count < current_count) {
        top_num = current_num;
        top_count = current_count;
      }

      current_num = sorted_arr[i];
      current_count = 0;
    }

    current_count++;
  }

  // Update top number if the final section has most occurences
  if (top_count < current_count) {
    top_num = current_num;
    top_count = current_count;
  }

  return top_num;
}

bool is_odd_palindrome(const char* str) {
  int str_size = strlen(str);

  // Return if not odd
  if (str_size % 2 == 0) return false;

  for (int i = 0; i < str_size / 2; i++) {
    if (str[i] != str[(str_size - 1) - i]) return false;
  }

  return true;
}


int longest_odd_subpalindrome(const char* str)  {
  int longest_pal = -1;
  int str_size = strlen(str);

  for (int i = 1; i < str_size - 1; i++) {
    // This identifies if palindrome exists, from here expand on either side to get its length
    if (str[i - 1] == str[i + 1] /*&& str[i] != str[i - 1]*/) {
      // Starts at 3 because to enter this branch, there must be a palindrome length 3
      int current_length = 3;
      int j = 1;

      while (true) {
        j++;

        int left_index = i - j;
        int right_index = i + j;
        // Make sure we aren't going outside the array
        if (left_index < 0 || right_index >= str_size) break;
        // Break as well if this stops being a palindrome
        else if (str[left_index] != str[right_index]) break;

        // If it is still a palindrome, add to length
        current_length += 2;
      }

      if (longest_pal < current_length) longest_pal = current_length;
    }
  }

  return longest_pal;
}

char* str_div_by_digit(const char* num, int digit) {
  int carry_digit = 0;
  int str_size = strlen(num);

  char* result = malloc((str_size + 1 + 2) * sizeof(char)); // Adds 1 for \0 and 2 for Rx

  // To avoid 0 padding
  int result_index = 0;
  bool leading = true;

  for (int i = 0; i < str_size; i++) {
    int current_num = (int)num[i] - 48 + (carry_digit * 10); // 48 is offset of 0 in ascii table
    int result_num = current_num / digit;
    carry_digit = current_num % digit;

    if (result_num != 0) leading = false;

    if (!leading) {
      result[result_index++] = (char)(result_num + 48);
    }
  }

  // Add remainder indicator
  result[result_index++] = 'R';
  result[result_index] = (char)(carry_digit + 48); // Can only be 1 b/c divisor is digit

  // Trim string length to save memory
  int result_size = strlen(result);
  result = realloc(result, (result_size + 1) * sizeof(char));

  return result;
}  
