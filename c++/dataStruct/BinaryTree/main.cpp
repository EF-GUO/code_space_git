#include <iostream>
#include "linkedBinaryTree.h"




int main()
{
	using namespace std;

	linkedBinaryTree<int> demo;

	linkedBinaryTree<int> demo1;

	vector<int>preOrder{ 1,2,3,4,6,8,5,7,9,10,11,12 };
	vector<int>inOrder{ 1,6,8,4,3,5,9,7,10,11,12,2 };
	vector<int>postOrder{ 8,6,4,9,12,11,10,7,5,3,2,1 };
	//demo.buildBinaryTreePreIn(preOrder, inOrder);
	demo.buildBinaryTreePostIn(postOrder, inOrder);

	demo.preOrderOutput();
	demo.inOrderOutput();
	demo.postOrderOutput();
}