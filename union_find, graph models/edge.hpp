#if !defined(__EDGE_HPP)
#define __EDGE_HPP

#include <iostream>
#include <stdexcept>

using std::istream;
using std::ostream;

#include "vertex.hpp"

class Edge {
  friend istream &operator>>(istream &is, Edge &e);
  friend ostream &operator<<(ostream &os, const Edge &e);

public:
  Edge() {}
  Edge(Vertex v, Vertex w) : v(v), w(w) {}
  explicit Edge(const Edge &e) : v(e.v), w(e.w) {}   // Copy constructor.
  
  inline Vertex from() const {return v;}     // Return endpoint v of the edge.
  inline Vertex to()   const {return w;}     // Return endpoint w of the edge.
  Vertex either() const {return v;}          // Return endpoint v of the edge.
  Vertex other(const Vertex vertex) const {  // Return the endpoint other than vertex; throw an exception if vertex isn't an endpoint.
    return ( (vertex == v) ? w : ( (vertex == w) ? v : throw std::runtime_error("Invalid edge!") ) ); 
  }


protected:
  virtual istream &read(istream &is) {
    is >> v >> w;
    return is;
  }

  virtual ostream &print(ostream &os) const {
    os << v << " -- " << w;
    return os;
  }

  Vertex v, w;  // The vertices connected by the edge.
};

// Friend functions cannot be virtual functions, so you cannot have dynamic binding of friend functions.
// The "virtual friend idiom" programming idiom addresses this problem.  In this idiom we have a friend
// function call a virtual function of a class.
inline istream &operator>>(istream &is, Edge &e) {
  return e.read(is);
}

inline ostream &operator<<(ostream &os, const Edge &e) {
  return e.print(os);
}

class Directed_Edge : public Edge {
public:
  Directed_Edge() : Edge() {}
  Directed_Edge(Vertex v, Vertex w) : Edge(v, w) {}
  Directed_Edge(const Edge &e) : Edge(e) {}   // Copy constructor.

protected:
  virtual ostream &print(ostream &os) const {
    os << v << " -> " << w;
    return os;
  }
};

class Weighted_Edge : public Edge {
public:
  Weighted_Edge() : Edge() {}
  Weighted_Edge(Vertex v, Vertex w, double wt) : Edge(v, w), wt(wt) {}

  double weight() const {return wt;}  // Return the weight of the edge.
protected:
  virtual istream &read(istream &is) {
    is >> v >> w >> wt;
    return is;
  }

  virtual ostream &print(ostream &os) const {
    os << v << " -- " << w << " (" << wt << ")";
    return os;
  }

  double wt;    // The weight of the edge.
};
  
class Directed_Weighted_Edge : public Weighted_Edge {
public:
  Directed_Weighted_Edge() : Weighted_Edge() {}
  Directed_Weighted_Edge(Vertex v, Vertex w, double wt) : Weighted_Edge(v, w, wt) {}

protected:
  virtual ostream &print(ostream &os) const {
    os << v << " -> " << w << " (" << wt << ")";
    return os;
  }
};
#endif
