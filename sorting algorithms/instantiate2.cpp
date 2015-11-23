#include "sort1.cpp"

#include<string>
#include <vector>

// If you want to use a particular instantiation of one of the sorting 
// routines in your test code, you will need to explicitly instantiate 
// it here.  For instance, if you want to sort a vector of floats using 
// quicksort, you would add
//    template void quicksort<float>(std::vector<float>&);

template void insertion_sort<int>(std::vector<int>&);
template void insertion_sort<std::string>(std::vector<std::string>&);
