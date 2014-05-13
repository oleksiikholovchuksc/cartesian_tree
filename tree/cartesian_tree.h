/*
 *  "cartesian_tree" is an implementation of quasi-balanced BST
 *  called Cartesian Tree or Treap (tree + heap).
 *  Learn more about it: http://en.wikipedia.org/wiki/Treap
 *
 *  One can use it both as SET or MAP data structure, 
 *  (each node keeps a pointer to user's data).
 *
 *  Supported operations:
 *  - insert an element                             O(log N)
 *  - lookup for an element with a particular key   O(log N)
 *  - erase an element with a particular key        O(log N)
 *
 *  Treap is a randomized data structure, so
 *  DON'T FORGET TO CALL srand() BEFORE YOU USE IT.
 *
 *  Author: Aleksey Kholovchuk (vortexxx192@gmail.com)
 */

#ifndef _CARTESIAN_TREE_H_
#define _CARTESIAN_TREE_H_

#include <limits.h>


/* Makes it easier to change later */
typedef long tkey_t;    /* try to call it key_t and you'll get name conflict */
#define TKEY_T_MIN LONG_MIN

/* Each node of the tree has the following structure: */
typedef struct Node {
  tkey_t key, priority;   /* priority is a kind of `technical' information */
  void* assoc;          /* pointer to a user's data (imagine MAP) */
  struct Node *left, *right;   /* links to the left and right child */
} NODE;

typedef NODE*   pNODE;
typedef NODE** ppNODE;


/* Returns a pointer to the tree consisting only from the root */
pNODE construct_tree(void);

/* Inserts new element to the tree. 
   If there isn't no node with such key, returns pointer
   to newly inserted node and sets flag `insertion_was' to 0.
   Otherwise, returns pointer to existing node with such key
   and sets the flag to 1. */
pNODE insert(pNODE root, tkey_t key, void* data, char* insertion_was);

/* Erases a node with a particular key.
   If there is a node in a tree with such key, returns pointer
   to user's data stored in the node and sets `erased' flag to 1.
   Otherwise, sets the flag to 0 and returns NULL. */
void* erase(pNODE root, tkey_t key, char* erased);

/* Returns a pointer to node with the particular key
   or NULL if there is no such node. */
pNODE find(pNODE root, tkey_t key);

/* Clean up. One should call this function every time 
   when the tree isn't needed no more. */
void destruct_tree(pNODE root);


#endif
