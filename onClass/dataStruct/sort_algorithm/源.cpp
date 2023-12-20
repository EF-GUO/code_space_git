#include <iostream>
#include "sortAlgorithm.h"


template<typename T>
void showArray(T* theArray, const int theSize);


int main()
{
	using namespace std;
	using namespace sortAlgorithm;

	int SIZE = 10;
	int* array = new int[SIZE] { 5, 1, 6, 8, 3, 4, 9, 7, 2, 10 };

	showArray<int>(array, SIZE);

	mergeSort(array, 0, SIZE - 1);

	showArray<int>(array, SIZE);



	delete[] array;
}




//��������

template<typename T>
void showArray(T* theArray, const int theSize)
{
	for (size_t i = 0; i < theSize; i++)
		std::cout << theArray[i] << " ";
	std::cout << std::endl;
}




















