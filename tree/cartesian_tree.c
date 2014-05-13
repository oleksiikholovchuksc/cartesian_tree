/* 
 *  An implementation of functions defined in "cartesian_tree.h",
 *  see it for more precise explanation of each of them.
 *
 *  Author: Aleksey Kholovchuk (vortexxx192@gmail.com)
 */


#include <time.h>
#include <stdlib.h>
#include <limits.h>

#include "cartesian_tree.h"


pNODE construct_tree(void) {
  srand(time(0));   /* treap is a randomized data structure, remember? */

  pNODE root = (pNODE)malloc(sizeof(NODE));
  root->key = root->priority = LONG_MIN;
  root->assoc = NULL;
  root->left = root->right = NULL;

  return root;
}


char insert(pNODE root, long key, void* assoc) {
  /* nope, Mr. Duplicate, we don't wanna see you at our party */
  if(find(root, key))
    return -1;

  /* constructing a new node */
  pNODE fresh_node = (pNODE)malloc(sizeof(NODE));
  fresh_node->key = key;
  fresh_node->priority = ((rand() << 15) | rand());
  fresh_node->assoc = assoc;

  /* searching for the proper place for new node */
  ppNODE T = &(root->right);
  while(1) {
    /* if we're at the bottom */
    if(!*T) {
      *T = fresh_node;
      return 0;
    }

    if((*T)->priority > fresh_node->priority)
      break;

    /* choosing the right direction */
    T = (fresh_node->key < (*T)->key) ? &((*T)->left) : &((*T)->right);
  }

  /* placing new node to its place */
  pNODE to_split = *T;
  *T = fresh_node;

  /* splitting a treap into two smaller treaps, 
     those smaller than `key', and those larger than `key' */
  ppNODE left_subt = &((*T)->left);
  ppNODE right_subt = &((*T)->right);

  while(to_split) {
    if(to_split->key < key) {
      *left_subt = to_split;
      left_subt = &((*left_subt)->right);
      to_split = to_split->right;
    } else {
      *right_subt = to_split;
      right_subt = &((*right_subt)->left);
      to_split = to_split->left;
    }
  }

  return 0;
}


char erase(pNODE root, long key) {
  /* searching for the node */
  pNODE pos = root;
  ppNODE pred_link;
  while(pos) {
    if(pos->left)
      if(pos->left->key == key) {
	pred_link = &(pos->left);
	pos = pos->left;
	break;
      }

    if(pos->right)
      if(pos->right->key == key) {
	pred_link = &(pos->right);
	pos = pos->right;
	break;
      }
    
    pos = (key < pos->key) ? pos->left : pos->right;
  }
  
  /* if there is no node with such key */
  if(!pos)
    return -1;

  pNODE to_free = pos;

  /* performing a `merge' operation */
  pNODE left_subt = pos->left;
  pNODE right_subt = pos->right;
  
  while(1) {
    if(!left_subt || !right_subt) {
      *pred_link = left_subt ? left_subt : right_subt;
      break;
    }

    if(left_subt->priority < right_subt->priority) {
      *pred_link = left_subt;
      pred_link = &(left_subt->right);
      left_subt = left_subt->right;
    } else {
      *pred_link = right_subt;
      pred_link = &(right_subt->left);
      right_subt = right_subt->left;
    }
  }

  /* sorry friend, we don't need you anymore */
  free(to_free);

  return 0;
}


pNODE find(pNODE root, long key) {
  pNODE T = root;

  /* lookup like in ordinary BST */
  while(T) {
    if(key == T->key)
      return T;

    T = (key < T->key) ? T->left : T->right;
  }
  return NULL;
}


void destruct_tree(pNODE T) {
  /* recursive depth-first traversal */

  if(!T)
    return;

  if(T->left)
    destruct_tree(T->left);
  
  if(T->right)
    destruct_tree(T->right);

  free(T);
}
