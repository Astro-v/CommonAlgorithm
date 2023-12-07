template <typename T>
void insertion_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end)
{
    for (auto it1 = std::next(beg); it1 != end; ++it1)
    {
        for (auto it2 = it1; it2 != beg && *std::prev(it2) > *it2; --it2)
        {
            std::iter_swap(it2, std::prev(it2));
        }
    }
}

template <typename T>
std::list<T> insertion_sort_2(std::list<T> input)
{
    for (auto it1 = std::next(input.begin()); it1 != input.end(); ++it1)
    {
        for (auto it2 = it1; it2 != input.begin() && *std::prev(it2) > *it2; --it2)
        {
            std::iter_swap(it2, std::prev(it2));
        }
    }

    return input;
}