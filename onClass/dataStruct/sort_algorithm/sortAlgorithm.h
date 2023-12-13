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




//�Զ���������Ҫ����operator>
//theArray:	��Ҫ�����������
//theSize:	����������ĳ���
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

//�Զ���������Ҫ����operator>
//theArray:	��Ҫ�����������
//theSize:	����������ĳ���
template<typename T>
inline void selectSort(T* theArray, const int theSize)
{
	for (size_t size = theSize; size > 1; size--)
	{
		//�ҵ����Ԫ�ص�����
		int indexOfMax = 0;
		for (size_t i = 1; i < size; i++)
		{
			if (theArray[i] > theArray[indexOfMax])
				indexOfMax = i;
		}
		//Ԫ�ؽ���
		std::swap(theArray[indexOfMax], theArray[size - 1]);
	}
}

//�Զ���������Ҫ����operator>
//theArray:	��Ҫ�����������
//theSize:	����������ĳ���
template<typename T>
inline void bubbleSort(T* theArray, const int theSize)
{
	for (size_t size = theSize; size > 0; size--)
	{
		//ð��:����ǰ����Ԫ���ƶ�����ǰ��Χĩβ
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


