#pragma once


namespace sortAlgorithm
{

	template<typename T>
	void insertSort(T* theArray, const int theSize);
	//��������

	template<typename T>
	void selectSort(T* theArray, const int theSize);
	//ѡ������

	template<typename T>
	void bubbleSort(T* theArray, const int theSize);
	//ð������

	template<typename T>
	void mergeSort(T* theArray, const int left, const int right);
	//�鲢����

	template<typename T>
	void merge(T* theArray, const int left, const int mid, const int right);
	//�ϲ�����

	template<typename T>
	void shellSort(T* theArray, const int n);

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

	template<typename T>
	inline void mergeSort(T* theArray, const int left, const int right)
	{
		using std::cout;
		using std::endl;
		if (left < right)
		{
			int mid = (left + right) / 2;
			mergeSort(theArray, left, mid);
			mergeSort(theArray, mid + 1, right);
			merge(theArray, left, mid, right);
		}
	}

	template<typename T>
	inline void merge(T* theArray, const int left, const int mid, const int right)
	{

		using std::cout;
		using std::endl;

		int leftSubSize = mid - left + 1;
		int rightSubSize = right - mid;

		T* leftSub = new T[leftSubSize];
		T* rightSub = new T[rightSubSize];

		for (size_t i = 0; i < leftSubSize; i++)
			leftSub[i] = theArray[left + i];
		for (size_t i = 0; i < rightSubSize; i++)
			rightSub[i] = theArray[mid + i + 1];

		int leftSubIndex = 0, rightSubIndex = 0;
		int index = left;
		while (leftSubIndex != leftSubSize || rightSubIndex != rightSubSize)
		{
			if (leftSubIndex == leftSubSize)
			{
				theArray[index++] = rightSub[rightSubIndex++];
				continue;
			}
			if (rightSubIndex == rightSubSize)
			{
				theArray[index++] = leftSub[leftSubIndex++];
				continue;
			}

			if (leftSub[leftSubIndex] < rightSub[rightSubIndex])
				theArray[index++] = leftSub[leftSubIndex++];
			else
				theArray[index++] = rightSub[rightSubIndex++];
		}
		delete[] leftSub;
		delete[] rightSub;

	}


	template<typename T>
	void shellSort(T* theArray, const int n)
	{
		for (int gap = n / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < n; ++i)
			{
				T temp = theArray[i];
				int j;
				for (j = i; j >= gap && theArray[j - gap] > temp; j -= gap)
					theArray[j] = theArray[j - gap];
				theArray[j] = temp;
			}
		}
	}
}




