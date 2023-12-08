#include <iostream>
#include "linkedBinaryTree.h"




int main()
{
	using namespace std;

	linkedBinaryTree<int> demo;

	vector<int>preOrder{ 1,2,3,4,6,8,5,7,9,10,11,12 };
	vector<int>inOrder{ 1,6,8,4,3,5,9,7,10,11,12,2 };
	demo.buildBinaryTreePreIn(preOrder, inOrder);

	demo.preOrderOutput();
	demo.inOrderOutput();
	demo.postOrderOutput();

}