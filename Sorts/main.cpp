#include <random>
#include <iostream>
#include <chrono>
#include <list>

#include "ParallelQuickSort.hpp"


int main() 
{
    // Génerer une liste aléatoire de 1000 éléments
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1, 1000);
    std::list<double> list;
    for (int n = 0; n < 1000; ++n) {
        list.push_back(dis(gen));
    }
    // Copier la liste
    std::list<double> list_1 = list;
    std::list<double> list_2 = list;

    // Timer pour mesurer le temps d'exécution
    auto start = std::chrono::high_resolution_clock::now();

    // Trier la liste
    parallel_quick_sort_1<double>(list_1.begin(), list_1.end());

    //  Timer pour mesurer le temps d'exécution
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total = end-start;

    std::cout << "Time to sort parallel_quick_sort_1: " << total.count() << " s\n";

    // Timer pour mesurer le temps d'exécution
    start = std::chrono::high_resolution_clock::now();

    // Trier la liste
    parallel_quick_sort_2<double>(list_2.begin(), list_2.end());

    //  Timer pour mesurer le temps d'exécution
    end = std::chrono::high_resolution_clock::now();
    total = end-start;
    
    std::cout << "Time to sort parallel_quick_sort_2: " << total.count() << " s\n";

    // Timer pour mesurer le temps d'exécution
    start = std::chrono::high_resolution_clock::now();

    // Trier la liste
    parallel_quick_sort_3<double>(list);

    //  Timer pour mesurer le temps d'exécution
    end = std::chrono::high_resolution_clock::now();
    total = end-start;
    
    std::cout << "Time to sort parallel_quick_sort_3: " << total.count() << " s\n";

        // Timer pour mesurer le temps d'exécution
    start = std::chrono::high_resolution_clock::now();

    // Trier la liste
    parallel_quick_sort_4<double>(list);

    //  Timer pour mesurer le temps d'exécution
    end = std::chrono::high_resolution_clock::now();
    total = end-start;
    
    std::cout << "Time to sort parallel_quick_sort_4: " << total.count() << " s\n";
}