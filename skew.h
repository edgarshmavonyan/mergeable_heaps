#include <iostream>
#include "IHeap.h"

class CSkewNode {
    int key;
    CSkewNode *left, *right;
    friend class CSkewHeap;

    void preOrderDelete() {
        if (left) left->preOrderDelete();
        delete left;
        if (right) right->preOrderDelete();
        delete right;
    }
public:
    explicit CSkewNode(int key) : key(key), left(nullptr), right(nullptr) {}
};



class CSkewHeap: public IHeap {
    CSkewNode* root;

private:

    explicit CSkewHeap(CSkewNode* root) : root(root) {}

    static CSkewNode* Meld(CSkewNode* first, CSkewNode* second) {
        if (!first)
            return second;
        if (!second)
            return first;
        if (first->key > second->key)
            std::swap(first, second);

        first->right = Meld(first->right, second);

        std::swap(first->left, first->right);

        return first;
    }

public:

    explicit CSkewHeap(int key) : root(new CSkewNode(key)) {}

    CSkewHeap() : root(nullptr) {}

    ~CSkewHeap() override {
        if (!root) return;
        root->preOrderDelete();
        delete root;
    }

    int GetMin() override {
        return root->key;
    }

    void Meld(IHeap& other) override {
        auto second = dynamic_cast<CSkewHeap*>(&other);

        root = Meld(root, second->root);

        second->root = nullptr;
    }

    void Insert(int key) override {
        CSkewHeap temp(key);

        Meld(temp);

        temp.root = nullptr;
    }

    int ExtractMin() override {
        int k = root->key;

        CSkewHeap left(root->left), right(root->right);

        delete root;

        left.Meld(right);

        *this = left;

        left.root = right.root = nullptr;

        return k;
    }
};