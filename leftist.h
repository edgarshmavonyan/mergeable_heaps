#include <iostream>
#include "IHeap.h"
#include <vector>
#include "binary.h"


class CLeftistNode {
    int key_;
    int dist_;
    CLeftistNode *left_, *right_;
    friend class CBinaryHeap<CLeftistNode>;

    inline void relax() {
        int distLeft = (left_ ? left_->dist_ + 1 : 1);
        int distRight = (right_ ? right_->dist_ + 1 : 1);
        dist_ = std::min(distLeft, distRight);

        if (distLeft < distRight)
            std::swap(left_, right_);
    }

    void preOrderDelete() {
        if (left_) left_->preOrderDelete();
        delete left_;
        if (right_) right_->preOrderDelete();
        delete right_;
    }

public:

    explicit CLeftistNode(int key) : key_(key), dist_(0), left_(nullptr), right_(nullptr) {}

};

typedef CBinaryHeap<CLeftistNode> CLeftistHeap;