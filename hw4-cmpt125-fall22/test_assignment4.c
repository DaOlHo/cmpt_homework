#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "assignment4.h"
#include "lib/BTnode.h"
#include "lib/queue.h"

#define SIZE 100000


/* Question 1 */

// helper functions
void move_queue(queue_str_t* dest, queue_str_t* src) {
  while (!queue_is_empty(src))
    enqueue(src, dequeue(dest));
}

queue_str_t* queue_create_from_array(char* strings[], int n) {
  queue_str_t* q = queue_create();
  for (int i = 0; i < n; i++)
    enqueue(q, strings[i]);
  return q;
}

bool check_and_free(queue_str_t* q, char* strings[], int n) {
  bool ret = true;
  for (int i = 0; i < n; i++)
    if (queue_is_empty(q) || dequeue(q)!=strings[i])
      ret = false;

  if (!queue_is_empty(q))
      ret = false;
  queue_free(q);
  return ret;
}

void test_q1size_1() {
  // create the strings
  char* strings[5] = {"hello", "hi", "hi", "123", "hi"};

  queue_str_t* q = queue_create_from_array(strings, 5);

  // testing the answer
  bool flag_ok = true;
  if (queue_size(q) != 5)             flag_ok = false;
  if (!check_and_free(q, strings, 5)) flag_ok = false;
  
  if (flag_ok)    printf("Q1-size-1 ok\n");
  else            printf("Q1-size-1 ERROR\n");
}


// empty queue
void test_q1size_2() {
  queue_str_t* q = queue_create_from_array(NULL, 0);

// testing the answer
  bool flag_ok = true;
  if (queue_size(q) != 0)   flag_ok = false;
  if (!queue_is_empty(q))   flag_ok = false;
  queue_free(q);

  if (flag_ok)    printf("Q1-size-2 ok\n");
  else            printf("Q1-size-2 ERROR\n");
}


void test_q1size_3() {
  // init the strings
  char* strings[SIZE];
  for (int i = 0; i < SIZE; i++) {
    strings[i] = malloc(20);
    sprintf(strings[i], "this_str%d",i);
  }

  queue_str_t* q = queue_create_from_array(strings, SIZE);

  // testing the answer
  bool flag_ok = true;
  if (queue_size(q) != SIZE)              flag_ok = false;
  if (!check_and_free(q, strings, SIZE))  flag_ok = false;

  for (int i = 0; i < SIZE; i++)
    free(strings[i]);

  if (flag_ok)    printf("Q1-size-3 ok\n");
  else            printf("Q1-size-3 ERROR\n");
}

void test_q1equal_1() {
  char hi[] = {'h', 'i', 0};
  char* strings1[6] = {"hello", "hi", hi, "123", "hi", "X"};
  char* strings2[6] = {"hello", "hi", "hi", "123", hi, "X"};
  // hi and "hi" have different pointers

  // create the queues
  queue_str_t* q1 = queue_create_from_array(strings1, 6);
  queue_str_t* q2 = queue_create_from_array(strings2, 6);

  // testing the answer
  bool flag_ok = true;
  if (queue_equal(q1, q2) == false) {
    printf("Q1-equal-1-1 ERROR\n");
    flag_ok = false;
  }
  if (!check_and_free(q1, strings1, 6)) {
    printf("Q1-equal-1-2 ERROR\n");
    flag_ok = false;
  }
  if (!check_and_free(q2, strings2, 6)) {
    printf("Q1-equal-1-3 ERROR\n");
    flag_ok = false;
  }

  if (flag_ok)    printf("Q1-equal-1 ok\n");
}


void test_q1equal_2() {
  char* strings3[2] = {"12", "3"};

  queue_str_t* q1 = queue_create(NULL,0);
  queue_str_t* q2 = queue_create(NULL,0);
  queue_str_t* q3 = queue_create_from_array(strings3, 2);

  // testing the answer
  bool flag_ok = true;
  if (queue_equal(q1, q2) == false)   flag_ok = false;
  if (queue_equal(q1, q3) == true)    flag_ok = false;
  if (queue_equal(q2, q3) == true)    flag_ok = false;
  if (!queue_is_empty(q1))            flag_ok = false;
  if (!queue_is_empty(q2))            flag_ok = false;
  if (!check_and_free(q3,strings3,2)) flag_ok = false;
  queue_free(q1);
  queue_free(q2);

  if (flag_ok)    printf("Q1-equal-2 ok\n");
  else            printf("Q1-equal-2 ERROR\n");
}


