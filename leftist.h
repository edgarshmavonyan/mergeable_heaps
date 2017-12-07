#include <iostream>
#include "IHeap.h"
#include <vector>

class CLeftistNode {
    int key;
    int dist;
    CLeftistNode *left, *right;
    friend class CLeftistHeap;

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

class CLeftistHeap: public IHeap {
    CLeftistNode* root;

private:

    explicit CLeftistHeap(CLeftistNode* root) : root(root) {}

    static CLeftistNode* Meld(CLeftistNode* first, CLeftistNode* second) {
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

    explicit CLeftistHeap(int key) : root(new CLeftistNode(key)) {}

    CLeftistHeap() : root(nullptr) {}

    ~CLeftistHeap() override {
        if (!root) return;
        root->preOrderDelete();
        delete root;
    }

    int GetMin() override {
        return root->key;
    }

    void Meld(IHeap& other) override {
        auto second = dynamic_cast<CLeftistHeap*>(&other);

        root = Meld(root, second->root);

        second->root = nullptr;
    }

    void Insert(int key) override {
        CLeftistHeap temp(key);

        Meld(temp);
        temp.root = nullptr;
    }

    int ExtractMin() override {
        int k = root->key;

        CLeftistHeap left(root->left), right(root->right);

        delete root;

        left.Meld(right);

        *this = left;

        left.root = right.root = nullptr;

        return k;
    }

};