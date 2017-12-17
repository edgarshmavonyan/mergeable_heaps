#include <iostream>
#include "IHeap.h"
#include "binary.h"

class CSkewNode {
    int key_;
    CSkewNode *left_, *right_;
    friend class CBinaryHeap<CSkewNode>;

    void preOrderDelete() {
        if (left_) left_->preOrderDelete();
        delete left_;
        if (right_) right_->preOrderDelete();
        delete right_;
    }

    void relax() {
        std::swap(left_, right_);
    }
public:
    explicit CSkewNode(int key) : key_(key), left_(nullptr), right_(nullptr) {}
};

typedef CBinaryHeap<CSkewNode> CSkewHeap;