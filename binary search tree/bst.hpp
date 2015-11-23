#if !defined(__BST_CSCI303)
#define __BST_CSCI303

// IMPORTANT: You should not edit this file.  I will be grading
// with my own copy of bst.hpp, so if your code relies on
// modifications you make here, it will not work when being graded.

// Make KEY and VALUE synonyms for the type char*.
using KEY   = char*;
using VALUE = char*;

// LNODE is a node in a singly linked list.
struct lnode {
  VALUE val;          // Pointer to the value stored in the node.
  struct lnode *next; // Pointer to the next node; it should
                      // be nullptr if there is no successor.
};
using LNODE = lnode; // Make LNODE a synonym for struct lnode.

// TNODE is a node in a binary search tree.
struct tnode {
  KEY key; // Search key for node.

  // If a child is missing, the pointer should be a nullptr.
  struct tnode *right; // Pointer to the right child.
  struct tnode *left;  // Pointer to the left child.

  LNODE *head; // Head of the linked list where values are stored.
  LNODE *tail; // Tail of the linked list where values are stored.
};
using TNODE = tnode; // Make TNODE a synonym for struct tnode.

// Public API.
TNODE *insert(TNODE*, KEY, VALUE);
TNODE *find(TNODE*, KEY);
void remove(TNODE*, KEY);
long int height(TNODE*);
void free(TNODE*);

#endif
