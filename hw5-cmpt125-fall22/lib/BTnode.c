#include <stdio.h>
#include <stdlib.h>

#include "BTnode.h"

BTnode_t* create_node(int val) {
    BTnode_t* newNode = (BTnode_t*) malloc(sizeof(BTnode_t));
    newNode->value = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

void set_left_child(BTnode_t* parent, BTnode_t* left_child) {
  if (parent)
    parent->left = left_child;
  if (left_child)
    left_child->parent = parent;
}

void set_right_child(BTnode_t* parent, BTnode_t* right_child) {
  if (parent)
    parent->right = right_child;
  if (right_child)
    right_child->parent = parent;
}

void BT_free(BTnode_t* root) {
  if (root==NULL)
    return;
  BT_free(root->left);
  BT_free(root->right);
  free(root);
}


void print_pre_order(BTnode_t* root) {
  if (root == NULL)
    return;  

  printf("%d ", root->value);
  print_pre_order(root->left);
  print_pre_order(root->right);
}

void print_in_order(BTnode_t* root) {
  if (root == NULL)
    return;  

  print_in_order(root->left);
  printf("%d ", root->value);
  print_in_order(root->right);
}

void print_post_order(BTnode_t* root) {
  if (root == NULL)
    return;  

  print_post_order(root->left);
  print_post_order(root->right);
  printf("%d ", root->value);
}
