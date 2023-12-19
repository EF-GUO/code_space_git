#pragma once

#include <stdexcept>
#include <stack>
#include "binaryTreeNode.h"
#include "indexedBSTree.h"
#include "bSTree.h"

template<typename K, typename E>
class indexedBinarySearchTree :public indexedBSTree<K, E>
{
public:
	indexedBinarySearchTree();
	~indexedBinarySearchTree();

	//ADT methods
	bool empty() const;
	int size() const;
	std::pair<const K, E>* find(const K& theKey) const;
	void erase(const K& theKey);
	void insert(const std::pair<const K, E>& thePair);
	void ascend();
	std::pair<const K, E>* get(const int theIndex) const;
	void deleteByIndex(const int theIndex);

private:
	indexedBinarySearchTreeNode<std::pair<const K, E>>* root;	//root�ڵ�
	int treeSize;

	//vist Node method pointer
	static void (*visit)(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode);

	//static print out the node
	static void output(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode);

	//static traverse methods
	static void inOrder(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode);
	static void postOrder(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode);

	//deleteNode 
	static void deleteNode(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode);

};

void (*indexedBinarySearchTree<int, int>::visit)(indexedBinarySearchTreeNode<std::pair<const int, int>>* theNode);


template<typename K, typename E>
inline indexedBinarySearchTree<K, E>::indexedBinarySearchTree()
	:root(nullptr), treeSize(0) {}

template<typename K, typename E>
inline indexedBinarySearchTree<K, E>::~indexedBinarySearchTree()
{
	visit = deleteNode;
	output(root);
}

template<typename K, typename E>
inline bool indexedBinarySearchTree<K, E>::empty() const { return treeSize == 0; }

template<typename K, typename E>
inline int indexedBinarySearchTree<K, E>::size() const { return treeSize; }

template<typename K, typename E>
inline std::pair<const K, E>* indexedBinarySearchTree<K, E>::find(const K& theKey) const
{
	indexedBinarySearchTreeNode<std::pair<const K, E>>
		* currentNode = root,
		* previousCurrentNode = nullptr;

	while (currentNode)
	{
		if (currentNode->element.first == theKey)
			return &currentNode->element;
		previousCurrentNode = currentNode;
		if (theKey < currentNode->element.first)
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;
	}

	return nullptr;
}

template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::erase(const K& theKey)
{
	if (!root)
		return;

	indexedBinarySearchTreeNode<std::pair<const K, E>>
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
	//û�ҵ�Ҫɾ���ļ�ֵ��
	if (!deleteNode)
		return;

	//��Ҫɾ���Ľڵ����������ӽڵ�
	if (deleteNode->leftChild && deleteNode->rightChild)
	{
		indexedBinarySearchTreeNode<std::pair<const K, E>>
			* leftMaxNode = deleteNode->leftChild,
			* previousLeftMaxNode = deleteNode;

		while (leftMaxNode->rightChild)
		{
			previousLeftMaxNode = leftMaxNode;
			leftMaxNode = leftMaxNode->rightChild;
		}

		//�����滻ɾ���ڵ���½ڵ�
		indexedBinarySearchTreeNode<std::pair<const K, E>>
			* insteadOfNode = new indexedBinarySearchTreeNode<std::pair<const K, E>>
			(leftMaxNode->element, deleteNode->leftChild, deleteNode->rightChild);

		if (!previousDeleteNode)
			root = insteadOfNode;
		else
			if (deleteNode == previousDeleteNode->leftChild)
				previousDeleteNode->leftChild = insteadOfNode;
			else
				previousDeleteNode->rightChild = insteadOfNode;
		if (previousLeftMaxNode == deleteNode)
			previousDeleteNode = insteadOfNode;
		else
			previousDeleteNode = previousLeftMaxNode;
		delete deleteNode;
		deleteNode = leftMaxNode;
	}
	//Ҫɾ���Ľڵ���1���ӽڵ���������ӽڵ�
	//����ɾ���ڵ��µ��ֽڵ�
	indexedBinarySearchTreeNode<std::pair<const K, E>>* childNode;
	if (deleteNode->leftChild)
		childNode = deleteNode->leftChild;
	else
		childNode = deleteNode->rightChild;

	//��ɾ���Ľڵ��ɾ���ڵ�ĸ��ڵ���������
	if (deleteNode == root)	//��Ҫɾ���Ľڵ���root�ڵ�
		root = childNode;
	else
	{
		if (previousDeleteNode->leftChild == deleteNode)
			previousDeleteNode->leftChild = childNode;
		else
			previousDeleteNode->rightChild = childNode;
	}

	//�ͷ�ɾ���ڵ�
	delete deleteNode;
	--treeSize;

}

template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair)
{
	indexedBinarySearchTreeNode<std::pair<const K, E>>
		* currentNode = root,
		* previousCurrentNode = nullptr;

	std::stack<indexedBinarySearchTreeNode<std::pair<const K, E>>*> nodeStack;

	while (currentNode)
	{
		previousCurrentNode = currentNode;

		//��ǰ��Ҫ����ļ�ֵ�ԣ����Ѿ����ڣ��޸�ֵ
		if (currentNode->element.first == thePair.first) {
			currentNode->element.second = thePair.second;
			return;
		}
		if (currentNode->element.first < thePair.first)
			currentNode = currentNode->rightChild;
		else
		{
			nodeStack.push(currentNode);
			currentNode = currentNode->leftChild;
		}
	}

	indexedBinarySearchTreeNode<std::pair<const K, E>>
		* insertNode = new indexedBinarySearchTreeNode<std::pair<const K, E>>(thePair);
	if (!root)
	{
		root = insertNode;
		treeSize++;
		return;
	}
	if (thePair.first < previousCurrentNode->element.first)
		previousCurrentNode->leftChild = insertNode;
	else
		previousCurrentNode->rightChild = insertNode;

	//������ת�ڵ��leftSizeֵ===>leftSize++
	while (!nodeStack.empty())
	{
		nodeStack.top()->leftSize++;
		nodeStack.pop();
	}

	++treeSize;
}

