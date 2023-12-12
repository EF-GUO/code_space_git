#pragma once

#include <stdexcept>


class queueEmpty :public std::logic_error
{
public:
	queueEmpty(const std::string& str = "this maxHeap is empty!") :logic_error(str) {}
};


class initialMaxHeapException :public std::logic_error
{
public:
	initialMaxHeapException(const std::string& str = "initialCapacity can't be lower than zero"):logic_error(str){}
};

class indexOutOfRangeException :public std::logic_error
{
public:
	indexOutOfRangeException(const std::string& str = "the index of maxHeapArray out of range") :logic_error(str) {}
};

