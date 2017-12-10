Mergeable_heaps
===============
- - - - 

We've implemented three most used mergeable heaps:

1) Binomial

2) Skew

3) Leftist 

To manage several heaps we have an interface HeapList.

It is implemented in heaplist.h and contains a vector of pointers to heaps.

The methods are

1) to create heap with a key use void Addheap(int key)

2) to insert value val into heap with index ind use void Insert(int index, int val)

3) to get the minimum of heap index use int GetMin(int index)

4) to extract the minimum of heap index use int ExtractMin(int index)

5) to merge two heaps with indexes index1 and index2 use void Meld(int index1, int index2)

HeapList uses abstract class of mergeable heaps named IHeap (is implemented in IHeap.h)

It is able to answer requests and has virtual destructor.

Finally, we have three inheritants of IHeap :

1) CBinomialHeap (binomial.h)

2) CSkewHeap (skew.h)

3) CLeftistHeap (leftist.h)

They use supporting friend classes of nodes.

The file with tests is unit_test.cpp.

They check the time of insert, extract and meld and the correctness of the implementation using CFoolHeap which is implemented using stl.