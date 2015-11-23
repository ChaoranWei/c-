#include "edge.hpp"
#include "graph.hpp"

using std::cin;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
  Directed_Weighted_Edge e;
  Digraph G;

  // Read in directed edges from a file.
  while (cin >> e) {
    cout << e << '\n';
    G.add_edge(e);
  }
  cout << G;

    std::vector<Vertex> S = G.tsort();
    for (auto &v : S) {
   cout << v << '\n';
   }
  return 0;
}
