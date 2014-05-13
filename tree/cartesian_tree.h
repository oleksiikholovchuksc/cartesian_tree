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
   Returns 0 if there was no such element in tree and -1 otherwise
   (in such case, nothing is inserted) */
char insert(pNODE, long, void*);

/* Erases a node with a particular key.
   returns 0 if an element with key `key' was deleted 
   and -1 otherwise. */
char erase(pNODE, long);

/* Returns a pointer to node with the particular key
   or NULL if there is no such node. */
pNODE find(pNODE, long);

/* Clean up. One should call this function every time 
   when the tree isn't needed no more. */
void destruct_tree(pNODE);


#endif
