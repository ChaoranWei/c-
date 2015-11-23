#include <cstring>  // Needed for C-style strings.
#include <iostream> // Needed for i/o.
using std::cout;
using std::endl;
#include <iomanip>  // Needed for setw.et
using std::setw;

#include "bst.hpp"
void print (TNODE*);
  
// Maximum number of characters that will be read from a line.
#define MAXLINE 32768 

// The while loop in main() will read lines from standard input.  For every word in the line,
// the search key-value pair word-line is inserted into the tree.

int main()
{
  char line[MAXLINE];
  char copy[MAXLINE];
  char sep[] {" "};
  
  TNODE *root {nullptr}; // The root of the BST.

  // The while-loop is pretty much pure C code.
  while (fgets(line, MAXLINE, stdin) != NULL) {
    // Copy the line and remove non-alphabetic characters other than hyphens.
    strcpy(copy, line);
    if (copy[0] != '\0') {
      for (unsigned int i = 0; i < strlen(copy); i++) {
	if (!isalnum(copy[i]) && (copy[i] != '-')) {
	  copy[i] = ' ';
	}
      }

      // Now loop over the words and insert the word-line pair into the BST.
      char *word = strtok(copy, sep);
      while (word != NULL) {
	if (isalpha(word[0])) {
	  root = insert(root, word, line);
	}
	word = strtok(NULL, sep);
      }
    }
  }

  print(root);
  return 0;
}

// Print the BST in ascending order of the search keys.
void print (TNODE *p)
{
  if (p != nullptr) {
    print(p->left);
    LNODE *l {p->head};
    do {
      cout << setw(16) << p->key << "   " << l->val;
      l = l->next;
    } while (l != nullptr);
    print(p->right);
  }
}
