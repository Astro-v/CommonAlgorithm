#include <random>
#include <iostream>
#include <chrono>
#include <list>

#include "ParallelQuickSort.hpp"
#include "QuickSort.hpp"
#include "BubbleSort.hpp"
#include "InsertionSort.hpp"

#define DEBUG

template<typename T>
void time_sort(void (*sort)(typename std::list<T>::iterator, typename std::list<T>::iterator), std::list<T> list);

template<typename T>
void time_sort(std::list<T> (*sort)(std::list<T>), std::list<T> list);

int main() 
{
    int N = 1000;

    // Génerer une liste aléatoire de 1000 éléments
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1, 1000);
    std::list<double> list;
    for (int n = 0; n < N; ++n) {
        list.push_back(dis(gen));
    }

    // Parrallel Quick Sort
    std::cout << "parallel_quick_sort_1 - ";
    time_sort<double>(parallel_quick_sort_1<double>, list);
    /*std::cout << "parallel_quick_sort_2 - ";
    time_sort<double>(parallel_quick_sort_2<double>, list);
    std::cout << "parallel_quick_sort_3 - ";
    time_sort<double>(parallel_quick_sort_3<double>, list);
    std::cout << "parallel_quick_sort_4 - ";
    time_sort<double>(parallel_quick_sort_4<double>, list);

    // Quick Sort    
    std::cout << "quick_sort_1 - ";
    //time_sort<double>(quick_sort_1<double>, list);
    std::cout << "quick_sort_2 - ";
    //time_sort<double>(quick_sort_2<double>, list);

    // Bubble Sort
    std::cout << "bubble_sort_1 - ";
    time_sort<double>(bubble_sort_1<double>, list);
    std::cout << "bubble_sort_2 - ";
    time_sort<double>(bubble_sort_2<double>, list);

    // Insertion Sort
    std::cout << "insertion_sort_1 - ";
    time_sort<double>(insertion_sort_1<double>, list);*/
}

template<typename T>
void time_sort(void (*sort)(typename std::list<T>::iterator, typename std::list<T>::iterator), std::list<T> list)
{
    // Timer pour mesurer le temps d'exécution
    auto start = std::chrono::high_resolution_clock::now();

    // Trier la liste
    sort(list.begin(), list.end());

    //  Timer pour mesurer le temps d'exécution
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total = end-start;

    std::cout << "Time to sort: " << total.count() << " seconds";

    bool sorted = true;
    for (auto it = list.begin(); it != std::prev(list.end()); ++it)
    {
        if (*it > *std::next(it))
        {
            sorted = false;
            break;
        }
    }
    if (sorted)
    {
        std::cout << " - OK" << std::endl;
    }
    else
    {
        std::cout << " - NOK" << std::endl;
    }

    #ifdef DEBUG
    // Afficher la liste triée
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    #endif
    
}

template<typename T>
void time_sort(std::list<T> (*sort)(std::list<T>), std::list<T> list)
{
    // Timer pour mesurer le temps d'exécution
    auto start = std::chrono::high_resolution_clock::now();

    // Trier la liste
    auto output = sort(list);

    //  Timer pour mesurer le temps d'exécution
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total = end-start;

    std::cout << "Time to sort: " << total.count() << " seconds";

    bool sorted = true;
    for (auto it = output.begin(); it != std::prev(output.end()); ++it)
    {
        if (*it > *std::next(it))
        {
            sorted = false;
            break;
        }
    }
    if (sorted)
    {
        std::cout << " - OK" << std::endl;
    }
    else
    {
        std::cout << " - NOK" << std::endl;
    }
}