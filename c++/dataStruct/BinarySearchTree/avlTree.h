#pragma once
#include <iostream>
#include <stdexcept>
#include <queue>
#include <stack>
#include "binaryTreeNode.h"
#include "binarySearchTree.h"


namespace avlTree
{
	using std::pair;

	template<typename K, typename E>
	class avlTree
	{
		using node = avlNode<std::pair<const K, E>>;
	public:
		avlTree();
		~avlTree();

		//insert
		void insert(const std::pair<const K, E>& thePair);

		//erase
		void erase(const K& theKey);

		//asc output
		void ascend();
		void levelOrder(void (*theVisit)(node* theNode) = output)
		{
			visit = theVisit;
			levelOrder(root);
		}

	private:
		node
			* root;
		int treeSize;
		//output node method
		static void output(node* theNode);
		static void (*visit)(node* theNode);
		static void destructorNode(node* theNode) { delete theNode; }

		//update the balance factor in [begin,end)
		static void updateBF(node* begin, node* end, const K& theKey);

		//rotate methods
		void LLrotate(node* PA, node* A, node* B);
		void RRrotate(node* PA, node* A, node* B);
		void LRrotate(node* PA, node* A, node* B);
		void RLrotate(node* PA, node* A, node* B);

		//Traversal methods
		static void preOrder(node* theNode);
		static void inOrder(node* theNode);
		static void postOrder(node* theNode);
		static void levelOrder(node* theNode);
	};
	void (*avlTree<int, int>::visit)(avlTree::node* theNode);

	template<typename K, typename E>
	inline avlTree<K, E>::avlTree()
		:root(nullptr), treeSize(0) {}

