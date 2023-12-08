#pragma once
//in github

#include<iostream>
#include <queue>
#include <map>
#include "binaryTree.h"
#include "binaryTreeNode.h"


template<typename T>
class linkedBinaryTree :binaryTree<binaryTreeNode<T>>
{

public:
	linkedBinaryTree() : root(nullptr), treeSize(0) {}
	~linkedBinaryTree() { erase(); }
	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	//前序遍历
	void preOrder(void (*theVisit)(binaryTreeNode<T>*))
	{
		visit = theVisit;
		preOrder(root);
	}
	//中序遍历
	void inOrder(void (*theVisit)(binaryTreeNode<T>*))
	{
		visit = theVisit;
		inOrder(root);
	}
	//后序遍历
	void postOrder(void (*theVisit)(binaryTreeNode<T>*))
	{
		visit = theVisit;
		postOrder(root);
	}
	//层次遍历 
	void levelOrder(void (*theVisit)(binaryTreeNode<T>*))
	{
		visit = theVisit;
		levelOrder(root);
	}
	void erase()
	{
		postOrder(dispose);
		root = nullptr;
		treeSize = 0;
	}


	//遍历并打印输出

	void preOrderOutput()
	{
		visit = output;
		std::cout << "PreOrderList:\t";
		preOrder(root);
		std::cout << std::endl;
	}
	void inOrderOutput()
	{
		visit = output;
		std::cout << "InOrderList:\t";
		inOrder(root);
		std::cout << std::endl;
	}
	void postOrderOutput()
	{
		visit = output;
		std::cout << "PostOrderList:\t";
		postOrder(root);
		std::cout << std::endl;
	}

	void buildBinaryTreePreIn(std::vector<T>& preOrder, std::vector<T>& inOrder);
	binaryTreeNode<T>* buildBinaryTreePreInHelper(
		std::vector<T>& preOrder, const int preLeft, const int preRight,
		std::vector<T>& inOrder, const int inLeft,
		std::map<T, int>& inMap
	);

	void buildBinaryTreePostIn(std::vector<T>& postOrder, std::vector<T>& inOrder);
	binaryTreeNode<T>* buildBinaryTreePostInHelper(
		std::vector<T>& postOrder, const int postLeft, const int postRight,
		std::vector<T>& inOrder, const int inLeft,
		std::map<T, int>& inMap
	);

private:
	binaryTreeNode<T>* root;
	int treeSize;
	static void (*visit)(binaryTreeNode<T>*);
	static void preOrder(binaryTreeNode<T>* node);
	static void inOrder(binaryTreeNode<T>* node);
	static void postOrder(binaryTreeNode<T>* node);
	static void levelOrder(binaryTreeNode<T>* node);

	static void dispose(binaryTreeNode<T>* node) { delete node; }
	static void output(binaryTreeNode<T>* node) { std::cout << node->element << " ";}

};

void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);

template<typename T>
inline void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* node)
{
	if (node)
	{
		visit(node);
		preOrder(node->leftChild);
		preOrder(node->rightChild);
	}
}

template<typename T>
inline void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* node)
{
	if (node)
	{
		inOrder(node->leftChild);
		visit(node);
		inOrder(node->rightChild);
	}
}

template<typename T>
inline void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* node)
{
	if (node)
	{
		postOrder(node->leftChild);
		postOrder(node->rightChild);
		visit(node);
	}
}

template<typename T>
inline void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T>* node)
{
	//			1
	//		  /   \				step1 [2,3]
	//		2       3			step2 [3,4,5]
	//    /   \   /   \			step3 [4,5,6,7]		
	//  4      5 6      7  

	std::queue<binaryTreeNode<T>*> nodeQueue;
	while (node)
	{
		visit(node);

		if (node->leftChild)
			nodeQueue.push(node->leftChild);
		if (node->rightChild)
			nodeQueue.push(node->rightChild);

		if (nodeQueue.empty())
			return;
		else
		{
			node = nodeQueue.front();
			nodeQueue.pop();
		}
	}
}

template<typename T>
inline void linkedBinaryTree<T>::buildBinaryTreePreIn(std::vector<T>& preOrder, std::vector<T>& inOrder)
{
	if (preOrder.empty() || inOrder.empty())
		return;
	if (preOrder.size() != inOrder.size())
		return;

	root = nullptr;
	treeSize = 0;
	std::map<T, int> inMap;

	for (size_t i = 0; i < preOrder.size(); i++)
		inMap[inOrder[i]] = i;
	root = buildBinaryTreePreInHelper(preOrder, 0, preOrder.size() - 1, inOrder, 0, inMap);
}

template<typename T>
inline binaryTreeNode<T>* linkedBinaryTree<T>::buildBinaryTreePreInHelper(
	std::vector<T>& preOrder, const int preLeft, const int preRight, 
	std::vector<T>& inOrder, const int inLeft,
	std::map<T, int>& inMap
)
{
	if (preLeft > preRight)
		return nullptr;

	binaryTreeNode<T>* node = new binaryTreeNode<T>(preOrder[preLeft]);
	treeSize++;
	int inMid = inMap[node->element];
	int leftSize = inMid - inLeft;

	node->leftChild = buildBinaryTreePreInHelper(
		preOrder,preLeft + 1,preLeft + leftSize,
		inOrder,inLeft,
		inMap
	);

	node->rightChild = buildBinaryTreePreInHelper(
		preOrder, preLeft + leftSize + 1, preRight,
		inOrder,inMid + 1,
		inMap
	);

	return node;
}






























