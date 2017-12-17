#include <iostream>
#include "IHeap.h"

#pragma once

template<typename NodeType>
class CBinaryHeap: public IHeap {

    NodeType* root_;

    explicit CBinaryHeap(NodeType* root) : root_(root) {}

    static NodeType* Meld(NodeType* first, NodeType* second) {
        if (!first)
            return second;
        if (!second)
            return first;
        if (first->key_ > second->key_)
            std::swap(first, second);

        first->right_ = Meld(first->right_, second);

        first->relax();

        return first;
    }

public:

    explicit CBinaryHeap(int key) : root_(new NodeType(key)) {}

    CBinaryHeap() : root_(nullptr) {}

    explicit operator bool() const override {
        return bool(root_);
    }

    ~CBinaryHeap() override {
        if (!root_) return;
        root_->preOrderDelete();
        delete root_;
    }

    int GetMin() override {
        return root_->key_;
    }

    void Meld(IHeap& other) override {
        auto second = dynamic_cast<CBinaryHeap*>(&other);

        root_ = Meld(root_, second->root_);

        second->root_ = nullptr;
    }

    void Insert(int key) override {
        CBinaryHeap temp(key);

        Meld(temp);

        temp.root_ = nullptr;
    }

    int ExtractMin() override {
        int k = root_->key_;

        CBinaryHeap left(root_->left_), right(root_->right_);

        delete root_;

        left.Meld(right);

        *this = left;

        left.root_ = right.root_ = nullptr;

        return k;
    }
};