#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "assignment3.h"
#include "set_t.h"

bool test_q1_1() {
  const char* A[] = {"hello", "World", "1", "2", "12345678"};
  sort_strings(A, 5);
  const char* correct_ans[] = { "1", "2", "World", "hello", "12345678"};
  bool flag_ok = true;
  for (int i = 0; i < 5; i++) {
    if (strcmp(A[i], correct_ans[i]) != 0) {
      flag_ok = false;
      break;
    }
  }
  if (flag_ok) {
    printf("Q1-1 ok\n");
    return true;
  }
  else  {
    printf("Q1-1 ERROR\n");
    return false;
  }
}


bool test_q1_2() {
  const char* A[] = {"Wx", "ab", "Zde", "6_@7h", "7", "hij",  "_hh", "b"};
  sort_strings(A, 8);
  const char* correct_ans[] = {"7", "b", "Wx", "ab", "Zde", "_hh", "hij", "6_@7h"};
  bool flag_ok = true;
  for (size_t i = 0; i < 8; i++) {
    if (strcmp(A[i], correct_ans[i]) != 0) {
      flag_ok = false;
      break;
    }
  }
  if (flag_ok) {
    printf("Q1-2 ok\n");
    return true;
  }
  else  {
    printf("Q1-2 ERROR\n");
    return false;
  }
}

bool equal_arrays(int* a1, int* a2, int n) {
  for (size_t i = 0; i < n; i++)
    if (a1[i] != a2[i])
      return false;
  return true;
}

bool test_q2_1()  {
  int ar[] = {4,3,6,1,2,5};
  int* trace =  insertion_sort(ar, 6);

  int correct_ans[] = {1,2,3,4,5,6};
  int correct_trace[] = {0,1,0,3,3,1};

  bool flag_ok;
  if (!trace) {
    flag_ok = false;
  }
  else {
    flag_ok = (equal_arrays(ar, correct_ans, 6) && equal_arrays(trace, correct_trace, 6));
    free(trace);
  }

  if (flag_ok) {
    printf("Q2-1 ok\n");
    return true;
  }
  else  {
    printf("Q2-1 ERROR\n");
    return false;
  }
}

bool test_q2_2()  {
  int ar[100];
  for (size_t i = 0; i < 100; i++)
    ar[i] = 100-i;

  int* trace =  insertion_sort(ar, 100);

  int correct_ans[100];
  int correct_trace[100];
  for (size_t i = 0; i < 100; i++) {
    correct_ans[i] = i+1;
    correct_trace[i] = 99-i;
  }

  bool flag_ok;
  if (!trace) {
    flag_ok = false;
  }
  else {
    flag_ok = (equal_arrays(ar, correct_ans, 6) && !equal_arrays(trace, correct_trace, 6));
    free(trace);
  }

  if (flag_ok) {
    printf("Q2-2 ok\n");
    return true;
  }
  else  {
    printf("Q2-2 ERROR\n");
    return false;
  }
}

// used for test Q3-find and Q3-count
bool is_even(int x) { return x%2 == 0; }
bool is_positive(int x) { return x>0; }

void test_q3_find()  {
  int A[6] = {-1,3,-6,5,2,7};

  if (find(A, 6, is_even)==2 && find(A, 6, is_positive)==1) 
    printf("Q3-find ok\n");
  else
    printf("Q3-find ERROR\n");
}

void test_q3_count()  {
  int A[6] = {-1,3,-6,5,2,8};

  if (count(A, 6, is_even)==3 && count(A, 6, is_positive)==4) 
    printf("Q3-count ok\n");
  else
    printf("Q3-count ERROR\n");
}

// used for test Q3-map
int mult4(int x) { return x*4;}

void test_q3_map()  {
  int A[6] = {-1,3,-6,5,2,7};
  map(A, 6, mult4);

  if (A[0]==-4 && A[3]==20) 
    printf("Q3-map ok\n");
  else
    printf("Q3-map ERROR\n");
}

