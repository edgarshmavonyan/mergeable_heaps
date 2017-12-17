#include <iostream>
#include "IHeap.h"
#include <vector>
#include "binary.h"


class CLeftistNode {
    int key;
    int dist;
    CLeftistNode *left, *right;
    friend class CBinaryHeap<CLeftistNode>;

    inline void relax() {
        int distLeft = (left ? left->dist + 1 : 1);
        int distRight = (right ? right->dist + 1 : 1);
        dist = std::min(distLeft, distRight);

        if (distLeft < distRight)
            std::swap(left, right);
    }

    void preOrderDelete() {
        if (left) left->preOrderDelete();
        delete left;
        if (right) right->preOrderDelete();
        delete right;
    }

public:

    explicit CLeftistNode(int key) : key(key), dist(0), left(nullptr), right(nullptr) {}

};

typedef CBinaryHeap<CLeftistNode> CLeftistHeap;