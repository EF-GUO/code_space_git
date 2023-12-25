#pragma once

#include <stack>
#include "indexedBSTree.h"
#include "binaryTreeNode.h"

namespace avlTree
{

	using std::stack;

	template<typename K, typename E>
	class avlTree :public indexedBSTree<K, E>
	{
		using node = avlNode<std::pair<const K, E>>;
	public:
		avlTree();
		~avlTree();

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
		node
			* root;
		int
			treeSize;

		static void (*visit)(node* theNode);

		//static private methods
		static void output(node* theNode);
		static void inOrder(node* theNode);
		static void postOrder(node* theNode);
		static void deleteNode(node* theNode);

		static void updateBF(node* begin, node* end, const K& theKey);

		//rotate methods
		static void LLrotate(node* PA, node* A, node* B);//LL型旋转（右旋）
		static void RRrotate(node* PA, node* A, node* B);//RR型旋转（左旋）
		static void LRrotate(node* PA, node* A, node* B);//LR型旋转(先右旋再左旋)
		//static node* RLrotate();

	};
	void (*avlTree<int, int>::visit)(avlTree::node* theNode);


	template<typename K, typename E>
	inline avlTree<K, E>::avlTree()
		:root(nullptr), treeSize(0) {}

	template<typename K, typename E>
	inline avlTree<K, E>::~avlTree()
	{
		visit = deleteNode;
		postOrder(root);
	}

	template<typename K, typename E>
	inline bool avlTree<K, E>::empty() const
	{
		return treeSize == 0;
	}

	template<typename K, typename E>
	inline int avlTree<K, E>::size() const
	{
		return treeSize;
	}

	template<typename K, typename E>
	inline std::pair<const K, E>* avlTree<K, E>::find(const K& theKey) const
	{
		return nullptr;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::erase(const K& theKey)
	{

	}

	template<typename K, typename E>
	inline void avlTree<K, E>::insert(const std::pair<const K, E>& thePair)
	{
		node
			* currentNode = root,
			* previousCurrentNode = nullptr,
			* A = nullptr，
			* previousA;

		while (currentNode)
		{
			//存在相同关键字的节点,修改值并返回
			if (currentNode->element.first != thePair.first)
			{
				currentNode->element.second = thePair.second;
				return;
			}

			if (currentNode->bf == 1 || currentNode->bf == -1)
				flagNode = currentNode;

			previousCurrentNode = currentNode;
			if (thePair.first < currentNode->element.first)
				currentNode = currentNode->leftChild;
			else
				currentNode = currentNode->rightChild;
		}

		node* newNode = node(thePair);

		if (!root)
			root = newNode;
		else
		{
			if (thePair.first < previousCurrentNode->element.first)
				previousCurrentNode->leftChild = newNode;
			else
				previousCurrentNode->rightChild = newNode;
		}


		if (A)//如果路径中存在平衡因子不等于0的节点
		{
			if (A->bf < 0)// A->bf == -1，节点A的左子树的高度低于其右子树的高度
			{
				//如果是在A节点的左子树插入新节点，左子树高度+1，A->bf = 0
				//此时以A节点为根的子树高度不变，不需要修改[root,A)的节点的平衡因子
				if (thePair.first < A->element.first)
				{
					//A->bf == 0
					//修改路径(A,newNode)中节点的平衡因子
					//return;
				}
				//在A的右子树插入新节点
				else
				{

				}
			}
			else//A->bf == 1,节点A的左子树的高度高于其右子树的高度
			{
				//如果是在A节点的右子树插入新节点，右子树高度+1，A->bf = 0
				//此时以A节点为根的子树高度不变，不需要修改[root,A)的节点的平衡因子
				if (thePair.first < A->element.first)
				{
					//A->bf == 0
					//修改路径(A,newNode)中节点的平衡因子
					//return;
				}
				//在A的左子树插入新的节点
				else
				{

				}
			}
		}
		else//节点A不存在,修改路径上所有节点的平衡因子
		{

		}


	}

	template<typename K, typename E>
	inline void avlTree<K, E>::ascend()
	{
		visit = output;
		inOrder(root);
	}

	template<typename K, typename E>
	inline std::pair<const K, E>* avlTree<K, E>::get(const int theIndex) const
	{
		return nullptr;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::deleteByIndex(const int theIndex)
	{
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::output(node* theNode)
	{
		std::cout
			<< "KEY: " << theNode->element.first << "\t"
			<< "VALUE: " << theNode->element.second
			<< std::endl;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::inOrder(node* theNode)
	{
		if (theNode)
		{
			inOrder(theNode->leftChild);
			visit(theNode);
			inOrder(theNode->rightChild);
		}
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::postOrder(node* theNode)
	{
		if (theNode)
		{
			postOrder(theNode->leftChild);
			postOrder(theNode->rightChild);
			visit(theNode);
		}
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::deleteNode(node* theNode)
	{
		delete theNode;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::updateBF(node* begin, node* end, const K& theKey)
	{
		//更新路径平衡因子
		//更新从begin节点到end节点的路径====>[begin,end)
		while (begin != end)
			if (theKey < begin->element.first)
			{
				begin->bf = 1;
				begin = begin->leftChild;
			}
			else
			{
				begin->bf = -1;
				begin = begin->rightChild;
			}
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::LLrotate(node* PA, node* A, node* B)
	{
		A->leftChild = B->rightChild;
		B->rightChild = A;

		if (!PA)
			root = B;
		else
		{
			if (A == PA->rightChild)
				PA->leftChild = B;
			else
				PA->rightChild = B;
		}

		A->bf = B->bf = 0;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::RRrotate(node* PA, node* A, node* B)
	{
		B->leftChild = A;
		A->rightChild = B->leftChild;
		if (!PA)
			root = B;
		else
		{
			if (A = PA->leftChild)
				PA->leftChild = B;
			else
				PA->rightChild = B;
		}

		A->bf = B->bf = 0;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::LRrotate(node* PA, node* A, node* B)
	{



	}

}





