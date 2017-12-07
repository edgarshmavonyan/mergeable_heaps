#include <iostream>
#include <vector>

#pragma once

class IHeap {

public:


    virtual void Insert(int key) = 0;

    virtual int GetMin() = 0;

    virtual int ExtractMin() = 0;

    virtual void Meld(IHeap& other) = 0;

    virtual ~IHeap() = default;

};