	template<typename K, typename E>
	inline avlTree<K, E>::~avlTree()
	{
		visit = destructorNode;
		postOrder(root);
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
			if (PA->leftChild == A)
				PA->leftChild = B;
			else
				PA->rightChild = B;
		}
		A->bf = B->bf = 0;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::RRrotate(node* PA, node* A, node* B)
	{
		// RR��
		// A�����ӽڵ�ΪB�����ӽڵ�
		A->rightChild = B->leftChild;
		// B�����ӽڵ�ΪA
		B->leftChild = A;

		// ���PAΪ��===>B��Ϊ�µ�root�ڵ�
		if (!PA)
			root = B;
		// ����,����PAָ��A��ָ����ΪB
		else
		{
			if (PA->leftChild == A)
				PA->leftChild = B;
			else
				PA->rightChild = B;
		}
		//����ƽ������
		A->bf = B->bf = 0;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::LRrotate(node* PA, node* A, node* B)
	{
		node* C = B->rightChild;
		B->rightChild = C->leftChild;
		A->leftChild = C->rightChild;
		C->leftChild = B;
		C->rightChild = A;

		if (!PA)
			root = C;
		else
		{
			if (PA->leftChild == A)
				PA->leftChild = C;
			else
				PA->rightChild = C;
		}
		//�޸Ľڵ��ƽ������
		int b = C->bf;

		if (b == 1)
		{
			B->bf = 0;
			A->bf = -1;
		}
		else if (b)	//b==-1
		{
			B->bf = 1;
			A->bf = 0;
		}
		else //b == 0
			A->bf = B->bf = 0;
		C->bf = 0;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::RLrotate(node* PA, node* A, node* B)
	{
		node* C = B->leftChild;

		A->rightChild = C->leftChild;
		B->leftChild = C->rightChild;

		C->leftChild = A;
		C->rightChild = B;


		//����PA
		if (PA)
		{
			if (A == PA->leftChild)
				PA->leftChild = C;
			else
				PA->rightChild = C;
		}
		else
			root = C;

		//�޸�ƽ������
		int b = C->bf;
		if (b == 1)
		{
			A->bf = 0;
			B->bf = -1;
		}
		else if (b)// b == -1
		{
			A->bf = 1;
			B->bf = 0;
		}
		else// b == 0
			A->bf = B->bf = 0;
		C->bf = 0;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::updateBF(node* begin, node* end, const K& theKey)
	{
		while (begin != end)
		{
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
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::insert(const std::pair<const K, E>& thePair)
	{
		node
			* currentNode = root,
			* previousNode = nullptr,
			* A = nullptr,
			* PA = nullptr;

		while (currentNode)
		{
			//���������ͬ�Ľڵ㣬�޸Ľڵ��ֵ������
			if (currentNode->element.first == thePair.first)
			{
				currentNode->element.second = thePair.second;
				return;
			}
			//ȷ���ڵ�A�Լ�A�ĸ��ڵ�====��A: ����·�������һ����Ϊ0�Ľڵ�
			if (currentNode->bf)
			{
				PA = previousNode;
				A = currentNode;
			}
			//���±���
			previousNode = currentNode;
			if (thePair.first < currentNode->element.first)
				currentNode = currentNode->leftChild;
			else
				currentNode = currentNode->rightChild;
		}
		node
			* newNode = new node(thePair);
		if (!root)
		{
			root = newNode;
			return;
		}
		else
		{
			if (thePair.first < previousNode->element.first)
				previousNode->leftChild = newNode;
			else
				previousNode->rightChild = newNode;
		}
		//���·���д���ƽ�����Ӳ�����0�Ľڵ�===��A����
		if (A)
		{
			if (A->bf > 0) // A == 1
			{
				if (thePair.first > A->element.first)
				{
					A->bf = 0;
					updateBF(A->rightChild, newNode, thePair.first);
				}
				else
				{
					node
						* B = A->leftChild;
					if (thePair.first < B->element.first) // LL��
					{
						updateBF(B->leftChild, newNode, thePair.first);
						LLrotate(PA, A, B);
					}
					else // LR��
					{
						updateBF(B->rightChild, newNode, thePair.first);
						LRrotate(PA, A, B);
					}
				}
			}
			else //A == -1
			{
				if (thePair.first < A->element.first)
				{
					A->bf = 0;
					updateBF(A->leftChild, newNode, thePair.first);
				}
				else
				{
					node
						* B = A->rightChild;
					if (thePair.first > B->element.first)// RR ��
					{
						updateBF(B->rightChild, newNode, thePair.first);
						RRrotate(PA, A, B);
					}
					else// RL ��
					{
						updateBF(B->leftChild, newNode, thePair.first);
						RLrotate(PA, A, B);
					}
				}
			}
		}
		//A�����ڣ�����·��[root,newNode)�����нڵ��ƽ������
		else
			updateBF(root, newNode, thePair.first);
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::erase(const K& theKey)
	{
		//hold path taken from root to physically deleted node
		std::stack<node*> pathStack;
		node
			* deleteNode = root;

		//�ҵ���Ҫɾ���Ľڵ�
		while (deleteNode && deleteNode->element.first != theKey)
		{
			pathStack.push(deleteNode);
			if (theKey < deleteNode->element.first)
				deleteNode = deleteNode->leftChild;
			else
				deleteNode = deleteNode->rightChild;
		}
		if (!deleteNode)
			throw std::logic_error("The node to be deleted was not found");
		
		//���Ҫɾ���Ľڵ������������ӽڵ�
		if (deleteNode->leftChild && deleteNode->rightChild)
		{
			pathStack.push(deleteNode);
			node
				* leftMaxNode = deleteNode->leftChild;
			while (leftMaxNode->rightChild)
			{
				pathStack.push(leftMaxNode);
				leftMaxNode = leftMaxNode->rightChild;
			}
			deleteNode->element = leftMaxNode->element;
			deleteNode = leftMaxNode;
		}

		//��ɾ���ڵ���¼��ڵ��ɾ���ڵ���ϼ��ڵ㽨������
		node
			* deleteNodeChild;
		if (deleteNode->leftChild)
			deleteNodeChild = deleteNode->leftChild;
		else
			deleteNodeChild = deleteNode->rightChild;

		if (deleteNode == root)
			root = deleteNodeChild;
		else
		{
			if (deleteNode == pathStack.top()->leftChild)
				pathStack.top()->leftChild = deleteNodeChild;
			else
				pathStack.top()->rightChild = deleteNodeChild;
		}
		std::pair<const K,E> deleteNodeElement = deleteNode->element;
		delete deleteNode;

		if (pathStack.empty())
			return;
		node
			* q = pathStack.top();
		pathStack.pop();
		
		while (q)
		{
			if (deleteNodeElement.first <= q->element.first)
			{
				//ɾ��������q�����
				q->bf--;
				
				//ɾ��֮ǰq->bf == 0����qΪ���������߶Ȳ��䣬ֻ��Ҫ�ı�q->bf
				if (q->bf == -1)
					return;
				//ɾ��֮ǰq->bf == -1����ʱ���ǲ�ƽ���
				else if (q->bf == -2)
				{

				}
				else //ɾ��֮��q->bf == 0��ɾ��֮ǰq->bf == 1����qΪ���������߶Ƚ���һ����λ����Ҫ�ı丸�ڵ��ƽ�����ӣ��п�����Ҫ�ı����Ƚڵ��
				{

				}

			}
			else
			{
				//ɾ��������q���ұ�
				q->bf++;

				if (q->bf == 1)
					return;

				else if (q->bf == 2)
				{
					node
						* B = q->leftChild,
						* PA;

					if (pathStack.empty())
						PA = 0;
					else
					{
						PA = pathStack.top();
						pathStack.pop();
					}

					switch (B->bf)
					{
					case 0:	//=====>RO��
						LLrotate(PA, q, B);
						B->bf = -1;
						q->bf = 1;
						return;
					case 1:	//=====>R1��
						LLrotate(PA, q, B);
						break;
					case -1:
						LRrotate(PA,)
					}

				}
				else //q->bf == 0
				{

				}

			}
		}

	}

	template<typename K, typename E>
	inline void avlTree<K, E>::preOrder(node* theNode)
	{
		if (theNode)
		{
			visit(theNode);
			preOrder(theNode->leftChild);
			preOrder(theNode->rightChild);
		}
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
	inline void avlTree<K, E>::output(node* theNode)
	{
		std::cout
			<< "KEY:\t" << theNode->element.first << "\t"
			<< "VALUE:\t" << theNode->element.second << std::endl;
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::ascend()
	{
		visit = output;
		inOrder(root);
	}

	template<typename K, typename E>
	inline void avlTree<K, E>::levelOrder(node* theNode)
	{
		std::queue<node*> theQueue;


		while (theNode)
		{
			visit(theNode);
			if (theNode->leftChild)
				theQueue.push(theNode->leftChild);
			if (theNode->rightChild)
				theQueue.push(theNode->rightChild);

			if (!theQueue.empty())
			{
				theNode = theQueue.front();
				theQueue.pop();
			}
			else
				theNode = nullptr;
		}
	}

}






















