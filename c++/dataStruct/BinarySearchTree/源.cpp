#include <iostream>

#include "binarySearchTree.h"

int main()
{
	using namespace std;

	//binarySearchTree<int, int> demo;
	//demo.insert(make_pair<int, int>(20, 1));
	//demo.insert(make_pair<int, int>(15, 2));
	//demo.insert(make_pair<int, int>(25, 3));
	//demo.insert(make_pair<int, int>(12, 4));
	//demo.insert(make_pair<int, int>(18, 5));
	//demo.insert(make_pair<int, int>(30, 6));

	//demo.outputInRange(10,26);

	binarySearchTree<int, int> demo1;
	binarySearchTree<int, int> demo2;
	binarySearchTree<int, int> demo3;

	demo1.insert(make_pair<int, int>(50, 0));
	demo1.insert(make_pair<int, int>(25, 0));
	demo1.insert(make_pair<int, int>(75, 0));
	demo1.insert(make_pair<int, int>(12, 0));
	demo1.insert(make_pair<int, int>(37, 0));
	demo1.insert(make_pair<int, int>(62, 0));
	demo1.insert(make_pair<int, int>(87, 0));
	demo1.insert(make_pair<int, int>(6, 0));
	demo1.insert(make_pair<int, int>(18, 0));
	demo1.insert(make_pair<int, int>(31, 0));
	demo1.insert(make_pair<int, int>(43, 0));
	demo1.insert(make_pair<int, int>(56, 0));
	demo1.insert(make_pair<int, int>(68, 0));
	demo1.insert(make_pair<int, int>(81, 0));
	demo1.insert(make_pair<int, int>(93, 0));
	demo1.insert(make_pair<int, int>(3, 0));
	demo1.insert(make_pair<int, int>(9, 0));
	demo1.insert(make_pair<int, int>(15, 0));
	demo1.insert(make_pair<int, int>(21, 0));
	demo1.insert(make_pair<int, int>(28, 0));
	demo1.insert(make_pair<int, int>(34, 0));
	demo1.insert(make_pair<int, int>(40, 0));
	demo1.insert(make_pair<int, int>(46, 0));
	demo1.insert(make_pair<int, int>(53, 0));
	demo1.insert(make_pair<int, int>(59, 0));
	demo1.insert(make_pair<int, int>(65, 0));
	demo1.insert(make_pair<int, int>(71, 0));
	demo1.insert(make_pair<int, int>(78, 0));
	demo1.insert(make_pair<int, int>(84, 0));
	demo1.insert(make_pair<int, int>(90, 0));
	demo1.insert(make_pair<int, int>(96, 0));
	



	demo1.split(39, &demo2, &demo3);
	demo2.ascend();
	cout << endl << endl << endl << endl;

	demo3.ascend();



	//demo2.~binarySearchTree<int, int>();

}











