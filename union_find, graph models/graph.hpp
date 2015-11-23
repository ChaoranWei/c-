#if !defined(__GRAPH_HPP)
#define __GRAPH_HPP

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "edge.hpp"

class Graph {
  friend std::ostream &operator<<(ostream &os, const Graph &G) {
    os << "graph: " << G.name << " {\n";
    os << " V: " << G.V << '\n';
    os << " E: " << G.E << '\n';
    os << " adjacency list = {" << '\n';
    for (long int v = 0; v < G.V; v++) {
      os << "  " << v << ": ";
      if (!G.adj[v].empty()) {
	for (auto &w : G.adj[v]) {
	  os << w << ' ';
	}
      }
      os << std::endl;
    }
    os << " }" << '\n';
    os << "}" << std::endl;

    return os;
  };

public:
  Graph(std::string name = "G") : name(name), E(0), V(0) {} // Dig the default argument.
  
  inline int num_edges() const {return E;}
  inline int num_vertices() const {return V;}
  virtual void add_edge(const Edge &e); // Add an edge by adding it to edges[] and updating adj[], resizing either as needed.

protected:
  std::string name;     // The name of the graph.
  long int E;           // The number o' edges.
  long int V;           // The number o' vertices.  The vertices are denoted by long ints in the range 0 to V-1.
  std::vector<std::list<Vertex>> adj; // The adjacency list.
  std::vector<Edge> edges;       // The edges.
};

class Digraph : public Graph {
public:
  Digraph(std::string name = "G") : Graph(name) {}; 
  
  virtual void add_edge(const Edge &e);
  std::vector<Vertex> tsort();

protected:
  std::vector<Directed_Edge> edges;       // The edges.
};

class Weighted_Graph : public Graph {
public:
  Weighted_Graph(std::string name = "G") : Graph(name) {}; 

protected:
  std::vector<Weighted_Edge> edges;       // The edges.
};

class Weighted_Digraph : public Digraph {
public:
  Weighted_Digraph(std::string name = "G") : Digraph(name) {}; 

protected:
  std::vector<Directed_Weighted_Edge> edges;       // The edges.
};

#endif
