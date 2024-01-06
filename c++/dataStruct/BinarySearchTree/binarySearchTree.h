#pragma once
#include <iostream>

#include "bSTree.h"
#include "binaryTreeNode.h"


template<typename K, typename E>
class binarySearchTree :public bSTree<K, E>
{
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

	static void outputInRangeHelper(binaryTreeNode<std::pair<const K, E>>* node, const K& theLow, const K& theHigh);

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

	//练习8 添加了outputInRange(theLow,theHigh)方法
	void outputInRange(const K& theLow, const K& theHigh);

	//练习10 利用二叉搜索树对元素进行排序
	void sortArray(K* theArray, const int theSize);
	void sortArray(binaryTreeNode<std::pair<const K, E>>* theNode, K* theArray, int& theSize = 0);

	//练习12，拆分二叉搜索树
	binaryTreeNode<std::pair<const K, E>>* split(const K& theKey, binarySearchTree<K, E>* lessThan = nullptr, binarySearchTree<K, E>* greaterThan = nullptr);

	binaryTreeNode<std::pair<const K, E>>* splitHelper(binaryTreeNode<std::pair<const K, E>>* node, const K& theKey, binaryTreeNode<std::pair<const K, E>>* lessThanRightNode, binaryTreeNode<std::pair<const K, E>>* moreThanLeftNode);

	//练习14,设计一个迭代器，按照关键字的升序查看元素
	class Iterator
	{
	public:
		Iterator(binaryTreeNode<std::pair<const K, E>>* theNode)
			:node(theNode) {}
		E& operator*()
		{
			return node->element.second;
		}

		//前置递增
		Iterator& operator++()
		{

		}

		//后置递增
		Iterator operator++(int)
		{

		}

	private:
		binaryTreeNode<std::pair<const K, E>>* node;
	};

	Iterator begin()
	{
		binaryTreeNode<std::pair<const K, E>>* currentNode = root;
		while (currentNode->leftChild)
			currentNode = currentNode->leftChild;
		return Iterator(currentNode);
	}

	Iterator end()
	{
		binaryTreeNode<std::pair<const K, E>>* currentNode = root;
		while (currentNode->rightChild)
			currentNode = currentNode->rightChild;
		return Iterator(currentNode);
	}

