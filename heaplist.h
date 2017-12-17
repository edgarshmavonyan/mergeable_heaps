#include <iostream>
#include "leftist.h"
#include "skew.h"
#include "binomial.h"
#include "fool.h"


class HeapList {
    std::vector<IHeap*> list_;

    enum HeapType {
        Binomial,
        Leftist,
        Skew,
        Fool
    };

    const HeapType TYPE = Fool;

public:

    explicit HeapList(int typ) : list_(), TYPE(static_cast<HeapType>(typ)) {}

    explicit HeapList(HeapType type) : list_(), TYPE(type) {}

    void Insert(int index, int val) {
        list_[index]->Insert(val);
    }

    void AddHeap(int key) {

        switch(TYPE) {
            case Leftist: {
                list_.push_back(new CLeftistHeap(key));
            } break;
            case Binomial: {
                list_.push_back(new CBinomialHeap(key));
            } break;

            case Skew: {
                list_.push_back(new CSkewHeap(key));
            } break;
            case Fool: {
                list_.push_back(new CFoolHeap(key));
            } break;
        }
    }

    int GetMin(int index) {
        return list_[index]->GetMin();
    }

    int ExtractMin(int index) {
        return list_[index]->ExtractMin();
    }

    void Meld(int index1, int index2) {

        list_[index1]->Meld(*list_[index2]);
        list_[index2] = nullptr;
    }

    ~HeapList() {
        for (auto element : list_)
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