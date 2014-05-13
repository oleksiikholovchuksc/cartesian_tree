/* Test-drive of functions provided by cartesian_tree.h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "tree/cartesian_tree.h"

int main(void) {
  char buf[10];
  pNODE T = construct_tree();
  long key;

  printf("Usage:\nadd <key>\nremove <key>\nlookup <key>\n\n");

  while(1) {
    /* dealing with user */
    scanf("%s %ld", buf, &key);

    if(!strcmp(buf, "add")) {
      char flag;
      pNODE res = insert(T, key, NULL, &flag);
      assert(res->key == key);
      if(flag)
	puts("Inserted, OK.");
      else
	puts("Ooops, a duplicate detected.");
    }
    else if(!strcmp(buf, "remove")) {
      if(!erase(T, key))
	puts("Found and erased, OK.");
      else
	puts("No such element.");
    }
    else if(!strcmp(buf, "lookup")) {
      if(find(T, key))
	puts("Yup, found.");
      else
	puts("Not found.");
    } else {
      destruct_tree(T);
      puts("Bye!");
      exit(0);
    }
  }
}
