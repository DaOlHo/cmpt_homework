#include "assignment3.h"

int cmpfunc(const void* a, const void* b) {
  // Deref
  char* str1 = *(char**)a;
  char* str2 = *(char**)b;

  int len1 = strlen(str1);
  int len2 = strlen(str2);

  if (len1 != len2) return len1 - len2;
  else return strcmp(str1, str2);
}

void sort_strings(const char* A[], int n) {
  // Technically sorting the pointers, so sizeof here works
  qsort(A, n, sizeof(*A), cmpfunc);
}

int insert(int* array, int n, int i) {
  int swaps = 0;
  
  while (true) {
    if (i == 0 || array[i] > array[i - 1]) return swaps;

    // Swap
    int temp = array[i];
    array[i] = array[i - 1];
    array[i - 1] = temp;

    swaps++;
    i--;
  }
}

int* insertion_sort(int* array, int n) {
  int* swap_array = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    swap_array[i] = insert(array, n, i);
  }

  return swap_array;
}

int find(int* A, int n, bool (*pred)(int)) {
  for (int i = 0; i < n; i++) {
    if (pred(A[i])) return i;
  }
  
  return -1;
}


int count(int* A, int n, bool (*pred)(int)) {
  int count = 0;

  for (int i = 0; i < n; i++) {
    if (pred(A[i])) count++;
  }

  return count;
}


void map(int* A, int n, int (*f)(int)) {
  for (int i = 0; i < n; i++) {
    A[i] = f(A[i]);
  }
}


int reduce(int* A, int n, int (*f)(int,int)) {
  int acc = A[0];
  
  for (int i = 1; i < n; i++) {
    acc = f(acc, A[i]);
  }

  return acc;
}
