#include <iostream>
#include "minHeap.h"

int main()
{
    unordered_map<int, int> ratingScore = {make_pair(1, 5), make_pair(2, 3), make_pair(3, 1), make_pair(4, 0)};
    MinHeap heap = MinHeap(ratingScore);
    int* books = heap.recommendBooks(2);

    for (int i = 0; i < 2; ++i)
        cout << i + 1 << ": " << books[i] << endl;
    return 0;
}