	//练习15,从二叉搜索树中删除最大的元素
	void eraseMax();
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

template<typename K, typename E>
inline void binarySearchTree<K, E>::outputInRange(const K& theLow, const K& theHigh)
{
	if (root)
		outputInRangeHelper(root, theLow, theHigh);
}

template<typename K, typename E>
inline void binarySearchTree<K, E>::outputInRangeHelper(binaryTreeNode<std::pair<const K, E>>* theNode, const K& theLow, const K& theHigh)
{
	if (theNode->leftChild)
		outputInRangeHelper(theNode->leftChild, theLow, theHigh);
	if (theNode->element.first >= theLow && theNode->element.first <= theHigh)
		output(theNode);
	if (theNode->rightChild)
		outputInRangeHelper(theNode->rightChild, theLow, theHigh);
}


inline void binarySearchTree<int, int>::sortArray(int* theArray, const int theSize)
{
	for (int i = 0; i < theSize; i++)
		insert(std::make_pair(theArray[i], i));

	int index = 0;
	sortArray(root, theArray, index);
}

template<typename K, typename E>
inline void binarySearchTree<K, E>::sortArray(binaryTreeNode<std::pair<const K, E>>* theNode, K* theArray, int& theSize)
{
	if (theNode)
	{
		sortArray(theNode->leftChild, theArray, theSize);
		theArray[theSize++] = theNode->element.first;
		sortArray(theNode->rightChild, theArray, theSize);
	}
}

template<typename K, typename E>
inline binaryTreeNode<std::pair<const K, E>>* binarySearchTree<K, E>::split(const K& theKey, binarySearchTree<K, E>* lessThan, binarySearchTree<K, E>* greaterThan)
{

	binaryTreeNode<std::pair<const K, E>>* returnNode = nullptr;

	if (theKey == root->element.first)
	{
		lessThan->root = root->leftChild;
		greaterThan->root = root->rightChild;
		returnNode = root;
		root = nullptr;
		treeSize = 0;
		return returnNode;
	}
	binaryTreeNode<std::pair<const K, E>>
		* currentNode = root,
		* previousCurrentNode = nullptr,
		* lessThanRightNode = nullptr,
		* moreThanLeftNode = nullptr;

	if (theKey > currentNode->element.first)
	{
		while (currentNode && theKey > currentNode->element.first)
		{
			previousCurrentNode = currentNode;
			currentNode = currentNode->rightChild;
		}
		if (!currentNode)
		{
			lessThan->root = root;
			greaterThan->root = nullptr;
			root = nullptr;
			return nullptr;
		}

		if (currentNode->element.first == theKey)
		{
			returnNode = currentNode;
			lessThan->root = root;
			greaterThan->root = nullptr;
			root = nullptr;
			return returnNode;
		}

		binaryTreeNode<std::pair<const K, E>>* nextNode = currentNode->leftChild;
		currentNode->leftChild = previousCurrentNode->rightChild = nullptr;

		lessThan->root = root;
		greaterThan->root = currentNode;

		lessThanRightNode = previousCurrentNode;
		moreThanLeftNode = currentNode;

		root = nextNode;

	}
	else if (theKey < currentNode->element.first)
	{
		while (currentNode && theKey < currentNode->element.first)
		{
			previousCurrentNode = currentNode;
			currentNode = currentNode->leftChild;
		}
		if (!currentNode)
		{
			greaterThan->root = root;
			lessThan->root = nullptr;
			root = nullptr;
			return nullptr;
		}
		if (currentNode->element.first == theKey)
		{
			returnNode = currentNode;
			lessThan->root = root;
			greaterThan->root = nullptr;
			root = nullptr;
			return returnNode;
		}
		binaryTreeNode<std::pair<const K, E>>* nextNode = currentNode->rightChild;
		currentNode->rightChild = previousCurrentNode->leftChild = nullptr;

		lessThan->root = currentNode;;
		greaterThan->root = root;

		lessThanRightNode = currentNode;
		moreThanLeftNode = previousCurrentNode;
		root = nextNode;
	}

	binaryTreeNode<std::pair<const K, E>>* temp = splitHelper(root, theKey, lessThanRightNode, moreThanLeftNode);
	root = nullptr;
	return temp;
}

template<typename K, typename E>
binaryTreeNode<std::pair<const K, E>>* binarySearchTree<K, E>::splitHelper(binaryTreeNode<std::pair<const K, E>>* node, const K& theKey, binaryTreeNode<std::pair<const K, E>>* lessThanRightNode, binaryTreeNode<std::pair<const K, E>>* moreThanLeftNode)
{
	if (!node)
		return nullptr;

	binaryTreeNode<std::pair<const K, E>>
		* currentNode = node,
		* previousCurrentNode = nullptr;
	if (theKey == currentNode->element.first)
	{
		moreThanLeftNode->leftChild = currentNode->rightChild;
		lessThanRightNode->rightChild = currentNode->leftChild;
		return currentNode;
	}
	//找到当前最外层的分界点

	if (theKey > currentNode->element.first)
	{
		while (currentNode && theKey > currentNode->element.first)
		{
			previousCurrentNode = currentNode;
			currentNode = currentNode->rightChild;
		}
		if (!currentNode)
		{
			lessThanRightNode->rightChild = node;
			return nullptr;
		}
		binaryTreeNode<std::pair<const K, E>>* nextNode = currentNode->leftChild;
		currentNode->leftChild = previousCurrentNode->rightChild = nullptr;

		lessThanRightNode->rightChild = node;
		moreThanLeftNode->leftChild = currentNode;

		lessThanRightNode = previousCurrentNode;
		moreThanLeftNode = currentNode;

		node = nextNode;
	}
	else if (theKey < currentNode->element.first)
	{
		while (currentNode && theKey < currentNode->element.first)
		{
			previousCurrentNode = currentNode;
			currentNode = currentNode->leftChild;
		}

		if (!currentNode)
		{
			moreThanLeftNode->leftChild = node;
			return nullptr;
		}

		binaryTreeNode<std::pair<const K, E>>* nextNode = currentNode->rightChild;
		currentNode->rightChild = previousCurrentNode->leftChild = nullptr;

		lessThanRightNode->rightChild = currentNode;
		moreThanLeftNode->leftChild = node;

		lessThanRightNode = currentNode;
		moreThanLeftNode = previousCurrentNode;

		node = nextNode;

	}
	return splitHelper(node, theKey, lessThanRightNode, moreThanLeftNode);

}


template<typename K, typename E>
void binarySearchTree<K, E>::eraseMax()
{
	binaryTreeNode<std::pair<const K, E>>
		* currentNode = root,
		* previousCurrentNode = nullptr;

	while (currentNode->rightChild)
	{
		previousCurrentNode = currentNode;
		currentNode = currentNode->rightChild;
	}

	if (currentNode->leftChild)
		previousCurrentNode->rightChild = currentNode->leftChild;
	else
		previousCurrentNode->rightChild = nullptr;

	delete currentNode;
	treeSize--;
}


