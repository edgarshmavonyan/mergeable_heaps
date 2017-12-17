#include <iostream>
#include <vector>
#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <random>
#include "testGenerator.h"


TEST(UniversalTest, SingleUniversal_Test) {
    std::mt19937 generator(time(0));
    const size_t size = 1000000;
    std::vector<int> values(size);
    for (int i = 0; i < size; i++) {
        values[i] = generator();
    }

    for (int type = 0; type < 3; type++) {
        HeapList tested(type);
        FoolHeapList fool;

        tested.AddHeap(values[0]);
        fool.AddHeap(values[0]);
        std::cout << "Size " << size << std::endl;

        for (int i = 0; i < size - 1; i++) {
            tested.Insert(0, values[i + 1]);
            fool.Insert(0, values[i + 1]);
            EXPECT_TRUE(tested.GetMin(0) == fool.GetMin(0));
        }

        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(tested.ExtractMin(0) == fool.ExtractMin(0));
        }
    }
}

TEST(UniversalTest, SingleRunTime_Test) {
    std::mt19937 generator(time(0));
    const size_t size = 1000000;
    std::vector<int> values(size);


    for (int i = 0; i < size; i++) {
        values[i] = generator();
    }

    for (int type = 0; type < 3; type++) {
        HeapList tested(type);
        FoolHeapList fool;

        tested.AddHeap(values[0]);
        fool.AddHeap(values[0]);
        std::cout << "Size " << size << std::endl;

        clock_t t = clock();

        for (int i = 0; i < size - 1; i++) {
            tested.Insert(0, values[i + 1]);
            fool.Insert(0, values[i + 1]);
            EXPECT_TRUE(tested.GetMin(0) == fool.GetMin(0));
        }

        t = clock() - t;

        std::cout << "time of inserting in heap (plus fool) " << type << ' ' << double(t) / CLOCKS_PER_SEC << std::endl;

        t = clock();

        for (int i = 0; i < size; i++)
            tested.ExtractMin(0);
        t = clock() - t;

        std::cout << "time of extracting from heap " << type << ' ' << double(t) / CLOCKS_PER_SEC << std::endl;

        t = clock();
        for (int i = 0; i < size; i++)
            fool.ExtractMin(0);
        t = clock() - t;

        std::cout << "time of extracting from heap fool " << double(t) / CLOCKS_PER_SEC << std::endl;
    }
}

TEST(MergeTest, MergeCorrectness_Test) {
    // 1000 heaps with 1000 keys
    std::mt19937 generator(time(0));
    const size_t size = 1000, number = 1000;
    std::vector<int> values(number*size);
    for (int i = 0; i < size * number; i++) {
        values[i] = generator();
    }

    // in order to test binomial, skew and leftist we create 1 fool heap with size * number
    // keys as merging would be too slow
    // it does not change the correctness of the test

    for (int type = 0; type < 3; type++) {
        FoolHeapList fool;
        fool.AddHeap(values[0]);
        HeapList tested(type);

        for (int i = 0; i < size * number - 1; i++)
            fool.Insert(0, values[i + 1]);

        for (int numHeap = 0; numHeap < number; numHeap++) {
            tested.AddHeap(values[numHeap * 1000]);

            for (int elem = 1; elem < size; elem++)
                tested.Insert(numHeap, values[numHeap * 1000 + elem]);
        }

        for (int numHeap = 1; numHeap < number; numHeap++) {
            tested.Meld(0, numHeap);
        }

        for (int i = 0; i < size * number; i++) {
            EXPECT_TRUE(fool.ExtractMin(0) == tested.ExtractMin(0));
        }
    }
}

