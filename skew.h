#include <iostream>
#include "IHeap.h"
#include "binary.h"

class CSkewNode {
    int key;
    CSkewNode *left, *right;
    friend class CBinaryHeap<CSkewNode>;

    void preOrderDelete() {
        if (left) left->preOrderDelete();
        delete left;
        if (right) right->preOrderDelete();
        delete right;
    }

    void relax() {
        std::swap(left, right);
    }
public:
    explicit CSkewNode(int key) : key(key), left(nullptr), right(nullptr) {}
};

typedef CBinaryHeap<CSkewNode> CSkewHeap;