template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::ascend()
{
	visit = output;
	inOrder(root);
	std::cout << std::endl;
}

template<typename K, typename E>
inline std::pair<const K, E>* indexedBinarySearchTree<K, E>::get(const int theIndex) const
{
	//����У��
	if (theIndex < 0 || theIndex >= treeSize)
		throw std::logic_error("index error");
	if (theIndex == root->leftSize)
		return &root->element;

	indexedBinarySearchTreeNode<std::pair<const K, E>>
		* currentNode = root;

	int currentIndex = root->leftSize;
	while (currentNode)
	{
		//�ҵ���ָ������
		if (theIndex == currentIndex)
			return &currentNode->element;
		//�����ڵ�ǰ���������
		if (theIndex < currentIndex)
		{
			currentIndex = currentIndex - (currentNode->leftSize - currentNode->leftChild->leftSize);
			currentNode = currentNode->leftChild;
		}
		//�����ڵ�ǰ�������ұ�
		else if (theIndex > currentNode->leftSize)
		{
			currentNode = currentNode->rightChild;
			currentIndex = currentIndex + currentNode->leftSize + 1;
		}
	}
	return nullptr;
}

template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::deleteByIndex(const int theIndex)
{
	if (!root)
		return;

	//check theIndex
	if (theIndex < 0 || theIndex >= treeSize)
		throw std::domain_error("index error of Index : " + theIndex);

	indexedBinarySearchTreeNode<std::pair<const K, E>>
		* deleteNode = root,
		* previousDeleteNode = nullptr;

	std::stack<indexedBinarySearchTreeNode<std::pair<const K, E>>*> nodeStack;
	int currentIndex = root->leftSize;

	while (deleteNode && theIndex != currentIndex)
	{
		previousDeleteNode = deleteNode;
		if (theIndex < currentIndex)
		{
			//����ǽ������ӽڵ㣬�򽫵�ǰ�ڵ㱣�棬��������޸ĵ�ǰ�ڵ��leftSizeֵ
			nodeStack.push(deleteNode);
			currentIndex = currentIndex - (deleteNode->leftSize - deleteNode->leftChild->leftSize);
			deleteNode = deleteNode->leftChild;
		}
		else
		{
			deleteNode = deleteNode->rightChild;
			currentIndex = currentIndex + deleteNode->leftSize + 1;
		}
	}
	//û�ҵ�Ҫɾ���Ľڵ�
	if (!deleteNode)
		return;

	//�����ǰ�ڵ��������ӽڵ�
	if (deleteNode->leftChild && deleteNode->rightChild)
	{
		indexedBinarySearchTreeNode<std::pair<const K, E>>
			* leftMaxNode = deleteNode->leftChild,
			* previousLeftMaxNode = deleteNode;

		while (leftMaxNode->rightChild)
		{
			previousLeftMaxNode = leftMaxNode;
			leftMaxNode = leftMaxNode->rightChild;
		}

		//�����µ��滻�ڵ�
		indexedBinarySearchTreeNode<std::pair<const K, E>>
			* insteadNode = new indexedBinarySearchTreeNode<std::pair<const K, E>>
			(leftMaxNode->element, deleteNode->leftChild, deleteNode->rightChild, deleteNode->leftSize - 1);

		if (!previousDeleteNode)
			root = insteadNode;
		else
			if (deleteNode = previousDeleteNode->leftChild)
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
	//����ǰ�ڵ�û���ӽڵ������һ���ӽڵ�����

	//���浱ǰҪɾ���Ľڵ���ӽڵ�
	indexedBinarySearchTreeNode<std::pair<const K, E>>* childNode;

	if (deleteNode->leftChild)
		childNode = deleteNode->leftChild;
	else
		childNode = deleteNode->rightChild;

	//���ɾ��root�ڵ㣬root�ڵ�ֻ��һ���ֽڵ�
	if (deleteNode == root)
		root = childNode;
	else
	{
		if (previousDeleteNode->leftChild == deleteNode)
			previousDeleteNode->leftChild = childNode;
		else
			previousDeleteNode->rightChild = childNode;
	}

	delete deleteNode;
	--treeSize;
	
	while (!nodeStack.empty())
	{
		nodeStack.top()->leftSize--;
		nodeStack.pop();
	}

}


template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::output(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode)
{
	if (theNode)
	{
		std::cout
			<< "theKey: " << theNode->element.first << "\t"
			<< "theVal: " << theNode->element.second << "\t"
			<< "theLeftSize" << theNode->leftSize <<
			std::endl;
	}
}

template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::inOrder(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode)
{
	if (theNode)
	{
		inOrder(theNode->leftChild);
		visit(theNode);
		inOrder(theNode->rightChild);
	}
}

template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::postOrder(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode)
{
	if (theNode)
	{
		postOrder(theNode->leftChild);
		postOrder(theNode->rightChild);
		visit(theNode);
	}
}

template<typename K, typename E>
inline void indexedBinarySearchTree<K, E>::deleteNode(indexedBinarySearchTreeNode<std::pair<const K, E>>* theNode)
{
	delete theNode;
}
