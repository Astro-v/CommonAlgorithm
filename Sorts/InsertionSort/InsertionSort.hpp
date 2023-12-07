#ifndef __INSERTION_SORT_HPP__
#define __INSERTION_SORT_HPP__

#include <list>

template <typename T>
void insertion_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end);

template <typename T>
std::list<T> insertion_sort_2(std::list<T> input);

#include "InsertionSort.ipp"

#endif  // __INSERTION_SORT_HPP__