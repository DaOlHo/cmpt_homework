#include <stdio.h>
#include <stdlib.h>

#include "BST.h"

// creates a Binary Search Tree
BST_t* BST_create() {
  BST_t* tree = (BST_t*) malloc(sizeof(BST_t));
  tree->root = NULL;
  return tree;
}

BTnode_t* BST_find(BST_t* tree, int item) {
  BTnode_t* current = tree->root;
  while (current!=NULL) {
    if (current->value == item)
      return current;
    if (current->value > item)
      current = current->left;
    else
      current = current->right;
  }
  // item not found
  return NULL;
}

// inserts item into the Binary Search Tree
void BST_insert(BST_t* tree, int item) {
  if (tree->root == NULL)   { // tree is empty
    tree->root = create_node(item);
    return;
  }
  BTnode_t* current = tree->root;
  BTnode_t* prev = NULL;
  while (current!=NULL)  {
    prev = current;
    // decide to go left or right in the next step 
    if (current->value > item)
      current = current->left;
    else
      current = current->right;
  }
  // now prev holds the lowest node in our path
  if (prev->value > item) {
    set_left_child(prev, create_node(item));
  }
  else {
    set_right_child(prev, create_node(item));
  }
}

// removes item from the Binary Search Tree
void BST_remove(BST_t* tree, int item) {
  // implement me
}


void BST_free(BST_t* tree) {
  BT_free(tree->root);
  free(tree);
}
