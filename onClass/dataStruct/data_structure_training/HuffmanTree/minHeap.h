#pragma once
#include <iostream>
#include <stdexcept>
#include "minPriorityQueue.h"
#include "helpMethods.h"

namespace heap
{
	template<typename T>
	class minHeap :minPriorityQueue<T>
	{
	public:
		minHeap(const int initialCapacity = 10);
		~minHeap();

		bool empty()const;
		int size() const;
		const T& top();
		void pop();
		void push(const T& theElement);

		//运算符重载,自定义std::cout<<minHeap;操作
		template<typename T>
		friend std::ostream& operator<<(std::ostream& os, const minHeap<T>& theHeap);

		//从无序数组初始化为有序的小根堆
		virtual void Initialize(T* theArray, const int size, const int arraylength);

	private:
		T
			* heap;			//存放元素的数组,索引从1开始
		int
			currentSize,	//当前小根堆中存在的元素个数
			maxSize;		//当前小根堆最大的元素个数
	};

	template<typename T>
	inline minHeap<T>::minHeap(const int initialCapacity)
	{
		if (initialCapacity < 0)
			throw std::logic_error("小根堆的初始化最大长度不能小于0");
		heap = new T[initialCapacity + 1];
		maxSize = initialCapacity;
		currentSize = 0;
	}

	template<typename T>
	inline minHeap<T>::~minHeap()
	{
		delete[] heap;
	}

	template<typename T>
	inline bool minHeap<T>::empty() const
	{
		return currentSize == 0;
	}

	template<typename T>
	inline int minHeap<T>::size() const
	{
		return currentSize;
	}

	template<typename T>
	inline const T& minHeap<T>::top()
	{
		if (currentSize == 0)
			throw std::logic_error("the minHeap is empty");

		//heap数组索引从1开始使用
		return heap[1];
	}

	template<typename T>
	inline void minHeap<T>::pop()
	{
		if (currentSize == 0)
			throw std::logic_error("the minHeap is empty can't be pop()");

		heap[1].~T();

		T lastElement = heap[currentSize--];

		int currentNode = 1,
			child = 2;

		//为当前末尾元素寻找新的插入位置，在此查找路径中的节点会序列化
		while (child <= currentSize)
		{
			//找到当前节点下面最小的子节点
			if (child < currentSize && heap[child + 1] < heap[child])
				++child;

			//如果末尾元素比当前节点的最小子节点还小，当前位置就能作为末尾元素的位置
			if (lastElement < heap[child])
				break;
			else
			{
				/*当前末尾元素比当前节点的最小子节点大
				 将当前最大的子节点向上冒泡
				 继续寻找末尾元素合适的插入位置*/
				heap[currentNode] = heap[child];
				currentNode = child;
				child *= 2;
			}
		}
		heap[currentNode] = lastElement;
	}

	template<typename T>
	inline void minHeap<T>::push(const T& theElement)
	{
		//必要时增加数组长度(数组索引从1开始)
		if (currentSize + 1 == maxSize)
		{
			hp::changeArrayLength1D(heap, maxSize, maxSize * 2);
			maxSize *= 2;
		}

		int index = ++currentSize;
		//不断向上冒泡
		while (index != 1 && heap[index / 2] > theElement)
		{
			heap[index] = heap[index / 2];
			index /= 2;
		}
		heap[index] = theElement;
	}

	template<typename T>
	inline void minHeap<T>::Initialize(T* theArray, const int size, const int arraylength)
	{
		if (size < 0 || arraylength < 0)
			throw std::logic_error("Initialize minHeap form array error: the size or arrayLength error");

		delete[] heap;
		heap = theArray;
		currentSize = size;
		maxSize = arraylength;

		for (int root = currentSize / 2; root >= 1; root--)
		{
			T rootElement = heap[root];

			int child = root * 2;
			while (child <= currentSize)
			{

				//找到最小的子节点
				if (child < currentSize && heap[child + 1] < heap[child])
					++child;

				if (rootElement < heap[child])
					break;

				heap[child / 2] = heap[child];
				child *= 2;
			}
			heap[child / 2] = rootElement;
		}
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const minHeap<T>& theHeap)
	{
		if (theHeap.currentSize == 0)
			os  << "empty";
		for (size_t i = 1; i <= theHeap.currentSize; i++)
			os << theHeap.heap[i] << " ";
		return os;
	}

}