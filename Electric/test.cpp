#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>

auto random_choice(auto begin, auto end) {
    std::size_t length = std::distance(begin, end);
    std::size_t idx = std::rand() % length;
    return std::next(begin, idx);
}

void quick_sort(std::random_access_iterator auto begin, std::random_access_iterator auto end, auto compare) {
    if (begin < end - 1) {
        auto pivot_value = *random_choice(begin, end);
        auto i = begin;
        auto j = end - 1;

        while (i <= j) {
            while (compare(*i, pivot_value)) i++;
            while (compare(pivot_value, *j)) j--;
            if (i < j) {
                std::swap(*i, *j);
                i++;
                j--;
            } else if (i == j) {
                i++;
            }
        }

        quick_sort(begin, j + 1, compare);
        quick_sort(i, end, compare);
    }
}


void quick_sort_x(std::random_access_iterator auto begin, std::random_access_iterator auto end) {
    quick_sort(begin, end, std::less<>{});
}

int main(){
    std::vector<int> v{8, 3, 1, 2, 5, 4, 7, 6};
    quick_sort_x(v.begin(), v.end());
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}