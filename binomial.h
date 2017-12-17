#include <iostream>
#include "IHeap.h"

class CBinomialNode {
    int key_;
    CBinomialNode* child_;
    CBinomialNode* next_;
    int degree_;

    friend class CBinomialHeap;
public:

    explicit CBinomialNode(int key) : key_(key), child_(nullptr), next_(nullptr), degree_(0) {}
};

class CBinomialHeap: public IHeap {
    CBinomialNode* root_;

private:

    inline void shiftPointers(CBinomialNode*& lefterPointer,
                              CBinomialNode*& leftPointer, CBinomialNode*& rightPointer) {
        lefterPointer = leftPointer;
        leftPointer = rightPointer;
        rightPointer = rightPointer->next_;
    }

    inline void linkRightTreetoLeft(CBinomialNode*& lefterPointer,
                                    CBinomialNode*& leftPointer, CBinomialNode*& rightPointer) {
        CBinomialNode* tmp = rightPointer->next_;
        rightPointer->next_ = leftPointer->child_;
        leftPointer->child_ = rightPointer;
        leftPointer->next_ = tmp;
        ++leftPointer->degree_;
        rightPointer = leftPointer->next_;
    }

    inline void linkLeftTreetoRight(CBinomialNode*& lefterPointer,
                                    CBinomialNode*& leftPointer, CBinomialNode*& rightPointer) {
        leftPointer->next_ = rightPointer->child_;
        rightPointer->child_ = leftPointer;
        ++rightPointer->degree_;
        if (lefterPointer)
            lefterPointer->next_ = rightPointer;
        else
            root_ = rightPointer;
        leftPointer = rightPointer;
        rightPointer = leftPointer->next_;
    }

    inline void swapTrees(CBinomialNode*& lefterPointer,
                          CBinomialNode*& leftPointer, CBinomialNode*& rightPointer) {
        if (lefterPointer)
            lefterPointer->next_ = rightPointer;
        else
            root_ = rightPointer;
        leftPointer->next_ = rightPointer->next_;
        rightPointer->next_ = leftPointer;
        std::swap(leftPointer, rightPointer);
    }

    static void preOrderDeleter(CBinomialNode* cur) {
        if (!cur)
            return;
        preOrderDeleter(cur->next_);
        preOrderDeleter(cur->child_);
        delete cur;
    }

    void checkFeasibility() {
        if (!root_)
            return;
        CBinomialNode *leftPointer = root_, *rightPointer = root_->next_, *lefterPointer = nullptr;
        while (rightPointer) {
            if (rightPointer->degree_ < leftPointer->degree_)
                swapTrees(lefterPointer, leftPointer, rightPointer);

            if (leftPointer->degree_ != rightPointer->degree_) {
                shiftPointers(lefterPointer, leftPointer, rightPointer);
                continue;
            }

            if (leftPointer->key_ <= rightPointer->key_)
                linkRightTreetoLeft(lefterPointer, leftPointer, rightPointer);
            else
                linkLeftTreetoRight(lefterPointer, leftPointer, rightPointer);
        }
    }

    void InsertList(CBinomialNode*& otherRoot) {

        CBinomialNode *lefter = nullptr, *iter1 = root_, *iter2 = otherRoot, *temp;

        while (iter1 && iter2) {
            if (iter1->degree_ <= iter2->degree_) {
                lefter = iter1;
                iter1 = iter1->next_;
                continue;
            }
            if (lefter)
                lefter->next_ = iter2;
            else
                root_ = iter2;
            temp = iter2->next_;
            iter2->next_ = iter1;
            lefter = iter2;
            iter2 = temp;
        }

        if (iter2) {
            lefter->next_ = iter2;
        }
    }

    std::pair<CBinomialNode*, CBinomialNode*> GetMin_() {
        CBinomialNode* lefterIter = nullptr, *iter = root_, *itMin = root_, *lefterMin = nullptr;
        int res = iter->key_;
        while (iter) {
            if (res > iter->key_)
                res = iter->key_, itMin = iter, lefterMin = lefterIter;
            lefterIter = iter;
            iter = iter->next_;
        }

        return std::make_pair(lefterMin, itMin);
    }

    static void reverseList(CBinomialNode*& root) {
        CBinomialNode* iter = root, *lefterIter = nullptr, *temp;
        while (iter) {
            temp = iter->next_;
            iter->next_ = lefterIter;
            root = lefterIter = iter;
            iter = temp;
        }
    }

public:
    CBinomialHeap() : root_(nullptr) {}

    explicit CBinomialHeap(int key) : root_(new CBinomialNode(key)) {}

    explicit CBinomialHeap(CBinomialNode* root) : root_(root) {}

    explicit operator bool() const override {
        return bool(root_);
    }

    ~CBinomialHeap() override {
        preOrderDeleter(root_);
    }

    int GetMin() override {
        auto min = GetMin_();

        return min.second->key_;
    }

    void Meld(IHeap& other) override {

        auto second = dynamic_cast<CBinomialHeap*>(&other);

        if (!root_) {
            root_ = second->root_;
            return;
        }

        InsertList(second->root_);

        checkFeasibility();
    }


    void Insert(int key) override {
        auto temp = CBinomialHeap(key);
        Meld(temp);
        temp.root_ = nullptr;
    }

    int ExtractMin() override {

        auto min = GetMin_();

        int res = min.second->key_;

        if (min.first) {
            min.first->next_ = min.second->next_;
        } else
            root_ = min.second->next_;

        CBinomialHeap children(min.second->child_);
        reverseList(children.root_);

        Meld(children);
        children.root_ = nullptr;

        return res;
    }
};