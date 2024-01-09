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

		//���������,�Զ���std::cout<<minHeap;����
		template<typename T>
		friend std::ostream& operator<<(std::ostream& os, const minHeap<T>& theHeap);

		//�����������ʼ��Ϊ�����С����
		virtual void Initialize(T* theArray, const int size, const int arraylength);

	private:
		T
			* heap;			//���Ԫ�ص�����,������1��ʼ
		int
			currentSize,	//��ǰС�����д��ڵ�Ԫ�ظ���
			maxSize;		//��ǰС��������Ԫ�ظ���
	};

	template<typename T>
	inline minHeap<T>::minHeap(const int initialCapacity)
	{
		if (initialCapacity < 0)
			throw std::logic_error("С���ѵĳ�ʼ����󳤶Ȳ���С��0");
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

		//heap����������1��ʼʹ��
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

		//Ϊ��ǰĩβԪ��Ѱ���µĲ���λ�ã��ڴ˲���·���еĽڵ�����л�
		while (child <= currentSize)
		{
			//�ҵ���ǰ�ڵ�������С���ӽڵ�
			if (child < currentSize && heap[child + 1] < heap[child])
				++child;

			//���ĩβԪ�رȵ�ǰ�ڵ����С�ӽڵ㻹С����ǰλ�þ�����ΪĩβԪ�ص�λ��
			if (lastElement < heap[child])
				break;
			else
			{
				/*��ǰĩβԪ�رȵ�ǰ�ڵ����С�ӽڵ��
				 ����ǰ�����ӽڵ�����ð��
				 ����Ѱ��ĩβԪ�غ��ʵĲ���λ��*/
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
		//��Ҫʱ�������鳤��(����������1��ʼ)
		if (currentSize + 1 == maxSize)
		{
			hp::changeArrayLength1D(heap, maxSize, maxSize * 2);
			maxSize *= 2;
		}

		int index = ++currentSize;
		//��������ð��
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

				//�ҵ���С���ӽڵ�
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