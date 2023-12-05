#include <list>
#include <future>
#include <algorithm>
#include <future>
#include <iostream>
#include <thread>
#include <iterator>
#include <random>

template<typename T>
void parallel_quick_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end) {
    if (beg == end || std::prev(end) == beg) {
        return ;
    }
    auto pivot = *beg;

    //partition the input array
    auto divide_point = std::partition(
        beg, 
        end, 
        [&](T const& t) {return t < pivot; });

    //apply async to recursive
    auto handle = std::async(
            std::launch::async|std::launch::deferred, 
            &parallel_quick_sort_1<T>, 
            std::next(divide_point), 
            end);

    parallel_quick_sort_1<T>(beg, divide_point);

    handle.get();
    return;  
}

template<typename T>
void parallel_quick_sort_2(typename std::list<T>::iterator beg, typename std::list<T>::iterator end) {
    if (beg == end || std::prev(end) == beg) {
        return ;
    }
    auto pivot = *beg;

    //partition the input array
    auto divide_point = std::partition(
        beg, 
        end, 
        [&](T const& t) {return t < pivot; });

        

    parallel_quick_sort_2<T>(beg, divide_point);

    //apply async to recursive
    auto handle = std::async(
            std::launch::async|std::launch::deferred, 
            &parallel_quick_sort_2<T>, 
            std::next(divide_point), 
            end);

    handle.get();
    return;  
}

template<typename T>
std::list<T> parallel_quick_sort_3(std::list<T> input) {
    if (input.size() < 2) {
        return input;
    }
    //move first element in the list to result list and take it as pivot value
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    //partition the input array
    auto divide_point = std::partition(
        input.begin(), 
        input.end(), 
        [&](T const& t) {return t < pivot; });

    //move lower part of the list to separate list so that we can make recursive call
    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    auto new_lower = parallel_quick_sort_3<T>(std::move(lower_list));
    //apply async to recursive
    auto new_upper_future = 
        std::async(
            std::launch::async|std::launch::deferred, 
            &parallel_quick_sort_3<T>, 
            std::move(input));

    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper_future.get());

    return result;  
}

template<typename T>
std::list<T> parallel_quick_sort_4(std::list<T> input) {
    if (input.size() < 2) {
        return input;
    }
    //move first element in the list to result list and take it as pivot value
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    //partition the input array
    auto divide_point = std::partition(
        input.begin(), 
        input.end(), 
        [&](T const& t) {return t < pivot; });

    //move lower part of the list to separate list so that we can make recursive call
    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    //apply async to recursive
    auto new_upper_future = 
        std::async(
            std::launch::async|std::launch::deferred, 
            &parallel_quick_sort_4<T>, 
            std::move(input));

    auto new_lower = parallel_quick_sort_4<T>(std::move(lower_list));


    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper_future.get());

    return result;  
}

int main() {

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