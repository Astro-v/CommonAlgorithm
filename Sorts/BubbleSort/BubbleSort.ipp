template <typename T>
void bubble_sort_1(typename std::list<T>::iterator beg, typename std::list<T>::iterator end)
{
    for (auto it1 = beg; it1 != end; ++it1)
    {
        for (auto it2 = beg; it2 != std::prev(end); ++it2)
        {
            if (*it2 > *std::next(it2))
            {
                std::iter_swap(it2, std::next(it2));
            }
        }
    }
}

template <typename T>
std::list<T> bubble_sort_2(std::list<T> input)
{
    // On crée une copie de la liste
    std::list<T> list_copy(input);
    for (auto it1 = list_copy.begin(); it1 != list_copy.end(); ++it1)
    {
        for (auto it2 = list_copy.begin(); it2 != std::prev(list_copy.end()); ++it2)
        {
            if (*it2 > *std::next(it2))
            {
                std::iter_swap(it2, std::next(it2));
            }
        }
    }
    return list_copy;
}