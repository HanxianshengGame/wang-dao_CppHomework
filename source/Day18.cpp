// Authors: Handling
// Created by 15870 on 2020/10/8.
// This is container

#include <functional>
#include <algorithm>
namespace heapsort {
template <typename T, typename Compare = std::less<T> >
class HeapSort {
 private:
  T *arr_;
  size_t  arr_sz_;
  Compare comp_;
 public:
  HeapSort(T *arr, size_t arr_sz, Compare compare):
           arr_(arr), arr_sz_(arr_sz), comp_(compare) {}
  void HeapAdjust(int pos, int heap_sz);
  void Sort();
};
template<typename T, typename Compare>
void HeapSort<T, Compare>::HeapAdjust(int pos, int heap_sz) {
  int dad = pos;
  int son = pos * 2 + 1;
  while(son < arr_sz_) {
    if(son + 1 < arr_sz_ && comp_(arr_[son + 1],arr_[son]))
      ++son;
    if(comp_(arr_[dad], arr_[son])) {
      std::swap(arr_[dad], arr_[son]);
      dad = son;
      son = dad * 2 + 1;
    } else {
      break;
    }
  }
}
template<typename T, typename Compare>
void HeapSort<T, Compare>::Sort() {

  int heap_sz = arr_sz_;
  for(int i = arr_sz_/2 - 1; i >= 0; --i) {
    HeapAdjust(i, heap_sz);
  }


  std::swap(arr_[0], arr_[heap_sz -1]);
  for(int i = heap_sz - 1; i > 2; --i) {
    HeapAdjust(0, i);
    std::swap(arr_[0], arr_[i-1]);
  }

}

}
namespace quicksort {
template <typename T, typename Compare = std::less<T> >
class QuickSort {
 private:
  Compare comp_;
  T *arr_;
  size_t  arr_sz_;
 public:
  QuickSort(T *arr, size_t arr_sz, Compare compare) :
            arr_(arr), arr_sz_(arr_sz), comp_(compare) {}

  void Sort();
 private:
  void Sort(T *first, T *last);
};
template<typename T, typename Compare>
void QuickSort<T, Compare>::Sort() {
  Sort(arr_, arr_ + arr_sz_);
}
template<typename T, typename Compare>
void QuickSort<T, Compare>::Sort(T *first, T *last) {
  if(last - first <= 1)
	return;
  auto pivot = std::partition(first, last, comp_);
  if(pivot - first > 2)
    Sort(first, pivot);
  if(last - (pivot + 1) > 2)
    Sort(pivot + 1, last);
}

}