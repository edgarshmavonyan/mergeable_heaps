#include <iostream>
#include "IHeap.h"

class CBinomialNode {
    int key;
    CBinomialNode* child;
    CBinomialNode* next;
    int degree;

    friend class CBinomialHeap;
public:

    explicit CBinomialNode(int key) : key(key), child(nullptr), next(nullptr), degree(0) {}
};

class CBinomialHeap: public IHeap {
    CBinomialNode* root;

private:

    static void preOrderDeleter(CBinomialNode* cur) {
        if (!cur)
            return;
        preOrderDeleter(cur->next);
        preOrderDeleter(cur->child);
        delete cur;
    }

    void checkFeasibility() {
        if (!root)
            return;
        CBinomialNode *leftPointer = root, *rightPointer = root->next, *lefterPointer = nullptr;
        while (rightPointer) {
            if (rightPointer->degree < leftPointer->degree) {
                if (lefterPointer)
                    lefterPointer->next = rightPointer;
                else
                    root = rightPointer;
                leftPointer->next = rightPointer->next;
                rightPointer->next = leftPointer;
                std::swap(leftPointer, rightPointer);
            }
            if (leftPointer->degree != rightPointer->degree) {
                lefterPointer = leftPointer;
                leftPointer = rightPointer;
                rightPointer = rightPointer->next;
                continue;
            }
            if (leftPointer->key <= rightPointer->key) {
                CBinomialNode* tmp = rightPointer->next;
                rightPointer->next = leftPointer->child;
                leftPointer->child = rightPointer;
                leftPointer->next = tmp;
                ++leftPointer->degree;
                rightPointer = leftPointer->next;
            } else {
                leftPointer->next = rightPointer->child;
                rightPointer->child = leftPointer;
                ++rightPointer->degree;
                if (lefterPointer)
                    lefterPointer->next = rightPointer;
                else
                    root = rightPointer;
                leftPointer = rightPointer;
                rightPointer = leftPointer->next;
            }
        }
    }

public:
    CBinomialHeap() : root(nullptr) {}

    explicit CBinomialHeap(int key) : root(new CBinomialNode(key)) {}

    explicit CBinomialHeap(CBinomialNode* root) : root(root) {}

    ~CBinomialHeap() override {
        preOrderDeleter(root);
    }

    int GetMin() override {
        CBinomialNode* iter = root;
        int res = iter->key;
        while (iter) {
            if (res > iter->key)
                res = iter->key;
            iter = iter->next;
        }
        return res;
    }

    void Meld(IHeap& other) override {

        clock_t t = clock();

        auto second = dynamic_cast<CBinomialHeap*>(&other);

        if (!root) {
            root = second->root;
            return;
        }

        CBinomialNode *lefter = nullptr, *iter1 = root, *iter2 = second->root, *temp;

        while (iter1 && iter2) {
            if (iter1->degree <= iter2->degree) {
                lefter = iter1;
                iter1 = iter1->next;
                continue;
            }
            if (lefter)
                lefter->next = iter2;
            else
                root = iter2;
            temp = iter2->next;
            iter2->next = iter1;
            lefter = iter2;
            iter2 = temp;
        }

        if (iter2) {
            lefter->next = iter2;
        }

        checkFeasibility();
    }


    void Insert(int key) override {
        auto temp = CBinomialHeap(key);
        Meld(temp);
        temp.root = nullptr;
    }

    int ExtractMin() override {

        CBinomialNode* lefterIter = nullptr, *iter = root, *itMin = root, *lefterMin = nullptr;
        int res = iter->key;
        while (iter) {
            if (res > iter->key)
                res = iter->key, itMin = iter, lefterMin = lefterIter;
            lefterIter = iter;
            iter = iter->next;
        }
        if (lefterMin) {
            lefterMin->next = itMin->next;
        } else
            root = itMin->next;

        CBinomialHeap children(itMin->child);
        iter = itMin->child;
        lefterIter = nullptr;

        while (iter) {
            lefterMin = iter->next;
            iter->next = lefterIter;
            children.root = lefterIter = iter;
            iter = lefterMin;
        }

        Meld(children);
        children.root = nullptr;

        return res;
    }
};