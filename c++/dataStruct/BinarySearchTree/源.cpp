#include <iostream>

#include "binarySearchTree.h"

int main()
{
	using namespace std;

	binarySearchTree<int, int> demo;
	demo.insert(make_pair<int, int>(20, 1));
	demo.insert(make_pair<int, int>(15, 2));
	demo.insert(make_pair<int, int>(25, 3));
	demo.insert(make_pair<int, int>(12, 4));
	demo.insert(make_pair<int, int>(18, 5));
	demo.insert(make_pair<int, int>(30, 6));

	demo.ascend();
	cout << endl << endl;
	cout << demo.find(12)->first<<"  "<< demo.find(12)->second << endl;

}











