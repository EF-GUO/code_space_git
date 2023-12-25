#pragma once



template<typename T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>
		* leftChild,
		* rightChild;

	binaryTreeNode()
		:element(), leftChild(nullptr), rightChild(nullptr) {}

	binaryTreeNode(const T& theElement)
		:element(theElement), leftChild(nullptr), rightChild(nullptr) {}

	binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeftChild, binaryTreeNode<T>* theRightChild)
		:element(theElement), leftChild(theLeftChild), rightChild(theRightChild) {}
};

template<typename T>
struct indexedBinarySearchTreeNode : public binaryTreeNode<T>
{
	int leftSize;
	indexedBinarySearchTreeNode<T>
		* leftChild,
		* rightChild;

	indexedBinarySearchTreeNode()
		:leftSize(0), binaryTreeNode<T>() {}

	indexedBinarySearchTreeNode(const T& theElement)
		: binaryTreeNode<T>(theElement), leftSize(0), leftChild(nullptr), rightChild(nullptr) {}

	indexedBinarySearchTreeNode(
		const T& theElement,
		indexedBinarySearchTreeNode<T>* theLeftChild,
		indexedBinarySearchTreeNode<T>* theRightChild
	)
		:binaryTreeNode<T>(theElement), leftSize(0), leftChild(theLeftChild), rightChild(theRightChild) {}

	indexedBinarySearchTreeNode(
		const T& theElement,
		indexedBinarySearchTreeNode<T>* theLeftChild,
		indexedBinarySearchTreeNode<T>* theRightChild,
		const int theLeftSize
	)
		:binaryTreeNode<T>(theElement), leftSize(theLeftSize), leftChild(theLeftChild), rightChild(theRightChild) {}


};

template<typename T>
struct avlNode
{
	T element;
	int bf;		//Æ½ºâÒò×Ó
	
	avlNode<T>
		* leftChild,
		* rightChild;

	avlNode()
		:element(), bf(0), leftChild(nullptr), rightChild(nullptr) {}

	avlNode(const T& theElement)
		:element(theElement), bf(0), leftChild(nullptr), rightChild(nullptr) {}

	avlNode(const T& theElement, const int theBf)
		:element(theElement), bf(theBf), leftChild(nullptr), rightChild(nullptr) {}

	avlNode(
		const T& theElement,
		const int theBf,
		avlNode<T>* theLeftChild,
		avlNode<T>* theRightChild
	)
		:element(theElement), bf(theBf), leftChild(theLeftChild), rightChild(theRightChild) {}
};
