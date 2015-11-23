#include "sort.cpp"

#include<string>

// If you want to use a particular instantiation of one of the sorting 
// routines in your test code, you will need to explicitly instantiate 
// it here.  For instance, if you want to sort a vector of floats using 
// quicksort, you would add
//    template void quicksort<float>(std::vector<float>&);

template void mergesort_iterative<int>(std::vector<int>&);
template void mergesort_recursive<int>(std::vector<int>&);
template void mergesort_iterative<double>(std::vector<double>&);
template void mergesort_recursive<double>(std::vector<double>&);

template void quicksort<int>(std::vector<int>&);
template void quicksort<double>(std::vector<double>&);
template void quicksort<std::string>(std::vector<std::string>&);

