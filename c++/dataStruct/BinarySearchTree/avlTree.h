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
		static void LLrotate(node* PA, node* A, node* B);//LL����ת��������
		static void RRrotate(node* PA, node* A, node* B);//RR����ת��������
		static void LRrotate(node* PA, node* A, node* B);//LR����ת(������������)
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
			* A = nullptr��
			* previousA;

		while (currentNode)
		{
			//������ͬ�ؼ��ֵĽڵ�,�޸�ֵ������
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


		if (A)//���·���д���ƽ�����Ӳ�����0�Ľڵ�
		{
			if (A->bf < 0)// A->bf == -1���ڵ�A���������ĸ߶ȵ������������ĸ߶�
			{
				//�������A�ڵ�������������½ڵ㣬�������߶�+1��A->bf = 0
				//��ʱ��A�ڵ�Ϊ���������߶Ȳ��䣬����Ҫ�޸�[root,A)�Ľڵ��ƽ������
				if (thePair.first < A->element.first)
				{
					//A->bf == 0
					//�޸�·��(A,newNode)�нڵ��ƽ������
					//return;
				}
				//��A�������������½ڵ�
				else
				{

				}
			}
			else//A->bf == 1,�ڵ�A���������ĸ߶ȸ������������ĸ߶�
			{
				//�������A�ڵ�������������½ڵ㣬�������߶�+1��A->bf = 0
				//��ʱ��A�ڵ�Ϊ���������߶Ȳ��䣬����Ҫ�޸�[root,A)�Ľڵ��ƽ������
				if (thePair.first < A->element.first)
				{
					//A->bf == 0
					//�޸�·��(A,newNode)�нڵ��ƽ������
					//return;
				}
				//��A�������������µĽڵ�
				else
				{

				}
			}
		}
		else//�ڵ�A������,�޸�·�������нڵ��ƽ������
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
		//����·��ƽ������
		//���´�begin�ڵ㵽end�ڵ��·��====>[begin,end)
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





