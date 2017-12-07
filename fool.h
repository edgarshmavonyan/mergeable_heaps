#include <iostream>
#include "IHeap.h"
#include <vector>
#include <algorithm>
#include <cstring>

class CFoolHeap : public IHeap {
    std::vector<int> heap;

    static bool comp(int a, int b) {
        return a > b;
    }

public:
    CFoolHeap() = default;

    explicit CFoolHeap(int key) : heap(1, key) {}

    void Insert(int key) override {
        heap.push_back(key);
        std::push_heap(heap.begin(), heap.end(), comp);
    }

    int GetMin() override {
        return heap.front();
    }

    int ExtractMin() override {
        std::pop_heap(heap.begin(), heap.end(), comp);
        int result = heap.back();
        heap.pop_back();
        return result;
    }

    ~CFoolHeap() override = default;

    void Meld(IHeap& other) override {
        auto second = dynamic_cast<CFoolHeap*>(&other);
        heap.insert(heap.end(), second->heap.begin(), second->heap.end());
        std::make_heap(heap.begin(), heap.end(), comp);
        second->heap.clear();
    }
};