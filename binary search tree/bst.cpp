#include "bst.hpp"
#include <cstring>
#include <iostream>
#include <iomanip>


TNODE *find(tnode* TNODE, KEY key) {
  char* k = new char[strlen(key) + 1];
  strcpy(k, key);
  if (TNODE == nullptr || strcmp(k, TNODE->key) == 0) return (TNODE);
  else{
    if (k > TNODE->key) return(find(TNODE->right, k));
    else return (find(TNODE->left, k));
  }
  delete k;
}

TNODE *NODE(KEY k,VALUE v){
  LNODE *newl = new LNODE{v, nullptr};
  TNODE *newt = new TNODE{k, nullptr, nullptr, newl, newl};
  return newt;
}


TNODE *insert(tnode* node, KEY key, VALUE val) {
  char* v = new char[strlen(val) + 1];
  strcpy(v, val);
  char* k = new char[strlen(key) + 1];
  strcpy(k, key);
 
  if (node == nullptr) {
    try {
    TNODE *newnode;
    newnode= NODE(k,v); 
    node = newnode;
    return node;
    }
    catch(...){throw;}
  }
  else if (strcmp(node->key, k) == 0) {
     LNODE *newNode;
     try {
       newNode = new LNODE{v, nullptr};
     }
     catch(...){throw;}
     node->tail->next = newNode;
     node->tail = node->tail->next;
     return node;
    
    }
   
  else {
    if (strcmp(k, node->key) > 0) {
      node->right = insert(node->right, k, v);
    }
    else {
      node->left = insert(node->left, k, v);
    }
    return(node);
  }
  
}


void remove(tnode* TNODE, KEY key) {
  char* k = new char[strlen(key) + 1];
  strcpy(k, key);
  tnode* DELNODE = find(TNODE, k);  

  if (DELNODE->right == nullptr && DELNODE->left == nullptr) {
    // DELNODE = nullptr;  
    delete DELNODE;
  }
  else if (DELNODE->right == nullptr) {
 
    DELNODE = DELNODE->left;
    delete DELNODE;
  }
  else if  (DELNODE->left == nullptr) {
    DELNODE = DELNODE->right;
    delete DELNODE;
  }
  else {
    tnode* temp = DELNODE->right;
    while (temp->left != nullptr) {
      temp = temp->left;
    }
    DELNODE->key = temp->key;
    //   DELNODE->right = temp->right;
    // DELNODE->left = temp->left;
    DELNODE->head = temp->head;
    DELNODE->tail = temp->tail;
    remove(DELNODE, temp->key);
    delete DELNODE;
  }
  delete k;
}

void free(tnode* TNODE) {
  if (TNODE != nullptr) {
    free(TNODE->left);
    free(TNODE->right);
    delete TNODE;
  }
}

long int height(tnode* TNODE) {
  if (TNODE == nullptr) return(-1);
  else {
    return 1 + std::max(height(TNODE->right), height(TNODE->left));
  }
}
