#pragma once
#include <stdexcept>

namespace hp
{

	//改变一维数组长度
	template<typename T>
	void* changeArrayLength1D(T*& theArray, const int oldSize, const int newSize)
	{
		if (newSize < 0)
			throw std::logic_error("length error in changeArrayLength1D()");

		T* newArray = new T[newSize];

		if (newSize > oldSize)
			std::copy(theArray, theArray + oldSize, newArray);
		else
			std::copy(theArray, theArray + newSize, newArray);

		delete theArray;
		theArray = newArray;
	}
}