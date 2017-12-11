#include <iostream>
#include "leftist.h"
#include "skew.h"
#include "binomial.h"
#include "fool.h"


class HeapList {
    std::vector<IHeap*> list;

    enum Heap {
        Binomial,
        Leftist,
        Skew,
        Fool
    };

    const Heap type = Fool;

public:

    HeapList(int typ) : list(), type(static_cast<Heap>(typ)) {}

    void Insert(int index, int val) {
        list[index]->Insert(val);
    }

    void AddHeap(int key) {

        switch(type) {
            case Leftist: {
                list.push_back(new CLeftistHeap(key));
            } break;
            case Binomial: {
                list.push_back(new CBinomialHeap(key));
            } break;

            case Skew: {
                list.push_back(new CSkewHeap(key));
            } break;
            case Fool: {
//                std::cout << "Inserted to Fool" << std::endl;
                list.push_back(new CFoolHeap(key));
            } break;
        }
    }

    int GetMin(int index) {
        return list[index]->GetMin();
    }

    int ExtractMin(int index) {
        return list[index]->ExtractMin();
    }

    void Meld(int index1, int index2) {

        list[index1]->Meld(*list[index2]);
        list[index2] = nullptr;
    }

    ~HeapList() {
        for (auto element : list)
            delete element;
    }

};


class BinomialHeapList: public HeapList {
public:
    BinomialHeapList() : HeapList(0) {}
};

class SkewHeapList: public HeapList {
public:
    SkewHeapList() : HeapList(2) {}
};

class LeftistHeapList: public HeapList {
public:
    LeftistHeapList() : HeapList(1) {}
};

class FoolHeapList: public HeapList {
public:
    FoolHeapList() : HeapList(3) {}
};