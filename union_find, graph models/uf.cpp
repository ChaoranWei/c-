#include <string>
#include <sstream>
#include <iostream>

#include "union_find.hpp"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main (int argc, char **argv)
{
  std::string line;
  unsigned long int N;
  unsigned long int p, q;

  getline(cin, line); 
  std::stringstream(line) >> N;
  Union_Find uf(N);

  while (getline(cin, line)) {
    std::stringstream(line) >> p >> q;
    uf.onion(p, q);
  }
  cout << "number of components: " << uf.num_components() << endl;
  cout << uf;

  return 0;
}
