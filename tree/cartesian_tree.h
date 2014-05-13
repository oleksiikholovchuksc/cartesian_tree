/*
 *  "cartesian_tree" is an implementation of quasi-balanced BST
 *  called Cartesian Tree or Treap (tree + heap).
 *  Learn more about it: http://en.wikipedia.org/wiki/Treap
 *
 *  One can use it both as SET or MAP data structure, 
 *  (each node keeps a pointer to user's data).
 *
 *  Supported operations:
 *  - insert an element
 *  - lookup for an element with a particular key
 *  - erase an element with a particular key
 *
 *
 *  Author: Aleksey Kholovchuk (vortexxx192@gmail.com)
 */

#ifndef _CARTESIAN_TREE_H_
#define _CARTESIAN_TREE_H_

/* Each node of the tree has the following structure: */
typedef struct Node {
  long key, priority;   /* priority is a kind of `technical' information */
  void* assoc;          /* pointer to a user's data (imagine MAP) */
  struct Node *left, *right;   /* links to the left and right child */
} NODE;

typedef NODE*   pNODE;
typedef NODE** ppNODE;

/* Returns a pointer to the tree consisting only from the root */
pNODE construct_tree(void);

/* Inserts new element to the tree. 
   If there isn't no node with such a key, returns pointer
   to newly inserted node and sets flag `insertion_was' to 0.
   Otherwise, returns pointer to existing node with such key
   and sets the flag to 1. */
pNODE insert(pNODE root, long key, void* data, char* insertion_was);

/* Erases a node with a particular key.
   Returns user's data stored in deleted node  if an element 
   with key `key' was deleted and NULL otherwise. */
void* erase(pNODE root, long key);

/* Returns a pointer to node with the particular key
   or NULL if there is no such node. */
pNODE find(pNODE root, long key);

/* Clean up. One should call this function every time 
   when the tree isn't needed no more. */
void destruct_tree(pNODE root);


#endif
