#pragma once

#include "bSTree.h"
#include "binaryTreeNode.h"

template<typename K, typename E>
class dBinarySearchTree :public bSTree<K, E>
{
public:
	dBinarySearchTree()
		:root(nullptr), treeSize(0) {}
	~dBinarySearchTree();

	bool empty() const;
	int size() const;
	std::pair<const K, E>* find(const K& theKey) const;
	void erase(const K& theKey);
	void insert(const std::pair<const K, E>& thePair);
	void ascend();

private:
	binaryTreeNode<std::pair<const K, E>>* root;
	int treeSize;

	static void output(binaryTreeNode<std::pair<const K, E>>* theNode);

	static void deleteNode(binaryTreeNode<std::pair<const K, E>>* theNode);

	static void (*visit)(binaryTreeNode<std::pair<const K, E>>* theNode);
	static void inOrder(binaryTreeNode<std::pair<const K, E>>* theNode);
	static void postOrder(binaryTreeNode<std::pair<const K, E>>* theNode);
};

template<typename K, typename E>
inline dBinarySearchTree<K, E>::~dBinarySearchTree()
{
	visit = deleteNode;
	postOrder(root);
}

template<typename K, typename E>
inline bool dBinarySearchTree<K, E>::empty() const
{
	return treeSize == 0;
}

template<typename K, typename E>
inline int dBinarySearchTree<K, E>::size() const
{
	return treeSize;
}

template<typename K, typename E>
inline std::pair<const K, E>* dBinarySearchTree<K, E>::find(const K& theKey) const
{
	binaryTreeNode<std::pair<const K, E>>
		* currentNode = root;
	while (currentNode)
	{
		if (currentNode->element.first == theKey)
			return currentNode;

		if (theKey < currentNode->element.first)
			currentNode = currentNode->leftChild;
		else if (theKey > currentNode->element.first)
			currentNode = currentNode->rightChild;
	}
	return nullptr;
}

template<typename K, typename E>
inline void dBinarySearchTree<K, E>::erase(const K& theKey)
{
	binaryTreeNode<std::pair<const K, E>>
		* deleteNode = root,
		* previousDeleteNode = nullptr;

	while (deleteNode && deleteNode->element.first != theKey)
	{
		previousDeleteNode = deleteNode;
		if (theKey < deleteNode->element.first)
			deleteNode = deleteNode->leftChild;
		else
			deleteNode = deleteNode->rightChild;
	}

	//没找到
	if (!deleteNode)	return;

	//要删除的节点有两个子节点
	if (deleteNode->leftChild && deleteNode->rightChild)
	{
		binaryTreeNode<std::pair<const K, E>>
			* leftMaxNode = deleteNode->leftChild,
			* previousLeftMaxNode = deleteNode;

		//用左子树最大的元素替换删除位置的节点
		while (leftMaxNode->rightChild)
		{
			previousLeftMaxNode = leftMaxNode;
			leftMaxNode = leftMaxNode->rightChild;
		}

		//创建新的节点
		binaryTreeNode<std::pair<const K, E>>
			* insteadNode = new binaryTreeNode < std::pair<const K, E>>
			(leftMaxNode->element.first, deleteNode->leftChild, deleteNode->rightChild);

		//如果要删除的节点是root根节点
		if (!previousDeleteNode)
			root = insteadNode;
		else if (deleteNode = previousDeleteNode->leftChild)
			previousDeleteNode->leftChild = insteadNode;
		else
			previousDeleteNode->rightChild = insteadNode;

		if (previousLeftMaxNode == deleteNode)
			previousDeleteNode = insteadNode;
		else
			previousDeleteNode = previousLeftMaxNode;
		delete deleteNode;
		deleteNode = leftMaxNode;
	}

	//要删除的节点只有一个或者两个子节点
	binaryTreeNode<std::pair<const K, E>> *childNode;
	if (deleteNode->leftChild)
		childNode = deleteNode->leftChild;
	else
		childNode = deleteNode->rightChild;

	if (deleteNode == root)
		root = childNode;
	else
	{
		if (deleteNode == previousDeleteNode->leftChild)
			preDeleteNode->leftChild = childNode;
		else
			preDeleteNode->rightChild = childNode;
	}

	delete deleteNode;
	--treeSize;
}

template<typename K, typename E>
inline void dBinarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair)
{
	binaryTreeNode<std::pair<const K, E>>
		* insertNode = new binaryTreeNode<std::pair<const K, E>>(thePair);

	//当root为空时
	if (!root)
	{
		root = insertNode;
		++treeSize;
		return;
	}

	binaryTreeNode<std::pair<const K, E>>
		* currentNode = root,
		* previousCurrentNode = nullptr;

	while (currentNode)
	{
		previousCurrentNode = currentNode;
		
		if (thePair.first <= currentNode->element.first)
			currentNode = currentNode->leftChild;
		if (thePair.first > currentNode->element.first)
			currentNode = currentNode->rightChild;
	}

	if (thePair.first < previousCurrentNode->element.first)
		previousCurrentNode->leftChild = insertNode;
	else
		previousCurrentNode->rightChild = insertNode;
	treeSize++;
}

template<typename K, typename E>
inline void dBinarySearchTree<K, E>::ascend()
{
	visit = output;
	inOrder(root);
}

template<typename K, typename E>
inline void dBinarySearchTree<K, E>::output(binaryTreeNode<std::pair<const K, E>>* theNode)
{
	std::cout << theNode->element.first << " " << theNode->element.second << std::endl;
}

template<typename K, typename E>
inline void dBinarySearchTree<K, E>::deleteNode(binaryTreeNode<std::pair<const K, E>>* theNode)
{
	delete theNode;
}

template<typename K, typename E>
inline void dBinarySearchTree<K, E>::inOrder(binaryTreeNode<std::pair<const K, E>>* theNode)
{
	if (theNode)
	{
		inOrder(theNode->leftChild);
		visit(theNode);
		inOrder(theNode->rightChild);
	}
}

template<typename K, typename E>
inline void dBinarySearchTree<K, E>::postOrder(binaryTreeNode<std::pair<const K, E>>* theNode)
{
	if (theNode)
	{
		postOrder(theNode->leftChild);
		postOrder(theNode->rightChild);
		visit(theNode);
	}
}



























