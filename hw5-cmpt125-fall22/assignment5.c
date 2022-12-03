#include "assignment5.h"


/* Question 1 */


int count_tokens(const char* str, char delim) {
  int i = 0;
  char current_char = str[0];
  int counter = 0;
  bool is_in_token = false;

  while (current_char != 0) {
    if (!is_in_token && current_char != delim) counter++;

    is_in_token = current_char != delim;

    current_char = str[++i];
  }
  
  return counter;
}


char** get_tokens(const char* str, char delim) {
  int str_len = strlen(str);
  char* buffer_str = malloc((str_len + 1) * sizeof(char));
  int buffer_str_iter = 0;

  bool is_in_token = false;

  char** result = malloc(count_tokens(str, delim) * sizeof(char*));
  int result_iter = 0;

  for (int i = 0; i < str_len; i++) {
    if ((is_in_token && str[i] == delim) || i == str_len - 1) {
      if (i == str_len - 1) buffer_str[buffer_str_iter++] = str[i]; // Account for end of string
      buffer_str[buffer_str_iter] = 0;

      // Copy to result and reset
      result[result_iter++] = realloc(buffer_str, (strlen(buffer_str) + 1) * sizeof(char));
      buffer_str = malloc(str_len * sizeof(char));
      buffer_str_iter = 0;
    }

    is_in_token = str[i] != delim;

    if (is_in_token) buffer_str[buffer_str_iter++] = str[i];
  }
  
  free(buffer_str);

  return result;
}


/* Question 2 */

char** append_chars(const char* str, int n, char* chars) {
  int len = strlen(str);
  char** result = malloc(n * sizeof(char*));

  for (int i = 0; i < n; i++) {
    result[i] = malloc((len + 2) * sizeof(char));
    strcpy(result[i], str);
    
    result[i][len] = chars[i];
    result[i][len + 1] = 0; // Just to be safe
  }

  return result;
}


/* Question 3 */

int count_words(const char* phone_number) {
  int len = strlen(phone_number);
  int count = 1;

  for (int i = 0; i < len; i++) {
    if (phone_number[i] == '7' || phone_number[i] == '9') count *= 4;
    else count *= 3;
  }

  return count;
}

void copy_to_array(char** dest, char** source, int source_n, int dest_offset) {
  for (int i = 0; i < source_n; i++) {
    dest[dest_offset + i] = source[i];
  }
}

char TWO[] = { 'a', 'b', 'c' };
char THREE[] = { 'd', 'e', 'f' };
char FOUR[] = { 'g', 'h', 'i' };
char FIVE[] = { 'j', 'k', 'l' };
char SIX[] = { 'm', 'n', 'o' };
char SEVEN[] = { 'p', 'q', 'r', 's' };
char EIGHT[] = { 't', 'u', 'v' };
char NINE[] = { 'w', 'x', 'y', 'z' };
char* NUM_TABLE[] = { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };

char** get_words(const char* phone_number) {  
  int str_len = strlen(phone_number);
  int result_len = 1;
  char** result = malloc(sizeof(char*) * count_words(phone_number));
  result[0] = ""; // Initial 'seed' string

  for (int i = 0; i < str_len; i++) {
    int num = phone_number[i] - 50; // 50 -> 0 so we can index NUM_TABLE
    int num_len;
    if (num == 5 || num == 7) num_len = 4;
    else num_len = 3;

    char** total_combos = malloc(sizeof(char*) * result_len * num_len);
    int total_combos_len = 0;

    for (int j = 0; j < result_len; j++) {
      char** combos = append_chars(result[j], num_len, NUM_TABLE[num]);
      copy_to_array(total_combos, combos, num_len, j * num_len);

      total_combos_len += num_len;
      free(combos);
    }

    // Overwrite top level array
    copy_to_array(result, total_combos, total_combos_len, 0);
    result_len = total_combos_len;

    free(total_combos);
  }

  return result;
}


/* Question 4 */

// Shamelessly stolen from my last assignment
BTnode_t* next_preorder(BTnode_t* node) {
  if (node->left != NULL) return node->left;
  else if (node->right != NULL) return node->right;

  // This is a leaf, so finding the next preorder is difficult
  BTnode_t* last = NULL;
  BTnode_t* curr = node;

  while (true) {
    if (curr->parent == NULL) return NULL;
    else {
      last = curr;
      curr = last->parent;

      if (curr->right != last && curr->right != NULL) return curr->right;
    }
  }
}

int get_max(BST_t* tree) {
  // Get initial values
  int max = tree->root->value;
  BTnode_t* curr_node = tree->root;

  while (curr_node != NULL) {
    if (max < curr_node->value) max = curr_node->value;

    curr_node = next_preorder(curr_node);
  }

  return max;
}

int get_tree_size(BST_t* tree) {
  int count = 0;
  BTnode_t* curr_node = tree->root;

  while (curr_node != NULL) {
    count++;
    curr_node = next_preorder(curr_node);
  }

  return count;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int get_median(BST_t* tree) {
  int tree_size = get_tree_size(tree);
  int* arr = malloc(sizeof(int) * tree_size);

  int arr_iter = 0;
  BTnode_t* curr_node = tree->root;

  while (curr_node != NULL) {
    arr[arr_iter++] = curr_node->value;
    curr_node = next_preorder(curr_node);
  }

  qsort(arr, tree_size, sizeof(int), cmpfunc);

  if (tree_size % 2 == 0) return arr[tree_size / 2];
  else return arr[(tree_size - 1) / 2];
}
