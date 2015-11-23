#include <vector>



template <typename T>
void insertion_sort (std::vector<T> &a) {
  for (unsigned long int i = 1; i < a.size(); i++) {
    for (unsigned long int j = i; (j > 0) && (a[j] < a[j - 1]); j--) {
      std::swap(a[j], a[j - 1]);
    }
  }
}
