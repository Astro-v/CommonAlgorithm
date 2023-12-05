#ifndef __PARALLEL_QUICK_SORT_HPP__
#define __PARALLEL_QUICK_SORT_HPP__

#include <list>
#include <future>
#include <algorithm>
#include <future>
#include <iostream>
#include <thread>
#include <iterator>

template <typename T>
void parallel_quick_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end);

template <typename T>
void parallel_quick_sort_2(typename std::list<T>::iterator beg, typename std::list<T>::iterator end);

template<typename T>
std::list<T> parallel_quick_sort_3(std::list<T> input);

template<typename T>
std::list<T> parallel_quick_sort_4(std::list<T> input);

#include "ParallelQuickSort.ipp"

#endif // __PARALLEL_QUICK_SORT_HPP__