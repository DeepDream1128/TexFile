#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <concepts>

// 函数用于交换两个元素
void swap_elements(auto a, auto b) {
    auto temp = std::move(*a);
    *a = std::move(*b);
    *b = std::move(temp);
}

auto random_choice(auto begin, auto end) {
    std::size_t length = end - begin;
    std::size_t idx = std::rand() % length;
    return begin + idx;
}

auto custom_partition(auto begin, auto end, auto compare) {
    auto pivotIndex = random_choice(begin, end);
    swap_elements(begin, pivotIndex);
    auto pivot = begin;
    auto i = begin + 1;

    for (auto j = begin + 1; j != end; ++j) {
        if (compare(*j, *pivot)) {
            swap_elements(j, i);
            ++i;
        }
    }

    swap_elements(begin, i - 1);
    return i - 1;
}

void quick_sort(auto begin, auto end, auto compare) {
    if (std::distance(begin, end) > 1) {
        auto p = custom_partition(begin, end, compare);
        quick_sort(begin, p, compare);
        quick_sort(p + 1, end, compare);
    }
}

void quick_sort(auto begin, auto end) {
    quick_sort(begin, end, std::less<>{});
}
