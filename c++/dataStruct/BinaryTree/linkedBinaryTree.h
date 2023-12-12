#pragma once
//git

#include<iostream>
#include <queue>
#include <map>
#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "expressionTree.h"

template<typename T>
class linkedBinaryTree :binaryTree<binaryTreeNode<T>>
{

public:
	linkedBinaryTree() : root(nullptr), treeSize(0) {}
	~linkedBinaryTree() { erase(); }
	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }

	binaryTreeNode<T>* getRoot() { return root; }

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
	void levelOrder(void (*theVisit)(binaryTreeNode<T>*) = output)
	{
		visit = theVisit;
		std::cout << "LevelOrderList:\t";
		levelOrder(root);
		std::cout << std::endl;
	}

	//迭代遍历二叉树(默认打印输出)
	//前序
	void preOrderByLoop(void (*theVisit)(binaryTreeNode<T>*) = output)
	{
		visit = theVisit;
		std::cout << "PreOrderList(loop):\t";
		preOrderByLoop(root);
		std::cout << std::endl;
	}
	//中序
	void inOrderByLoop(void (*theVisit)(binaryTreeNode<T>*) = output)
	{
		visit = theVisit;
		std::cout << "InOrderList(loop):\t";
		inOrderByLoop(root);
		std::cout << std::endl;
	}
	//后序
	void postOrderByLoop(void (*theVisit)(binaryTreeNode<T>*) = output)
	{
		visit = theVisit;
		std::cout << "PostOrderList(loop):\t";
		postOrderByLoop(root);
		std::cout << std::endl;
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

	//返回二叉树高度
	int height()
	{
		return height(root);
	}

	//返回节点数
	int countNodes()
	{
		visit = countNode;
		postOrder(root);
		return count;
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
		std::vector<T>& inOrder, const int inLeft, const int inRight,
		std::map<T, int>& inMap
	);

	bool compare(const binaryTree<T>* const theTree) const;


private:
	binaryTreeNode<T>* root;
	int treeSize;
	static int count;

	static void (*visit)(binaryTreeNode<T>*);
	static void preOrder(binaryTreeNode<T>* node);
	static void inOrder(binaryTreeNode<T>* node);
	static void postOrder(binaryTreeNode<T>* node);
	static void levelOrder(binaryTreeNode<T>* node);

	//loop
	void preOrderByLoop(binaryTreeNode<T>* node);
	void inOrderByLoop(binaryTreeNode<T>* node);
	void postOrderByLoop(binaryTreeNode<T>* node);
	//get height
	static int height(binaryTreeNode<T>* node);
	//get count
	static void countNode(binaryTreeNode<T>* node) { count++; }
	static void dispose(binaryTreeNode<T>* node) { delete node; }
	static void output(binaryTreeNode<T>* node) { std::cout << node->element << " "; }

	//compare
	static bool compare(const binaryTreeNode<T>* const Lhs, const binaryTreeNode<T>* const Rhs);
};
int linkedBinaryTree<int>::count;
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
inline void linkedBinaryTree<T>::preOrderByLoop(binaryTreeNode<T>* node)
{

	binaryTreeNode<T>** theStack = new binaryTreeNode<T>*[treeSize];
	int stackTop = -1;
	while (stackTop != -1 || node)
	{
		while (node)
		{
			visit(node);
			theStack[++stackTop] = node;
			node = node->leftChild;
		}
		node = theStack[stackTop--];
		node = node->rightChild;
	}
	delete theStack;
}

template<typename T>
inline void linkedBinaryTree<T>::inOrderByLoop(binaryTreeNode<T>* node)
{
	binaryTreeNode<T>** theStack = new binaryTreeNode<T>*[treeSize];
	int stackTop = -1;

	while (node || stackTop != -1)
	{
		while (node)
		{
			theStack[++stackTop] = node;
			node = node->leftChild;
		}
		node = theStack[stackTop--];
		visit(node);
		node = node->rightChild;
	}
}

template<typename T>
inline void linkedBinaryTree<T>::postOrderByLoop(binaryTreeNode<T>* node)
{
	binaryTreeNode<T>** theStack = new binaryTreeNode<T>*[treeSize];
	int stackTop = -1;
	binaryTreeNode<T>* previousNode = nullptr;
	while (node || stackTop != -1)
	{
		while (node)
		{
			theStack[++stackTop] = node;
			node = node->leftChild;
		}

		node = theStack[stackTop--];
		if (!node->rightChild || node->rightChild == previousNode)
		{
			visit(node);
			previousNode = node;
			node = nullptr;
		}
		else
		{
			theStack[++stackTop] = node;
			node = node->rightChild;
		}
	}
}

template<typename T>
inline int linkedBinaryTree<T>::height(binaryTreeNode<T>* node)
{
	if (!node)
		return 0;

	int leftHeight = height(node->leftChild);
	int rightHeight = height(node->rightChild);
	return std::max(leftHeight, rightHeight) + 1;
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
		preOrder, preLeft + 1, preLeft + leftSize,
		inOrder, inLeft,
		inMap
	);
	node->rightChild = buildBinaryTreePreInHelper(
		preOrder, preLeft + leftSize + 1, preRight,
		inOrder, inMid + 1,
		inMap
	);

	return node;
}

template<typename T>
inline void linkedBinaryTree<T>::buildBinaryTreePostIn(std::vector<T>& postOrder, std::vector<T>& inOrder)
{
	if (postOrder.empty() || inOrder.empty())
		return;
	if (postOrder.size() != inOrder.size())
		return;

	root = nullptr;
	treeSize = 0;
	std::map<T, int> inMap;

	for (size_t i = 0; i < postOrder.size(); i++)
		inMap[inOrder[i]] = i;
	root = buildBinaryTreePostInHelper(postOrder, 0, postOrder.size() - 1, inOrder, 0, inOrder.size() - 1, inMap);
}

template<typename T>
inline binaryTreeNode<T>* linkedBinaryTree<T>::buildBinaryTreePostInHelper(std::vector<T>& postOrder, const int postLeft, const int postRight, std::vector<T>& inOrder, const int inLeft, const int inRight, std::map<T, int>& inMap)
{
	if (postLeft > postRight)
		return nullptr;

	binaryTreeNode<T>* node = new binaryTreeNode<T>(postOrder[postRight]);
	treeSize++;
	int inMid = inMap[postOrder[postRight]];
	int rightSize = inRight - inMid;

	node->leftChild = buildBinaryTreePostInHelper(
		postOrder, postLeft, postRight - rightSize - 1,
		inOrder, inLeft, inMid - 1, inMap
	);

	node->rightChild = buildBinaryTreePostInHelper(
		postOrder, postRight - rightSize, postRight - 1,
		inOrder, inMid + 1, inRight, inMap
	);
	return node;
}


template<typename T>
inline bool linkedBinaryTree<T>::compare(const binaryTree<T>* const theTree) const
{
	if (!theTree)
		return false;
	if (treeSize != theTree)
		return false;
	return compare(root, theTree);
}


template<typename T>
inline bool linkedBinaryTree<T>::compare(const binaryTreeNode<T>* const Lhs, const binaryTreeNode<T>* const Rhs)
{
	if (!Lhs && !Rhs)
		return true;
	if (!Lhs || !Rhs)
		return false;

	return Lhs->element == Rhs->element && compare(Lhs->leftChild, Lhs->leftChild) && compare(Rhs->rightChild, Rhs->rightChild);
}







