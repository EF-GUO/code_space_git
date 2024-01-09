#pragma once
#include "linkedBinaryTree.h"
template<typename T>
class linkedBinaryTree;

namespace nodeSet
{
	template<typename T>
	struct binaryTreeNode
	{
		T element;
		binaryTreeNode<T>
			* leftChild,
			* rightChild;

		binaryTreeNode()
			:
			element(), leftChild(nullptr), rightChild(nullptr) {};

		binaryTreeNode(const T& theElement)
			:
			element(theElement), leftChild(nullptr), rightChild(nullptr) {};

		binaryTreeNode(
			const T& theElement,
			binaryTreeNode<T>* theLeftChild,
			binaryTreeNode<T>* theRightChild
		)
			:
			element(theElement),
			leftChild(theLeftChild),
			rightChild(theRightChild) {};
	};

	template<typename T>
	struct huffmanNode
	{
		linkedBinaryTree<int>* tree;
		T weight;
		operator T()const { return weight; }
	};

}