#include "bs_tree.h"
#include <list>
#include <iostream>

using namespace std;

bs_tree::bs_tree() { 
  T_nil = new bs_tree_node();
  T_nil->p = T_nil;
  T_nil->left = T_nil;
  T_nil->right = T_nil;
  T_root = T_nil;
}

bs_tree::~bs_tree() { 
  remove_all(T_root);
  delete T_nil;
}

void bs_tree::insert(bs_tree_node* z, bs_tree_i_info& t_info) {
  bs_tree_node* x = T_root;
  bs_tree_node* y = T_nil;

  while (x != T_nil) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else if (z->key > x->key)
      x = x->right;
    else {
      t_info.i_duplicate++;
      delete z; // Duplicate found, free the memory allocated for z
      return;
    }
  }

  z->p = y;
  if (y == T_nil)
    T_root = z;
  else {
    if (z->key < y->key)
      y->left = z;
    else
      y->right = z;
  }

  z->left = T_nil;
  z->right = T_nil;
}

void bs_tree::insert(int key, bs_tree_i_info& t_info) {
  bs_tree_node* z = new bs_tree_node;
  z->key = key;
  insert(z, t_info);
}

int bs_tree::inorder_output(bs_tree_node* x, int level, int* array, int index) {
  if (x != T_nil) {
    index = inorder_output(x->left, level + 1, array, index);
    array[index++] = x->key;
    index = inorder_output(x->right, level + 1, array, index);
  }
  return index;
}

void bs_tree::remove_all(bs_tree_node* x) {
  if (x != T_nil) {
    remove_all(x->left);
    remove_all(x->right);
    delete x;
  }
}

int bs_tree::convert(int* array, int n) {
  int count = 0;
  if (T_root != T_nil) {
    count = inorder_output(T_root, 1, array, 0);
  }
  return count;
}