// used for test Q3-reduce
int sum(int x, int y) {return x+y;}
int last(int x, int y) {return y;}

void test_q3_reduce()  {
  int A[6] = {-1,3,-6,5,2,7};

  if (reduce(A, 6, sum)==10 && reduce(A, 6, last)==7) 
    printf("Q3-reduce ok\n");
  else
    printf("Q3-reduce ERROR\n");
}
 

bool test_q4_1() {
  bool flag_ok = true;

  set_t* A = set_create_empty(); // A = {}
  for (int i=0;i<=5;i++)
    set_insert(A, 10*i);
  
  // A = {0,10,20,30,40,50}
  if (set_size(A) != 6)
    flag_ok = false;

  set_insert(A, -1); // A = {-1,0,10,20,30,40,50}

  if (set_size(A) != 7)
    flag_ok = false;

  for (size_t i = 0; i <= 5; i++)
    if (!set_contains(A,10*i))
      flag_ok = false;
  if (!set_contains(A,-1))
      flag_ok = false;

  set_free(A);

  if (flag_ok) {
    printf("Q4-1 ok\n");
    return true;
  }
  else  {
    printf("Q4-1 ERROR\n");
    return false;
  }
}


bool test_q4_2() {
  bool flag_ok = true;

  set_t* A = set_create_empty(); // A = {}

  for (int i=0;i<5;i++)
    set_insert(A, i);
  // A = {0,1,2,3,4}

  set_insert(A, 2);
  set_insert(A, 3);
  if (set_size(A) != 5)
    flag_ok = false;

  set_insert(A, 9); // A = {0,1,2,3,4,9}
  for (size_t i = 0; i < 5; i++)
    if (!set_contains(A,i))
      flag_ok = false;

  set_remove(A, 1); // A = {0,2,3,4,9}
  set_remove(A, 9); // A = {0,2,3,4}
  if (set_size(A) != 4)
    flag_ok = false;

  set_free(A);


  if (flag_ok) {
    printf("Q4-2 ok\n");
    return true;
  }
  else  {
    printf("Q4-2 ERROR\n");
    return false;
  }
}

/** START functions used for set_map() **/
  int mod5(int x) {return x%5;}
  int plus1(int x) {return x+1;}
/** END functions used for set_map() **/

bool test_q4_3() {
  bool flag_ok = true;

  set_t* A = set_create_empty(); // A = {}
  for (int i=10;i<15;i++)
    set_insert(A, i);
  // here A = {10,11,12,13,14}
  
  int ans1 = set_map(A, plus1); // A = {11,12,13,14,15}
  if (ans1!= 5 || !set_contains(A,15) || set_contains(A,10))
    flag_ok = false;
  
  set_insert(A, 9); // A becomes {9,11,12,13,14,15}
  if (set_size(A) != 6)
    flag_ok = false;
  
  set_remove(A, 13); // A becomes {9,11,12,14,15}
  
  set_insert(A, 1); // A becomes {1,9,11,12,14,15}
  set_insert(A, 12); // A doesn’t change because 12 was already in A
  
  int ans2 = set_map(A, mod5); // A becomes  {0,1,2,4}
  if (ans2!= 4 || set_size(A)!=4)
    flag_ok = false;

  set_free(A);

  if (flag_ok) {
    printf("Q4-3 ok\n");
    return true;
  }
  else  {
    printf("Q4-3 ERROR\n");
    return false;
  }
}


// when testing your code, it may be convenient 
// to comment out some of the test cases
// and focus only on the one you are working on right now
int main()  {

  test_q1_1();
  test_q1_2();

  test_q2_1();
  test_q2_2();

  test_q3_find();
  test_q3_count();
  test_q3_map();
  test_q3_reduce(); 

  test_q4_1();
  test_q4_2();
  test_q4_3();

}