void test_q1equal_3() {
  char* strings1[3] = {"A", "A", "C"};
  char* strings2[2] = {"A", "A"};
  char* strings3[3] = {"A", "A", "A"};

  // create the queues
  queue_str_t* q1 = queue_create_from_array(strings1, 3);
  queue_str_t* q2 = queue_create_from_array(strings2, 2);
  queue_str_t* q3 = queue_create_from_array(strings3, 3);

  // testing the answer
  bool flag_ok = true;
  if (queue_equal(q1, q2) == true)        flag_ok = false;
  if (queue_equal(q2, q3) == true)        flag_ok = false;
  if (queue_equal(q1, q3) == true)        flag_ok = false;
  if (!check_and_free(q1, strings1, 3))   flag_ok = false;
  if (!check_and_free(q2, strings2, 2))   flag_ok = false;
  if (!check_and_free(q3, strings3, 3))   flag_ok = false;

  if (flag_ok)    printf("Q1-equal-3 ok\n");
  else            printf("Q1-equal-3 ERROR\n");
}


void test_q1tostring_1() {
  // create the strings
  char* strings[5] = {"123", "45", "6", "789", "abc"};
  char* correct_ans = "123456789abc";

  queue_str_t* q = queue_create_from_array(strings, 5);

  // testing the answer
  char* result =  queue_str_to_string(q);
  bool flag_ok = true;
  if (!result || strcmp(result, correct_ans)!=0)    flag_ok = false;
  if (!check_and_free(q, strings, 5))               flag_ok = false;

  if (result)
    free(result);
  
  if (flag_ok)    printf("Q1-tostring-1 ok\n");
  else            printf("Q1-tostring-1 ERROR\n");
}



void test_q1tostring_2() {
  // create the strings
  char* strings[2] = {"", ""};
  char* correct_ans = "";

  queue_str_t* q = queue_create_from_array(strings, 2);

  // testing the answer
  char* result =  queue_str_to_string(q);
  bool flag_ok = true;
  if (!result || strcmp(result, correct_ans)!=0)    flag_ok = false;
  if (!check_and_free(q, strings, 2))               flag_ok = false;

  if (result)
    free(result);
  
  if (flag_ok)    printf("Q1-tostring-2 ok\n");
  else            printf("Q1-tostring-2 ERROR\n");
}


void test_q1tostring_3() {
  // create the strings
  char* strings[SIZE];
  for (int i = 0; i < SIZE; i++) {
    strings[i] = malloc(20);
    sprintf(strings[i], "str%6d",i);
  }

  char* correct_ans = malloc(SIZE*9+1);
  correct_ans[0] = 0;
  for (int i = 0; i < SIZE; i++)
    strcpy(correct_ans+i*9, strings[i]);


  queue_str_t* q = queue_create_from_array(strings, SIZE);

  // testing the answer
  char* result =  queue_str_to_string(q);
  bool flag_ok = true;
  if (!result || strcmp(result, correct_ans)!=0) {
    printf("Q1-tostring-3-1 ERROR\n");
    flag_ok = false;
  }
  if (!check_and_free(q, strings, SIZE)) {
    printf("Q1-tostring-3-2 ERROR\n");
    flag_ok = false;
  }

  free(correct_ans);
  for (int i = 0; i < SIZE; i++)
    free(strings[i]);
  if (result)
    free(result);

  if (flag_ok)    printf("Q1-tostring-3 ok\n");
}


/* Question 2 */

BTnode_t* build_tree() {
/***
// creates the following tree
//      0
//    /   \
//   1      2
//  / \    / \
// 3   5  5  100
//    / \    / \
//   9   7  11  -2
****/
  BTnode_t* root_zero = create_node(0);
  BTnode_t* one = create_node(1);
  BTnode_t* two = create_node(2);
  BTnode_t* five1 = create_node(5);
  BTnode_t* hundred = create_node(100);
  BTnode_t* neg_two = create_node(-2);
  BTnode_t* three = create_node(3);
  BTnode_t* five2 = create_node(5);
  BTnode_t* seven = create_node(7);
  BTnode_t* eleven = create_node(11);
  BTnode_t* nine = create_node(9);

  set_left_child(root_zero, one);
  set_right_child(root_zero, two);
  
  set_left_child(one, three);
  set_right_child(one, five1);

  set_left_child(two, five2);
  set_right_child(two, hundred);

  set_left_child(five1, nine);
  set_right_child(five1, seven);

  set_left_child(hundred, eleven);
  set_right_child(hundred, neg_two);

  return root_zero;
}

bool greater20(int x) {return x>20;}
bool greater100(int x) {return x>100;}
bool is_negative(int x) {return x<0;}
bool is_even(int x) {return x%2==0;}


