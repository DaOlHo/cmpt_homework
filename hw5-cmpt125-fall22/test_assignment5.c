#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "assignment5.h"
#include "lib/BTnode.h"
#include "lib/BST.h"

void test_q1_1() {

  char *str = "HELLO WORLD dot  c";
  char delim = ' ';
  int count = count_tokens(str, delim);
  if (count == 4)
    printf("Q1-1-count ok\n");
  else
    printf("Q1-1-count ERROR\n");

  char **tokens = get_tokens(str, delim);

  char *sol[4] = {"HELLO", "WORLD", "dot", "c"};

  if (!tokens) {
    printf("Q1-1-tokens ERROR: tokens==NULL\n");
    return;
  }

  bool flagOk = true;
  for (int i = 0; i < 4; i++) {
    if (!tokens[i] || strcmp(tokens[i], sol[i])!=0) {
      printf("Q1-1-tokens ERROR: tokens[%d] error: %s != %s\n", i, tokens[i], sol[i]);
      flagOk = false;
    }
  }

  for (int i = 0; i < 4; i++) {
    if (tokens[i])
      free(tokens[i]);
  }
  free(tokens);

  if (flagOk)
    printf("Q1-1-get-tokens ok\n");
}

void test_q1_2() {

  char *str = "---Given--the---existence-as-uttered--forth----in----the----public--works-of-Puncher--and--Wattmann---";
  char delim = '-';
  int count = count_tokens(str, delim);
  if (count == 14)
    printf("Q1-1-count ok\n");
  else
    printf("Q1-1-count ERROR\n");

  char **tokens = get_tokens(str, delim);

  char *sol[] = {"Given", "the", "existence", "as", "uttered", "forth",
                  "in", "the", "public", "works", "of", "Puncher", "and", "Wattmann"};

  if (!tokens) {
    printf("Q1-2-tokens ERROR: tokens==NULL\n");
    return;
  }

  bool flagOk = true;
  for (int i = 0; i < 14; i++) {
    if (!tokens[i] || strcmp(tokens[i], sol[i])!=0) {
      printf("Q1-2-tokens ERROR: tokens[%d] error: %s != %s\n", i, tokens[i], sol[i]);
      flagOk = false;
    }
  }

  for (int i = 0; i < 14; i++) {
    if (tokens[i])
      free(tokens[i]);
  }
  free(tokens);

  if (flagOk)
    printf("Q1-2-get-tokens ok\n");
}

void test_q2_1() {
  char* init_str = "hello";

  char c[] = {'a','b','c'};

  char** res = append_chars(init_str, 3, c);
  
  char* correct[] = {"helloa","hellob","helloc"};
  bool flagOk = true;

  if (!res) {
    flagOk = false;
    return;
  }
  for (int i = 0; i < 3; i++)
    if (res[i]==NULL || strcmp(res[i], correct[i])!=0)
      flagOk = false;

  for (int i = 0; i < 3; i++)
    if (res[i])
      free(res[i]);
  free(res);

  if (flagOk)
    printf("Q2-1 ok\n");
  else
    printf("Q2-1 ERROR\n");
}

void test_q2_2() {
  char* init_str = "abc";

  char c[] = {'a','x','a','b','y','z'};

  char** res = append_chars(init_str, 6, c);
  
  char* correct[] = {"abca", "abcx", "abca", "abcb", "abcy", "abcz"};
  bool flagOk = true;

  if (!res) {
    flagOk = false;
    return;
  }
  for (int i = 0; i < 6; i++)
    if (res[i]==NULL || strcmp(res[i], correct[i])!=0)
      flagOk = false;

  for (int i = 0; i < 6; i++)
    if (res[i])
      free(res[i]);
  free(res);

  if (flagOk)
    printf("Q2-2 ok\n");
  else
    printf("Q2-2 ERROR\n");
}


void test_q2_3() {
  char* init_str = "";

  char c[] = {'x','y','x','z'};

  char** res = append_chars(init_str, 4, c);
  
  char* correct[] = {"x","y","x","z"};
  bool flagOk = true;

  if (!res) {
    flagOk = false;
    return;
  }
  for (int i = 0; i < 4; i++)
    if (res[i]==NULL || strcmp(res[i], correct[i])!=0)
      flagOk = false;

  for (int i = 0; i < 4; i++)
    if (res[i])
      free(res[i]);
  free(res);

  if (flagOk)
    printf("Q2-3 ok\n");
  else
    printf("Q2-3 ERROR\n");
}



void test_q3_1() {

  int ans1 = count_words("7");
  int ans2 = count_words("222");
  int ans3 = count_words("29");
  int ans4 = count_words("23456789");

  if (ans1==4 && ans2==27 && ans3==12 && ans4==11664)
    printf("Q3-1 ok\n");
  else
    printf("Q3-1 ERROR\n");
}

