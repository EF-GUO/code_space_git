#include <iostream>
#include "maxHeap.h"


int main()
{
	using namespace std;
	const int SIZE = 11;

	maxHeap<int> demo;
	demo.initialize(new int[SIZE] {0, 20, 12, 35, 15, 10, 80, 30, 17, 2, 1}, SIZE - 1);

	demo.showHeap();
	int count = 0;


	auto z = demo.begin();
	auto j = demo.end();

	for (maxHeap<int>::Iterator i = demo.begin(); i != demo.end(); ++i)
		count++;


}




