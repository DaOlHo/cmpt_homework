#include "set_t.h"

set_t* set_create_empty() {
  set_t* set = malloc(sizeof(set_t));

  set->length = 0;
  set->inner = NULL;

  return set;
}

int set_size(set_t* A) {
  return A->length;
}

void set_insert(set_t* A, int x) {
  if (!set_contains(A, x)) {
    A->length++;
    A->inner = realloc(A->inner, sizeof(int) * A->length);
    A->inner[A->length - 1] = x;
  }
}

void set_remove(set_t* A, int x) {
  if (set_contains(A, x)) {
    bool is_found = false;

    // My attempt at an in place remove
    for (int i = 0; i < A->length; i++) {
      if (is_found) A->inner[i - 1] = A->inner[i];
      if (A->inner[i] == x) is_found = true;
    }

    A->length--;
    A->inner = realloc(A->inner, sizeof(int) * A->length);
  }
}

bool set_contains(set_t* A, int x) {
  for (int i = 0; i < A->length; i++) {
    if (A->inner[i] == x) return true;
  }
  
  return false;
}

void print_all(set_t* A) {
  for (int i = 0; i < A->length; i++) {
    printf("%d, ", A->inner[i]);
  }

  printf("\n");
}

int set_map(set_t* A, int (*f)(int)) {
  // Move array out of set
  int* arr = A->inner;
  int arr_len = A->length;
  A->inner = NULL;
  A->length = 0;

  for (int i = 0; i < arr_len; i++) {
    set_insert(A, f(arr[i]));
  }
  
  return A->length;
}

void set_free(set_t* A) {
  free(A->inner);
  free(A);
}
