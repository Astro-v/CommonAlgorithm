#ifndef __QUICK_SORT_HPP__
#define __QUICK_SORT_HPP__

#include <list>
#include <future>
#include <algorithm>
#include <future>
#include <iostream>
#include <thread>
#include <iterator>

template <typename T>
void quick_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end);

template<typename T>
std::list<T> quick_sort_2(std::list<T> input);

#include "QuickSort.ipp"

#endif // __QUICK_SORT_HPP__