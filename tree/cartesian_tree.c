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
  pNODE root = (pNODE)malloc(sizeof(NODE));
  root->key = root->priority = TKEY_T_MIN;
  root->assoc = NULL;
  root->left = root->right = NULL;

  return root;
}


pNODE insert(pNODE root, tkey_t key, void* assoc, char* insertion_was) {
  /* nope, Mr. Duplicate, we don't wanna see you at our party */
  pNODE search_res = find(root, key);
  if(search_res) {
    *insertion_was = 0;
    return search_res;
  }

  /* constructing a new node */
  pNODE fresh_node = (pNODE)malloc(sizeof(NODE));
  fresh_node->key = key;
  fresh_node->priority = ((rand() << 15) | rand());
  fresh_node->left = fresh_node->right = NULL;
  fresh_node->assoc = assoc;

  /* searching for the proper place for new node */
  ppNODE T = &(root->right);

  while(1) {
    /* if we're at the bottom */
    if(!*T) {
      *T = fresh_node;
      *insertion_was = 1;
      return fresh_node;
    }

    if(fresh_node->priority < (*T)->priority)
      break;

    /* choosing correct direction */
    T = (fresh_node->key < (*T)->key) ? &((*T)->left) : &((*T)->right);
  }

  /* placing new node to its place */
  pNODE to_split = *T;
  *T = fresh_node;

  /* splitting a treap into two smaller treaps, 
     those smaller than `key', and those larger than `key' */
  ppNODE left_subt = &((*T)->left);
  ppNODE right_subt = &((*T)->right);
  *right_subt = *left_subt = NULL;

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

  *insertion_was = 1;
  return fresh_node;
}


void* erase(pNODE root, tkey_t key, char* erased) {
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
  if(!pos) {
    *erased = 0;
    return NULL;
  }

  pNODE to_free = pos;
  void* users_data = pos->assoc;

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

  *erased = 1;
  return users_data;
}


pNODE find(pNODE root, tkey_t key) {
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
