template<typename T>
void quick_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end) {
    if (beg == end || std::prev(end) == beg) {
        return ;
    }
    auto pivot = *beg;

    //partition the input array
    auto divide_point = std::partition(
        std::next(beg), 
        end, 
        [&](T const& t) {return t < pivot; });

    std::iter_swap(beg, std::prev(divide_point));

    quick_sort_1<T>(beg, std::prev(divide_point));
    quick_sort_1<T>(divide_point, end);

    return;  
}

template<typename T>
std::list<T> quick_sort_2(std::list<T> input) {
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

    auto new_lower = quick_sort_2<T>(std::move(lower_list));
    auto new_upper = quick_sort_2<T>(std::move(input));


    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper);

    return result;  
}