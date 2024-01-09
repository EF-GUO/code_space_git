#pragma once

#include "binaryTree.h"
#include "node.h"


template<typename T>
class linkedBinaryTree
{
	using Node = nodeSet::binaryTreeNode<T>;
public:
	linkedBinaryTree()
		:
		root(nullptr),
		treeSize(0) {}

	~linkedBinaryTree();
	virtual bool empty() const;
	virtual int size() const;
	virtual const nodeSet::binaryTreeNode<T>const* getRoot() const
	{
		return root;
	}
	virtual void makeTree(
		const T& theElement,
		linkedBinaryTree<T>& leftSubTree,
		linkedBinaryTree<T>& rightSubTree
	);

	virtual void preOrder(void (*theVisit) (Node*) = output);
	virtual void inOrder(void (*theVisit) (Node*) = output);
	virtual void postOrder(void (*theVisit) (Node*) = output);
	virtual void levelOrder(void (*theVisit) (Node*) = output);

	template<typename T>
	friend linkedBinaryTree<int>* getHuffmanTree(std::vector<int>& weight, int n);

private:
	Node
		* root;
	int
		treeSize;

	static void (*visit)(Node* node);

	static void preOrder(Node* node);
	static void inOrder(Node* node);
	static void postOrder(Node* node);
	static void levelOrder(Node* node);

	static void deleteNode(Node* node);
	static void output(Node* node);
};

void (*linkedBinaryTree<int>::visit)(linkedBinaryTree::Node* node);


template<typename T>
inline linkedBinaryTree<T>::~linkedBinaryTree()
{
	visit = deleteNode;
	postOrder(root);
}

template<typename T>
inline bool linkedBinaryTree<T>::empty() const
{
	return false;
}

template<typename T>
inline int linkedBinaryTree<T>::size() const
{
	return 0;
}

template<typename T>
inline void linkedBinaryTree<T>::makeTree(const T& theElement, linkedBinaryTree<T>& leftSubTree, linkedBinaryTree<T>& rightSubTree)
{
	root = new nodeSet::binaryTreeNode<T>(theElement, leftSubTree.root, rightSubTree.root);
	treeSize = leftSubTree.treeSize + rightSubTree.treeSize + 1;

	leftSubTree.root = rightSubTree.root = nullptr;
	leftSubTree.treeSize = rightSubTree.treeSize = 0;
}

template<typename T>
inline void linkedBinaryTree<T>::preOrder(void(*theVisit)(Node*))
{
	visit = theVisit;
	preOrder(root);
}

template<typename T>
inline void linkedBinaryTree<T>::inOrder(void(*theVisit)(Node*))
{
	visit = theVisit;
	inOrder(root);
}

template<typename T>
inline void linkedBinaryTree<T>::postOrder(void(*theVisit)(Node*))
{
	visit = theVisit;
	postOrder(root);
}

template<typename T>
inline void linkedBinaryTree<T>::levelOrder(void(*theVisit)(Node*))
{
	visit = theVisit;
	levelOrder(root);
}

template<typename T>
inline void linkedBinaryTree<T>::preOrder(Node* node)
{
	if (node)
	{
		visit(node);
		preOrder(node->leftChild);
		preOrder(node->rightChild);
	}
}

template<typename T>
inline void linkedBinaryTree<T>::inOrder(Node* node)
{
	if (node)
	{
		inOrder(node->leftChild);
		visit(node);
		inOrder(node->rightChild);
	}
}

template<typename T>
inline void linkedBinaryTree<T>::postOrder(Node* node)
{
	if (node)
	{
		postOrder(node->leftChild);
		postOrder(node->rightChild);
		visit(node);
	}
}

template<typename T>
inline void linkedBinaryTree<T>::levelOrder(Node* node)
{

}

template<typename T>
inline void linkedBinaryTree<T>::deleteNode(Node* node)
{
	delete node;
}

template<typename T>
inline void linkedBinaryTree<T>::output(Node* node)
{
	if (node)
		std::cout << node->element << " ";
}
