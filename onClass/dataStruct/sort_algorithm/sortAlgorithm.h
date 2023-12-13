#pragma once


//insert-sort
template<typename T>
void insertSort(T* theArray, const int theSize);

//select-sort
template<typename T>
void selectSort(T* theArray, const int theSize);

//bubble-sort
template<typename T>
void bubbleSort(T* theArray, const int theSize);




//自定义类型需要重载operator>
//theArray:	需要被排序的数组
//theSize:	被排序数组的长度
template<typename T>
inline void insertSort(T* theArray, const int theSize)
{
	for (int i = 1; i < theSize; i++)
	{
		T key = theArray[i];
		int j = i - 1;
		while (j >= 0 && theArray[j] > key)
		{
			theArray[j + 1] = theArray[j];
			--j;
		}
		theArray[j + 1] = key;
	}
}

//自定义类型需要重载operator>
//theArray:	需要被排序的数组
//theSize:	被排序数组的长度
template<typename T>
inline void selectSort(T* theArray, const int theSize)
{
	for (size_t size = theSize; size > 1; size--)
	{
		//找到最大元素的索引
		int indexOfMax = 0;
		for (size_t i = 1; i < size; i++)
		{
			if (theArray[i] > theArray[indexOfMax])
				indexOfMax = i;
		}
		//元素交换
		std::swap(theArray[indexOfMax], theArray[size - 1]);
	}
}

//自定义类型需要重载operator>
//theArray:	需要被排序的数组
//theSize:	被排序数组的长度
template<typename T>
inline void bubbleSort(T* theArray, const int theSize)
{
	for (size_t size = theSize; size > 0; size--)
	{
		//冒泡:将当前最大的元素移动到当前范围末尾
		for (size_t i = 0; i < size - 1; i++)
		{
			if (theArray[i] > theArray[i + 1])
			{
				T temp = theArray[i];
				theArray[i] = theArray[i + 1];
				theArray[i + 1] = temp;
			}
		}
	}
}


