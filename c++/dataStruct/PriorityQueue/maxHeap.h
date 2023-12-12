#pragma once

#include "maxPriorityQueue.h"
#include "tools.h"
#include "maxHeapException.h"
#include <array>


//location(i) = i;
template<typename T>
class maxHeap :public maxPriorityQueue<T>
{
public:
	maxHeap(const int initialCapacity = 10);
	maxHeap(const maxHeap<T>& theHeap);
	~maxHeap();


	//ADT methods
	bool empty() const;
	int size() const;
	const T& top();
	void pop();
	void push(const T& theElement);

	//数组中建堆
	void initialize(T* theHeap, int theSize);

	//get heapArray
	T* getHeapArray(int& theSize)
	{
		theSize = heapSize;
		return heap;
	}

	void showHeap()
	{
		for (size_t i = 1; i <= heapSize; i++)
			std::cout << heap[i] << " ";
		std::cout << std::endl;
	}

	void changeMax(const T& theElement);

	T removei(const int i);


	//任意顺序 计数的迭代器
	class Iterator
	{
	public:
		Iterator(const T* const heap_, int index_):theHeap(heap_),theIndex(index_)
		{
		}

		Iterator& operator++()
		{
			theIndex++;
			return *this;
		}

		bool operator!=(const Iterator& theRhs)
		{
			if (theHeap == theRhs.theHeap && theIndex == theRhs.theIndex)
				return false;
			return true;
		}
	private:
		int theIndex;
		const T* const theHeap;	
	};

	Iterator begin()
	{
		return Iterator(heap, 1);
	}

	Iterator end()
	{
		return Iterator(heap, heapSize+1);
	}
private:
	T* heap;
	int arrayLength;
	int heapSize;
};

template<typename T>
inline maxHeap<T>::maxHeap(const int initialCapacity)
{
	if (initialCapacity < 0)
		throw initialMaxHeapException();
	heap = new T[initialCapacity + 1];
	arrayLength = initialCapacity + 1;
	heapSize = 0;
}

template<typename T>
inline maxHeap<T>::maxHeap(const maxHeap<T>& theHeap)
{
	heap = new T[theHeap.arrayLength];
	heapSize = theHeap.heapSize;
	arrayLength = theHeap.arrayLength;

	if (heapSize != 0)
		std::copy(theHeap.heap, theHeap.heap + heapSize + 1, heap);
}

template<typename T>
inline maxHeap<T>::~maxHeap() { delete[] heap; }

template<typename T>
inline bool maxHeap<T>::empty() const
{
	return heapSize == 0;
}

template<typename T>
inline int maxHeap<T>::size() const
{
	return heapSize;
}

template<typename T>
inline const T& maxHeap<T>::top()
{
	return heap[1];
}

template<typename T>
inline void maxHeap<T>::pop()
{
	//队列为空，抛出异常
	if (heapSize == 0)
		throw queueEmpty();

	//根元素释放
	heap[1].~T();
	T lastElement = heap[heapSize--];
	int currentNode = 1,
		child = 2;

	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
			++child;
		if (lastElement > heap[child])
			break;

		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<typename T>
inline void maxHeap<T>::push(const T& theElement)
{
	//容量满了,扩容
	if (heapSize = arrayLength - 1)
	{
		changeLength1D(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode = currentNode / 2;
	}
	heap[currentNode] = theElement;
}

template<typename T>
inline void maxHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[] heap;

	heap = theHeap;
	arrayLength = theSize + 1;
	heapSize = theSize;

	//堆化
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];
		int child = 2 * root;
		while (child <= heapSize)
		{
			if (child < heapSize && heap[child] < heap[child + 1])
				++child;
			if (rootElement >= heap[child])
				break;

			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootElement;
	}

}

template<typename T>
inline void maxHeap<T>::changeMax(const T& theElement)
{
	if (theElement == heap[1])
		return;

	heap[1].~T();

	int currentNode = 1,
		child = 2;

	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
			++child;
		if (theElement >= heap[child])
			break;
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = theElement;
}

template<typename T>
inline T maxHeap<T>::removei(const int i)
{
	if (i < 1 || i > heapSize)
		throw indexOutOfRangeException();
	T removeElement = heap[i];
	heap[i].~T();
	//移除末尾元素
	if (i == heapSize)
		heapSize--;
	//移除非末尾元素
	else
	{
		T lastElement = heap[heapSize--];
		int currentNode = i,
			child = 2 * i;
		while (child <= heapSize)
		{
			if (child < heapSize && heap[child] < heap[child + 1])
				++child;
			if (lastElement >= heap[child])
				break;

			heap[currentNode] = heap[child];
			currentNode = child;
			child *= 2;
		}
		heap[currentNode] = lastElement;
	}
	return removeElement;
}
