TEST(MergeTest, MergeCompareTime_Test) {
    // 1000 heaps with 1000 keys
    std::mt19937 generator(time(0));
    const size_t size = 1000, number = 1000;
    std::vector<int> values(number*size);
    for (int i = 0; i < size * number; i++) {
        values[i] = generator();
    }

    // in order to test binomial, skew and leftist we create 1 fool heap with size * number
    // keys as merging would be too slow
    // it does not change the correctness of the test

    for (int type = 0; type < 3; type++) {
        FoolHeapList fool;
        fool.AddHeap(values[0]);
        HeapList tested(type);

        for (int i = 0; i < size * number - 1; i++)
            fool.Insert(0, values[i + 1]);

        for (int numHeap = 0; numHeap < number; numHeap++) {
            tested.AddHeap(values[numHeap * 1000]);

            for (int elem = 1; elem < size; elem++)
                tested.Insert(numHeap, values[numHeap * 1000 + elem]);
        }

        clock_t t = clock();

        for (int numHeap = 1; numHeap < number; numHeap++) {
            tested.Meld(0, numHeap);
        }

        t = clock() - t;

        std::cout << "time of merging for heap of type " << type << ' ' << double(t) / CLOCKS_PER_SEC << std::endl;

        for (int i = 0; i < size * number; i++) {
            EXPECT_TRUE(fool.ExtractMin(0) == tested.ExtractMin(0));
        }
    }
}

TEST(mainTest, randomTest) {
    std::vector<int> values, order;

    int heapNumber = 100000;
    size_t size = 100000;
    int testNumber = 100000;

    FoolHeapList fool;
    BinomialHeapList binomial;
    LeftistHeapList leftist;
    SkewHeapList skew;

    generateSomeValues(size, values);
    generateHeapOrder(size, heapNumber, order);
    generateHeaps(size, heapNumber, fool, order, values);
    generateHeaps(size, heapNumber, binomial, order, values);
    generateHeaps(size, heapNumber, skew, order, values);
    generateHeaps(size, heapNumber, leftist, order, values);

    std::vector<std::pair<int, std::pair<int, int> > > sequence;

    generateTestSequences(heapNumber, testNumber, sequence);

    for (int i = 0; i < testNumber; i++) {
        auto& ind = sequence[i].second;
        int type = sequence[i].first;

        ASSERT_TRUE(fool.Empty(ind.first) == binomial.Empty(ind.first));
        ASSERT_TRUE(fool.Empty(ind.first) == skew.Empty(ind.first));
        ASSERT_TRUE(fool.Empty(ind.first) == leftist.Empty(ind.first));
        EXPECT_TRUE(fool.Empty(ind.second) == binomial.Empty(ind.second));
        EXPECT_TRUE(fool.Empty(ind.second) == skew.Empty(ind.second));
        EXPECT_TRUE(fool.Empty(ind.second) == leftist.Empty(ind.second));

        switch(type) {
            case 0 : {
                if (!fool.Empty(ind.first)) {
                    int foolRes = fool.GetMin(ind.first);
                    EXPECT_EQ(foolRes, binomial.GetMin(ind.first));
                    EXPECT_EQ(foolRes, skew.GetMin(ind.first));
                    EXPECT_EQ(foolRes, leftist.GetMin(ind.first));
                }
                break;
            }
            case 1: {
                if (!fool.Empty(ind.first)) {
                    int foolRes = fool.ExtractMin(ind.first);
                    EXPECT_EQ(foolRes, binomial.ExtractMin(ind.first));
                    EXPECT_EQ(foolRes, skew.ExtractMin(ind.first));
                    EXPECT_EQ(foolRes, leftist.ExtractMin(ind.first));
                }
                break;
            }
            case 2: {
                if (fool.Empty(ind.first) || fool.Empty(ind.second) || ind.first == ind.second)
                    continue;
                fool.Meld(ind.first, ind.second);
                binomial.Meld(ind.first, ind.second);
                skew.Meld(ind.first, ind.second);
                leftist.Meld(ind.first, ind.second);

                int foolRes = fool.GetMin(ind.first);
                EXPECT_EQ(foolRes, binomial.GetMin(ind.first));
                EXPECT_EQ(foolRes, skew.GetMin(ind.first));
                EXPECT_EQ(foolRes, leftist.GetMin(ind.first));
                break;
            }
            default: {
                EXPECT_TRUE(false);
            }
        }
    }
}



int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}