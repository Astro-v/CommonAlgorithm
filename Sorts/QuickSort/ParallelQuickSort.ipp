template <typename T>
void parallel_quick_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end)
{
    if (beg == end || std::prev(end) == beg)
    {
        return;
    }
    auto pivot = *beg;

    // partition the input array
    auto divide_point = std::partition(std::next(beg), end, [&](T const& t) { return t < pivot; });

    std::iter_swap(beg, std::prev(divide_point));

    // apply async to recursive
    auto handle = std::async(std::launch::async | std::launch::deferred, &parallel_quick_sort_1<T>, divide_point, end);

    parallel_quick_sort_1<T>(beg, std::prev(divide_point));

    handle.get();
    return;
}

template <typename T>
void parallel_quick_sort_2(typename std::list<T>::iterator beg, typename std::list<T>::iterator end)
{
    if (beg == end || std::prev(end) == beg)
    {
        return;
    }
    auto pivot = *beg;

    // partition the input array
    auto divide_point = std::partition(std::next(beg), end, [&](T const& t) { return t < pivot; });

    std::iter_swap(beg, std::prev(divide_point));

    parallel_quick_sort_2<T>(beg, std::prev(divide_point));

    // apply async to recursive
    auto handle = std::async(std::launch::async | std::launch::deferred, &parallel_quick_sort_2<T>, divide_point, end);

    handle.get();
    return;
}

template <typename T>
std::list<T> parallel_quick_sort_3(std::list<T> input)
{
    if (input.size() < 2)
    {
        return input;
    }
    // move first element in the list to result list and take it as pivot value
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    // partition the input array
    auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });

    // move lower part of the list to separate list so that we can make recursive call
    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    auto new_lower = parallel_quick_sort_3<T>(std::move(lower_list));
    // apply async to recursive
    auto new_upper_future = std::async(std::launch::async | std::launch::deferred, &parallel_quick_sort_3<T>, std::move(input));

    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper_future.get());

    return result;
}

template <typename T>
std::list<T> parallel_quick_sort_4(std::list<T> input)
{
    if (input.size() < 2)
    {
        return input;
    }
    // move first element in the list to result list and take it as pivot value
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    // partition the input array
    auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });

    // move lower part of the list to separate list so that we can make recursive call
    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    // apply async to recursive
    auto new_upper_future = std::async(std::launch::async | std::launch::deferred, &parallel_quick_sort_4<T>, std::move(input));

    auto new_lower = parallel_quick_sort_4<T>(std::move(lower_list));

    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper_future.get());

    return result;
}

template <typename T>
void parallel_quick_sort_5(typename std::list<T>::iterator beg, typename std::list<T>::iterator end, int depth)
{
    if (beg == end || std::prev(end) == beg)
    {
        return;
    }
    auto pivot = *beg;

    // partition the input array
    auto divide_point = std::partition(std::next(beg), end, [&](T const& t) { return t < pivot; });

    std::iter_swap(beg, std::prev(divide_point));

    if (depth > 0)
    {
        // apply async to recursive
        auto handle = std::async(std::launch::async | std::launch::deferred, &parallel_quick_sort_5<T>, divide_point, end, depth - 1);
        parallel_quick_sort_5<T>(beg, std::prev(divide_point), depth - 1);
        handle.get();
    }
    else
    {
        parallel_quick_sort_5<T>(divide_point, end, depth - 1);
        parallel_quick_sort_5<T>(beg, std::prev(divide_point), depth - 1);
    }

    return;
}