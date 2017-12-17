#include <iostream>
#include "IHeap.h"

#pragma once

template<typename NodeType>
class CBinaryHeap: public IHeap {
    NodeType* root;

private:

    explicit CBinaryHeap(NodeType* root) : root(root) {}

    static NodeType* Meld(NodeType* first, NodeType* second) {
        if (!first)
            return second;
        if (!second)
            return first;
        if (first->key > second->key)
            std::swap(first, second);

        first->right = Meld(first->right, second);

        first->relax();

        return first;
    }

public:

    explicit CBinaryHeap(int key) : root(new NodeType(key)) {}

    CBinaryHeap() : root(nullptr) {}

    ~CBinaryHeap() override {
        if (!root) return;
        root->preOrderDelete();
        delete root;
    }

    int GetMin() override {
        return root->key;
    }

    void Meld(IHeap& other) override {
        auto second = dynamic_cast<CBinaryHeap*>(&other);

        root = Meld(root, second->root);

        second->root = nullptr;
    }

    void Insert(int key) override {
        CBinaryHeap temp(key);

        Meld(temp);

        temp.root = nullptr;
    }

    int ExtractMin() override {
        int k = root->key;

        CBinaryHeap left(root->left), right(root->right);

        delete root;

        left.Meld(right);

        *this = left;

        left.root = right.root = nullptr;

        return k;
    }
};