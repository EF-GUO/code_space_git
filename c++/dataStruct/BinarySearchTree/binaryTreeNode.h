#pragma once



template<typename T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>
		* leftChild,
		* rightChild;

	binaryTreeNode()
		:leftChild(nullptr), rightChild(nullptr) {}

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

