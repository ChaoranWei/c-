#if !defined(__UNION_FIND_HPP)
#define __UNION_FIND_HPP

#include <iostream>
#include <vector>

#include "vertex.hpp"

using Component = long int;

// This class is union-find with union by size (i.e., the number of nodes in the subtrees).
//  - Your find() should perform path compression.
//  - Your onion() will need to decrement ncomponents appropriately when components are merged.
//  - Your onion() will also need to increment the tree size (stored as a negative number in the root)
//    as needed.

class Union_Find {
public:
  // Overload the << operator using a friend function.  A friend function is not a member of the class, 
  // but can access all the data and function members of the class.
  // If uf is a Union_Find object, then cout << uf writes uf.s to the screen.
  friend std::ostream &operator<<(std::ostream &os, const Union_Find &uf) {
    for (auto &i : uf.s) { 
      os << i << " ";
    }
    os << std::endl;
    return os;
  }

  // Constructor to create and initialize a union-find object for N vertices.
  // The simplest way to initialize s[] is in the class member initialization list.
  // Initially s[] is all -1, and there are N components.
  Union_Find(long int N) : ncomponents(N), s(N,-1) {}
  
  Component find (const Vertex &p);                // Find operation: return the component id of p, applying path compression.
  void onion (const Vertex &p, const Vertex &q);   // Union operation: union the components containing p and q.
  inline bool connected (const Vertex &p, const Vertex &q) {return (find(p) == find(q));} // Are p and q are in the same component?
  inline Component num_components() {return ncomponents;} 
  
private:
  Component ncomponents; // Number of connected components.
  std::vector<Vertex> s;
};

#endif
