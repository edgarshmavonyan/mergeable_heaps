#include <iostream>
#include <vector>
#include "heaplist.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <random>



TEST(UniversalTest, DISABLED_SingleUniversalTest) {
    std::mt19937 generator;
    int size = 1000000;
    std::vector<int> values(size);
    for (int i = 0; i < size; i++) {
        values[i] = generator();
    }

    for (int type = 0; type < 3; type++) {
        HeapList first(type), second(3);

        first.AddHeap(size);
        second.AddHeap(size);
        std::cout << "Size " << size << std::endl;

        for (int i = 0; i < size - 1; i++) {
            int next = generator();
            first.Insert(0, next);
            second.Insert(0, next);
            EXPECT_TRUE(first.GetMin(0) == second.GetMin(0));
        }

        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(first.ExtractMin(0) == second.ExtractMin(0));
        }
    }
}

TEST(UniversalTest, SingleRunTimeTest) {
    std::mt19937 generator;
    int size = 1000000;
    std::vector<int> values(size);
    for (int i = 0; i < size; i++) {
        values[i] = generator();
    }

    for (int type = 0; type < 3; type++) {
        HeapList first(type), second(3);

        first.AddHeap(size);
        second.AddHeap(size);
        std::cout << "Size " << size << std::endl;

        clock_t t = clock();

        for (int i = 0; i < size - 1; i++) {
            first.Insert(0, values[i]);
            second.Insert(0, values[i]);
            EXPECT_TRUE(first.GetMin(0) == second.GetMin(0));
        }

        t = clock() - t;

        std::cout << "time of inserting in heap (plus fool) " << type << ' ' << double(t) / CLOCKS_PER_SEC << std::endl;

        t = clock();

        for (int i = 0; i < size; i++)
            first.ExtractMin(0);
        t = clock() - t;

        std::cout << "time of extracting from heap " << type << ' ' << double(t) / CLOCKS_PER_SEC << std::endl;

        t = clock();
        for (int i = 0; i < size; i++)
            second.ExtractMin(0);
        t = clock() - t;

        std::cout << "time of extracting from heap fool " << double(t) / CLOCKS_PER_SEC << std::endl;
    }
}





int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}