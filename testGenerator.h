#include <random>
#include <vector>
#include "heaplist.h"

void generateSomeValues(size_t size, std::vector<int>& arr) {
    std::mt19937 generator(time(0));

    arr.resize(size);

    for (size_t i = 0; i < size; i++)
        arr[i] = generator();
}

void generateHeapOrder(int size, int heapNumber, std::vector<int>& order) {
    order.resize(size);
    std::mt19937 generator(time(0));

    for (int i = 0; i < size; i++)
        order[i] = (generator() % heapNumber + heapNumber) % heapNumber;
}

void generateHeaps(int size, int heapNumber, HeapList& heaps, std::vector<int>& order, std::vector<int>& values) {

    for (int i = 0; i < std::min(heapNumber, size); i++)
        heaps.AddHeap(values[i]);

    for (int i = std::min(heapNumber, size); i < size; i++)
        heaps.Insert(order[i], values[i]);
}

void generateTestSequences(int heapNumber, int number, std::vector<std::pair<int, std::pair<int, int> > >& seq) {
    std::mt19937 generator(time(0));

    seq.resize(number);

    for (int i = 0; i < number; i++) {
        int type = (generator() % 3 + 3) % 3;

        seq[i].first = type;

        int first = (generator() % heapNumber + heapNumber) % heapNumber;
        int second = (generator() % heapNumber + heapNumber) % heapNumber;

        seq[i].second.first = first;
        seq[i].second.second = second;
    }
}