#pragma once


template<typename T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;

	binaryTreeNode() = default;

	binaryTreeNode(const T& theElement)
		:element(theElement), leftChild(nullptr), rightChild(nullptr)
	{}
	binaryTreeNode(const T& theElement,binaryTreeNode<T>* theLeftChild,binaryTreeNode<T>* theRightChild)
		:element(theElement),leftChild(theLeftChild),rightChild(theRightChild)
	{}
};