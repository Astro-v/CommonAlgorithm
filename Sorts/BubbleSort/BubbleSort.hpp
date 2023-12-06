#ifndef __BUBBLE_SORT_HPP__
#define __BUBBLE_SORT_HPP__

#include <list>


template <typename T>
void bubble_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end);

template<typename T>
std::list<T> bubble_sort_2(std::list<T> input);

#include "BubbleSort.ipp"

#endif // __BUBBLE_SORT_HPP__