void test_q2find() {
  BTnode_t* root_zero = build_tree();
  BTnode_t* two = root_zero->right;
  BTnode_t* hundred = root_zero->right->right;
  BTnode_t* neg_two = hundred->right;

  if (find(root_zero, greater20) == hundred)
    printf("Q2-find-1 ok\n");
  else
    printf("Q2-find-1 ERROR\n");

  if (find(root_zero, is_negative) == neg_two)
    printf("Q2-find-2 ok\n");
  else
    printf("Q2-find-2 ERROR\n");

  if (find(root_zero, is_even) == root_zero ||
      find(root_zero, is_even) == two ||
      find(root_zero, is_even) == hundred ||
      find(root_zero, is_even) == neg_two)
    printf("Q2-find-3 ok\n");
  else
    printf("Q2-find-3 ERROR\n");

  if (find(root_zero, greater100) == NULL)
    printf("Q2-find-4 ok\n");
  else
    printf("Q2-find-4 ERROR\n");


  BT_free(root_zero);
}

int plus1(int x) {return x+1;};
int mult3(int x) {return 3*x;};

void test_q2map() {
  BTnode_t* root_zero = build_tree();
  BTnode_t* hundred = root_zero->right->right;
  BTnode_t* neg_two = hundred->right;
  BTnode_t* five1 = root_zero->left->right;
  BTnode_t* five2 = root_zero->right->left;

  // add 1 to all entries
  map(root_zero, plus1);
  if (hundred->value == 101)
    printf("Q2-map-1 ok\n");
  else
    printf("Q2-map-1 ERROR\n");

  if (neg_two->value == -1)
    printf("Q2-map-2 ok\n");
  else
    printf("Q2-map-2 ERROR\n");

  // now multiply all entries by 3
  map(root_zero, mult3);

  if (five1->value == 18)
    printf("Q2-map-3 ok\n");
  else
    printf("Q2-map-3 ERROR\n");

  if (five2->value == 18)
    printf("Q2-map-4 ok\n");
  else
    printf("Q2-map-4 ERROR\n");

  BT_free(root_zero);
}


void test_q2sum_of_leaves() {
  BTnode_t* root_zero = build_tree();
  BTnode_t* five2 = root_zero->right->left;
  BTnode_t* one = root_zero->left;

  if (sum_of_leaves(root_zero) == 33)
    printf("Q2-sum-1 ok\n");
  else
    printf("Q2-sum-1 ERROR\n");

  if (sum_of_leaves(five2) == 5)
    printf("Q2-sum-2 ok\n");
  else
    printf("Q2-sum-2 ERROR\n");

  if (sum_of_leaves(one) == 19)
    printf("Q2-sum-3 ok\n");
  else
    printf("Q2-sum-3 ERROR\n");

  BT_free(root_zero);
}


/* Question 3 */


void test_q3_1() {
  BTnode_t* root_zero = build_tree();

  int correct[11] = {0,1,3,5,9,7,2,5,100,11,-2};
  int ans[11];

  int i=0;
  BTnode_t* node = root_zero;
  while (node) {
    ans[i++] = node->value;
    node = next_preorder(node);
  }

  bool ok_flag = true;
  for (int i = 0; i < 11; i++) {
    if (ans[i] != correct[i]) {
      ok_flag = false;
//      printf("ans[%d] = %d, correct[%d]=%d\n", i,ans[i], i, correct[i]);
    }
  }
  if (node) {
    ok_flag = false;
//    printf("The tree is expected to have been traversed by now\n");
  }

  BT_free(root_zero);

  if (ok_flag)
    printf("Q3-1 ok\n");
  else
    printf("Q3-1 ERROR\n");
}

#define TREE_SIZE 100000
void test_q3_2() {
  // build a long skinny tree going only left
  //            0
  //           /
  //          1
  //         /
  //        2
  //      ...
  //      /
  //   TREE_SIZE-1

  int i;
  BTnode_t* root_zero = create_node(0);
  BTnode_t* node = root_zero;
  for (i = 1; i < TREE_SIZE; i++) {
      set_left_child(node, create_node(i));
      node = node->left;
  }

  bool ok_flag = true;
  node = root_zero;
  for (i = 0; i < TREE_SIZE && node; i++) {
    if (node->value!= i) {
      ok_flag = false;
      printf("Q3-2 ERROR: the %d'th node is incorrect %d\n", i, node->value);
    }
    node = next_preorder(node);
  }

  if (i != TREE_SIZE) {
    ok_flag = false;
    printf("Q3-2 ERROR: not all nodes were read\n");
  }
  
  if (node) {
    ok_flag = false;
    printf("Q3-2 ERROR: node is expected to be NULL at the end\n");
  }

  BT_free(root_zero);

  if (ok_flag)
    printf("Q3-2 ok\n");
}



// when testing your code, it may be convenient 
// to comment out some of the test cases
// and focus only on the one you are working on right now
int main()  {

  test_q1size_1();
  test_q1size_2();
  test_q1size_3();
 
  test_q1equal_1();
  test_q1equal_2();
  test_q1equal_3();
 
  test_q1tostring_1();
  test_q1tostring_2();
  test_q1tostring_3();
 
  test_q2find();
  test_q2map();
  test_q2sum_of_leaves();

  test_q3_1();
  test_q3_2();
}