int str_cmp(const void* str1, const void* str2) {
  return strcmp(*(char**)str1, *(char**)str2);
}

bool compare_strs(char* ans[], char* correct[], int n) {
  // sort and compare
  qsort(ans, n, sizeof(char*), str_cmp);
  qsort(correct, n, sizeof(char*), str_cmp);
  for (int  i = 0; i < n; i++)
    if (strcmp(ans[i], correct[i])!=0)
      return false;

  return true; 
}

void test_q3_2() {

  char** ans1 = get_words("7");
  char** ans2 = get_words("222");
  char** ans3 = get_words("29");

  bool flagOk = true;

  // order doesn't matter
  char* correct1[] = {"p","s","q","r"};
  char* correct2[] = {"aaa","aab","aac","aba","abb","abc","aca","acb","acc",
                     "baa","bab","bac","bba","bbb","bbc","bca","bcb","bcc",
                     "caa","cab","cac","cba","cbb","cbc","cca","ccb","ccc"};
  char* correct3[] = {"aw","bw","cw","ax","bx","cx","ay","by","cy","az","bz","cz"};

  if (ans1==NULL) {
    printf("Q3-2 ERROR: ans1=NULL\n");
    return;
  }

  if (ans2==NULL) {
    printf("Q3-2 ERROR: ans2=NULL\n");
    return;
  }

  if (ans3==NULL) {
    printf("Q3-2 ERROR: ans3=NULL\n");
    return;
  }

  flagOk = compare_strs(ans1, correct1, 4) && compare_strs(ans2, correct2, 27) && compare_strs(ans3, correct3, 12);
  if (flagOk)
    printf("Q3-2 ok\n");
  else
    printf("Q3-2 ERROR\n");
}

BST_t* build_tree() {
  BST_t* bstree = BST_create();

  BST_insert(bstree, 4);
  BST_insert(bstree, 2);
  BST_insert(bstree, 8);
  /*    4
  //   / \
  //  2   8
  */
  BST_insert(bstree, 3);
  BST_insert(bstree, 5);
  BST_insert(bstree, 10);
  /*     4
  //   /   \
  //  2     8
  //   \   / \
  //    3 5   10
  */
  BST_insert(bstree, 7);
  /*     4
  //   /   \
  //  2     8
  //   \   / \
  //    3 5   10
  //       \
  //        7
  */
 BST_insert(bstree, 11);
  return bstree;
}

void test_q4_1() {

  BST_t* tree = build_tree();
  bool flagOk = true;

  if (get_max(tree)!= 11) {
    flagOk = false;
  }

  BST_free(tree);
  
  if (flagOk)
    printf("Q4-1 ok\n");
  else
    printf("Q4-1 ERROR\n");
}


void test_q4_2() {

  BST_t* tree = build_tree();
  bool flagOk = true;

  if (get_median(tree)!= 7) {
    flagOk = false;
  }

  BST_free(tree);
  
  if (flagOk)
    printf("Q4-2 ok\n");
  else
    printf("Q4-2 ERROR\n");
}

void test_q4_3() {
    BST_t* large_tree = BST_create();
    
    //the median shall be 5001
    for (int i = 10000; i >= 1; i--) {
        BST_insert(large_tree, i);
    }
    printf("~\nQ4-2 #1 tree has finished building! start timing now if you want to measure runtime.\n~\n");
    int ans = get_median(large_tree);
    if (ans == 5001) {
        printf("Q4-2 test 1 ok.\n");
    } else {
        printf("Q4-2 test 1 wrong.\n");
    }
    BST_free(large_tree);


    BST_t* larger_tree = BST_create();
    BST_insert(larger_tree, 1000000);
    BTnode_t* current_head_of_lt = larger_tree->root;
    for (int i = 99999; i >= 1; i--) {
        BTnode_t* temp = create_node(i);
        set_left_child(current_head_of_lt, temp);
        current_head_of_lt = temp;
    }

    printf("~\nQ4-2 #2 tree has finished building! start timing now if you want to measure runtime.\n~\n");
    int ans_2 = get_median(larger_tree);
    printf("Your answer for Q4-2 #2 is %d, the right answer is 50001, please confirm. \n", ans_2);
    BST_free(larger_tree);
}

// when testing your code, it may be convenient
// to comment out some of the test cases
// and focus only on the one you are working on right now
int main() {
  test_q1_1();
  test_q1_2();

  test_q2_1();
  test_q2_2();
  test_q2_3();

  test_q3_1();
  test_q3_2();

  test_q4_1();
  test_q4_2();
  test_q4_3();
}