#include "assignment4.h"


/* Question 1 */

// Ideally if you were actually implementing this you would have
// access to the inner array, but I don't, so...
int queue_size(queue_str_t* q) {
  int size = 0;
  queue_str_t* tmp = queue_create();

  // Count elements
  while(!queue_is_empty(q)) {
    enqueue(tmp, dequeue(q));

    size++;
  }

  // Return elements to original queue
  while(!queue_is_empty(tmp)) {
    enqueue(q, dequeue(tmp));
  }

  queue_free(tmp);

  return size;
}


bool queue_equal(queue_str_t* q1, queue_str_t* q2) {
  bool is_equal = true;

  queue_str_t* tmp1 = queue_create();
  queue_str_t* tmp2 = queue_create();

  while(!(queue_is_empty(q1) || queue_is_empty(q2))) {
    char* str1 = dequeue(q1);
    char* str2 = dequeue(q2);

    if (strcmp(str1, str2) != 0) is_equal = false;

    enqueue(tmp1, str1);
    enqueue(tmp2, str2);
  }

  // Account for uneven strings
  while(!queue_is_empty(q1)) {
    enqueue(tmp1, dequeue(q1));
    is_equal = false;
  }
  while(!queue_is_empty(q2)) {
    enqueue(tmp2, dequeue(q2));
    is_equal = false;
  }

  // Return elements to original queue
  while(!queue_is_empty(tmp1)) {
    enqueue(q1, dequeue(tmp1));
  }
  while(!queue_is_empty(tmp2)) {
    enqueue(q2, dequeue(tmp2));
  }

  queue_free(tmp1);
  queue_free(tmp2);

  return is_equal;
}

char* queue_str_to_string(queue_str_t* q) {
  queue_str_t* tmp = queue_create();
  char* res_str = malloc(sizeof(char));
  res_str[0] = 0;

  // Iterate over all elements and cat them
  while(!queue_is_empty(q)) {
    char* curr_str = dequeue(q);
    
    // Append str
    int dest_len = strlen(res_str);
    int src_len = strlen(curr_str);

    res_str = realloc(res_str, (dest_len + src_len + 1) * sizeof(char));
    strcat(res_str, curr_str);

    enqueue(tmp, curr_str);
  }

  // Return elements to original queue
  while(!queue_is_empty(tmp)) {
    enqueue(q, dequeue(tmp));
  }

  queue_free(tmp);

  return res_str;
}


/* Question 2 */

BTnode_t* find(BTnode_t* root, bool (*pred)(int)) {
  if (root == NULL) return NULL;

  if (pred(root->value)) return root;
  else {
    BTnode_t* left = find(root->left, pred);
    if (left != NULL) return left;

    BTnode_t* right = find(root->right, pred);
    if (right != NULL) return right;
  }

  // Else return null
  return NULL;
}  


void map(BTnode_t* root, int (*f)(int)) {
  if (root == NULL) return; // Do nothing

  // Apply f to current value
  root->value = f(root->value);

  // Apply to children
  map(root->left, f);
  map(root->right, f);
}


int sum_of_leaves(const BTnode_t* root) {
  long res = 0;

  // Left and right are NULL if it a leaf
  if (root->left == NULL && root->right == NULL) res += root->value;
  else {
    res = sum_of_leaves(root->left) + sum_of_leaves(root->right);
  }

  return res;
}


/* Question 3 */

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