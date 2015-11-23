#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cin; 
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

#include "sort.hpp"

template <typename T> bool are_identical (vector<T> &a, vector<T> &b);
template <typename T> void test(long int &n); // function prototype
template <> void test<string>(long int &n);   // function prototype (template specialization)

int main (int argc, char **argv) {
  long int n;

  // Prompt the user for the size of the list.
  cout << "Enter the problem size: ";
  cin >> n;                          

  if (n < 0) {
    cerr << "Bogus problem size specified. Say \"bye-bye\" to the nice program!" << endl;
    return (16);
  }

  //---------------------------------------------
  // Test integer instantiation.
  cout << "---------------------------------------------------\n";
  cout << "Testing integer instantiation...\n" << endl;
  test<int>(n);

  //---------------------------------------------
  // Test double instantiation.
  cout << "---------------------------------------------------\n";
  cout << "Testing double instantiation...\n" << endl;
  test<double>(n);

  //---------------------------------------------
  // Test string instantiation.
  cout << "---------------------------------------------------\n";
  cout << "Testing string instantiation...\n" << endl;
  test<string>(n);

  return 0;
}

template <typename T>
void test(long int &n)
{
  //----------------------
  // Initialization. 

  // Exception handling?  we don't need no stinkin' exception handling...
  vector<T> v0(n);

  // Fill v0 with random numbers. 
  std::mt19937 e(0); // Everyone's favorite pseudo-random number engine: the Mersenne twister.
  std::uniform_int_distribution<int> u(-100000,100000); // Convert engine output to a uniform integer distribution.
  auto t_start = std::chrono::high_resolution_clock::now();
  for (auto &w : v0) { // Range-for (new in C++11).
    w = u(e);
  }
  auto t_end = std::chrono::high_resolution_clock::now();
  cout << "Initialization:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //----------------------------------------------------------------
  // Use the vector member function sort() to check our work.

  vector<T> v1(v0); // Copy constructor for the vector template class; v1 is a clone of v0.
  
  t_start = std::chrono::high_resolution_clock::now(); // love them ::...
  std::sort(v1.begin(), v1.end());
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Library sort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() << "ms\n";

  //---------------------------------
  // Test the sorts.

  auto v2(v0); // auto: infer the correct type for v2 from the type of v0.

  t_start = std::chrono::high_resolution_clock::now();
  try {
    mergesort_iterative(v2);
    t_end = std::chrono::high_resolution_clock::now();
    cout << "Iterative mergesort:\n";
    cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
    cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "NO!!") << "\n";
  }
  catch (...) {
    cerr << "Ack!  the call to iterative mergesort threw an exception!" << endl;
  }

  v2 = v0;
  t_start = std::chrono::high_resolution_clock::now();
  try {
    mergesort_recursive(v2);
    t_end = std::chrono::high_resolution_clock::now();
    cout << "Recusive mergesort:\n";
    cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
    cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "NO!!") << "\n";
    
  }
  catch (...) {
    cerr << "Ack!  the call to iterative mergesort threw an exception!" << endl;
  }
  v2 = v0;
  t_start = std::chrono::high_resolution_clock::now();
  quicksort(v2);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Quicksort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "NO!!") << "\n";

  // No need to clean up---the vector objects and associated resource are freed automagically!
}

template <>
void test<string>(long int &n)  // Explicit template specialization.
{
  //----------------------
  // Initialization. 

  // The template specialization for strings is needed since generating random strings can't be done with the code above.
  // (Well, you can use the code above to generate random strings, but they aren't printable.)
  // However, I'm too lazy to implement random string generation, so I'll just hardwire a test case.

  vector<string> v0 {"fum", "fie", "fee", "foo", "foe", "bar", "ick", "ack", "yuck"};

  //----------------------------------------------------------------
  // Use the vector member function sort() to check our work.

  vector<string> v1(v0); // Copy constructor for the vector template class; v1 is a clone of v0.
  
  auto t_start = std::chrono::high_resolution_clock::now();
  std::sort(v1.begin(), v1.end());
  auto t_end = std::chrono::high_resolution_clock::now();
  cout << "Library sort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //---------------------------------
  // Apply the sort.

  auto v2(v0);

  t_start = std::chrono::high_resolution_clock::now();
  quicksort(v2);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "User-supplied sort<" << typeid(v0[0]).name() << ">:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "no") << "\n";

  // No need to clean up---the vector objects and associated resource are freed automagically!
}

template <typename T>
bool are_identical (vector<T> &a, vector<T> &b)
{
  for (unsigned long int k = 0; k < a.size(); k++) {
    if (a[k] != b[k]) {
      return false;
    }
  }
  return true;
}
