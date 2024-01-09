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
		// RR型
		// A的右子节点为B的左子节点
		A->rightChild = B->leftChild;
		// B的左子节点为A
		B->leftChild = A;

		// 如果PA为空===>B就为新的root节点
		if (!PA)
			root = B;
		// 否则,更改PA指向A的指针域为B
		else
		{
			if (PA->leftChild == A)
				PA->leftChild = B;
			else
				PA->rightChild = B;
		}
		//更改平衡因子
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
		//修改节点的平衡因子
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


		//更改PA
		if (PA)
		{
			if (A == PA->leftChild)
				PA->leftChild = C;
			else
				PA->rightChild = C;
		}
		else
			root = C;

		//修改平衡因子
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
			//如果存在相同的节点，修改节点的值并结束
			if (currentNode->element.first == thePair.first)
			{
				currentNode->element.second = thePair.second;
				return;
			}
			//确定节点A以及A的父节点====》A: 插入路径中最后一个不为0的节点
			if (currentNode->bf)
			{
				PA = previousNode;
				A = currentNode;
			}
			//向下遍历
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
		//如果路径中存在平衡因子不等于0的节点===》A存在
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
					if (thePair.first < B->element.first) // LL型
					{
						updateBF(B->leftChild, newNode, thePair.first);
						LLrotate(PA, A, B);
					}
					else // LR型
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
					if (thePair.first > B->element.first)// RR 型
					{
						updateBF(B->rightChild, newNode, thePair.first);
						RRrotate(PA, A, B);
					}
					else// RL 型
					{
						updateBF(B->leftChild, newNode, thePair.first);
						RLrotate(PA, A, B);
					}
				}
			}
		}
		//A不存在，更新路径[root,newNode)上所有节点的平衡因子
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

		//找到需要删除的节点
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
		
		//如果要删除的节点有左右两个子节点
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

		//将删除节点的下级节点和删除节点的上级节点建立连接
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
				//删除发生在q的左边
				q->bf--;
				
				//删除之前q->bf == 0，以q为根的子树高度不变，只需要改变q->bf
				if (q->bf == -1)
					return;
				//删除之前q->bf == -1，此时树是不平衡的
				else if (q->bf == -2)
				{

				}
				else //删除之后q->bf == 0，删除之前q->bf == 1，以q为根的子树高度降低一个单位，需要改变父节点的平衡因子，有可以需要改变祖先节点的
				{

				}

			}
			else
			{
				//删除发生在q的右边
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
					case 0:	//=====>RO型
						LLrotate(PA, q, B);
						B->bf = -1;
						q->bf = 1;
						return;
					case 1:	//=====>R1型
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






















