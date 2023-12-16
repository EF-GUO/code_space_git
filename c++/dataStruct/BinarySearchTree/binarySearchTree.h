#pragma once

#include "bSTree.h"
#include "binaryTreeNode.h"


template<typename K, typename E>
class binarySearchTree :public bSTree<K, E>
{
public:
	binarySearchTree()
		:root(nullptr), treeSize(0) {}

	~binarySearchTree();

	bool empty() const { return treeSize == 0; };
	int size() const { return treeSize; };

	std::pair<const K, E>* find(const K& theKey) const;
	void erase(const K& theKey);
	void insert(const std::pair<const K, E>& thePair);

	void ascend();


private:
	binaryTreeNode<std::pair<const K, E>>* root;
	int treeSize;
	static void output(binaryTreeNode<std::pair<const K, E>>* theNode)
	{
		std::cout << "Key: " << theNode->element.first << "\t" << "Val: " << theNode->element.second << std::endl;
	}
	static void (*visit)(binaryTreeNode<std::pair<const K, E>>* theNode);

	static void delHelper(binaryTreeNode<std::pair<const K, E>>* theNode)
	{
		delete theNode;
	}

	static void inOrder(binaryTreeNode<std::pair<const K, E>>* theNode);
	static void postOrder(binaryTreeNode<std::pair<const K, E>>* theNode);
};

void (*binarySearchTree<int, int>::visit)(binaryTreeNode<std::pair<const int, int>>* theNode);

template<typename K, typename E>
inline binarySearchTree<K, E>::~binarySearchTree()
{
	visit = delHelper;
	postOrder(root);
}

template<typename K, typename E>
inline void binarySearchTree<K, E>::ascend()
{
	visit = output;
	inOrder(root);
}

template<typename K, typename E>
void binarySearchTree<K, E>::inOrder(binaryTreeNode<std::pair<const K, E>>* theNode)
{
	if (theNode)
	{
		inOrder(theNode->leftChild);
		visit(theNode);
		inOrder(theNode->rightChild);
	}
}

template<typename K, typename E>
inline void binarySearchTree<K, E>::postOrder(binaryTreeNode<std::pair<const K, E>>* theNode)
{
	if (theNode)
	{
		postOrder(theNode->leftChild);
		postOrder(theNode->rightChild);
		visit(theNode);
	}
}

template<typename K, typename E>
inline std::pair<const K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{
	binaryTreeNode<std::pair<const K, E>>* currentNode = root;
	while (currentNode)
	{
		if (theKey < currentNode->element.first)
			currentNode = currentNode->leftChild;
		else
		{
			if (theKey > currentNode->element.first)
				currentNode = currentNode->rightChild;
			else
				return &currentNode->element;
		}
	}
	return nullptr;
}

template<typename K, typename E>
inline void binarySearchTree<K, E>::erase(const K& theKey)
{
	binaryTreeNode<std::pair<const K, E>>
		* preDeleteNode = nullptr,
		* deleteNode = root;

	while (deleteNode && deleteNode->element.first != theKey)
	{
		preDeleteNode = deleteNode;
		if (theKey < deleteNode->element.first)
			deleteNode = deleteNode->leftChild;
		else
			deleteNode = deleteNode->rightChild;
	}

	if (!deleteNode)	//没有查找到要删除的关键字
		return;

	if (deleteNode->leftChild && deleteNode->rightChild)
	{
		binaryTreeNode<std::pair<const K, E>>
			* leftMaxNode = deleteNode->leftChild,
			* preLeftMaxNode = deleteNode;

		//找到左子树要删除的最大子节点
		while (leftMaxNode->rightChild)
		{
			preLeftMaxNode = leftMaxNode;
			leftMaxNode = leftMaxNode->rightChild;
		}
		//创建新的节点insteadOfDelNode(leftMaxNode->element,p->left,p->right)
		binaryTreeNode<std::pair<const K, E>>
			* insteadOfDelNode = new binaryTreeNode<std::pair<const K, E>>
			(leftMaxNode->element, deleteNode->leftChild, deleteNode->rightChild);

		if (!preDeleteNode)
			root = insteadOfDelNode;
		else if (deleteNode == preDeleteNode->leftChild)
			preDeleteNode->leftChild = insteadOfDelNode;
		else
			preDeleteNode->rightChild = insteadOfDelNode;
		if (preLeftMaxNode == deleteNode)
			preDeleteNode = insteadOfDelNode;
		else
			preDeleteNode = preLeftMaxNode;
		delete deleteNode;
		deleteNode = leftMaxNode;
	}


	//下面的代码处理要删除的节点只有一个或者两个子节点
	binaryTreeNode<std::pair<const K, E>>* childNode;

	if (deleteNode->leftChild)
		childNode = deleteNode->leftChild;
	else
		childNode = deleteNode->rightChild;

	if (deleteNode == root)
		root = childNode;
	else
	{
		if (deleteNode == preDeleteNode->leftChild)
			preDeleteNode->leftChild = childNode;
		else
			preDeleteNode->rightChild = childNode;
	}

	delete deleteNode;
	--treeSize;

}

template<typename K, typename E>
inline void binarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair)
{
	binaryTreeNode < std::pair<const K, E>>
		* previousNode = nullptr,
		* currentNode = root;
	while (currentNode)
	{
		previousNode = currentNode;
		if (currentNode->element.first < thePair.first)
			currentNode = currentNode->rightChild;
		else
		{
			if (currentNode->element.first > thePair.first)
				currentNode = currentNode->leftChild;
			else
			{
				currentNode->element.second = thePair.second;
				return;
			}
		}
	}
	binaryTreeNode<std::pair<const K, E>>* newNode = new binaryTreeNode<std::pair<const K, E>>(thePair);
	if (!root)
		root = newNode;
	else
	{
		if (previousNode->element.first < thePair.first)
			previousNode->rightChild = newNode;
		else
			previousNode->leftChild = newNode;
	}
	++treeSize;
}




















