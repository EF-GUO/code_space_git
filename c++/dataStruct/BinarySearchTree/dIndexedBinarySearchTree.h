#pragma once

#include <iostream>
#include <stack>
#include "binaryTreeNode.h"
#include "indexedBSTree.h"

namespace dISTree {

	using std::cout;
	using std::endl;

	//带有重复键的索引二叉搜索树
	template<typename K, typename E>
	class dIndexedBinarySearchTree :public indexedBSTree<K, E>
	{
		using dISTreeNode = indexedBinarySearchTreeNode < std::pair < const K, E>>;
	public:
		dIndexedBinarySearchTree();
		~dIndexedBinarySearchTree();
		//ADT methods
		bool empty() const;
		int size() const;
		std::pair<const K, E>* find(const K& theKey) const;
		void erase(const K& theKey);
		void insert(const std::pair<const K, E>& thePair);
		//升序遍历并打印输出所有节点
		void ascend();
		std::pair<const K, E>* get(const int theIndex) const;
		void deleteByIndex(const int theIndex);

	private:
		dISTreeNode* root;
		int treeSize;
		static void (*visit)(dISTreeNode* theNode);
		//static method
		static void output(dISTreeNode* theNode);
		static void inOrder(dISTreeNode* theNode);
		static void postOrder(dISTreeNode* theNode);
		static void deleteNode(dISTreeNode* theNode);

	};
	void(*dIndexedBinarySearchTree<int, int>::visit)(indexedBinarySearchTreeNode < std::pair < const int, int>>*);

	template<typename K, typename E>
	inline dIndexedBinarySearchTree<K, E>::dIndexedBinarySearchTree()
		:root(nullptr), treeSize(0) {}

	template<typename K, typename E>
	inline dIndexedBinarySearchTree<K, E>::~dIndexedBinarySearchTree()
	{
		visit = deleteNode;
		postOrder(root);
	}

	template<typename K, typename E>
	inline bool dIndexedBinarySearchTree<K, E>::empty() const
	{
		return treeSize == 0;
	}

	template<typename K, typename E>
	inline int dIndexedBinarySearchTree<K, E>::size() const
	{
		return treeSize;
	}

	template<typename K, typename E>
	inline std::pair<const K, E>* dIndexedBinarySearchTree<K, E>::find(const K& theKey) const
	{
		if (!root)
			return nullptr;
		dISTreeNode* currentNode = root;

		while (currentNode)
		{
			if (currentNode->element.first == theKey)
				return &currentNode->element;

			if (theKey < currentNode->element.first)
				currentNode = currentNode->leftChild;
			else
				currentNode = currentNode->rightChild;
		}
		return nullptr;
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::erase(const K& theKey)
	{

		dISTreeNode
			* deleteNode = root,
			* previousDeleteNode = nullptr;


		//存放需要修改leftSize的节点
		std::stack<dISTreeNode*> nodeStack;

		//找到被删除节点及其父节点
		while (deleteNode && deleteNode->element.first != theKey)
		{
			previousDeleteNode = deleteNode;
			if (theKey < deleteNode->element.first)
			{
				deleteNode = deleteNode->leftChild;
				nodeStack.push(deleteNode);
			}
			else
				deleteNode = deleteNode->rightChild;
		}
		//没有找到需要删除的节点
		if (!deleteNode)
			return;
		//如果被删除的节点有两个子节点，将其转换为===》删除只有一个子节点的节点
		if (deleteNode->leftChild && deleteNode->rightChild)
		{
			//用被删除节点的左子树最大节点替换当前需要删除的节点
			dISTreeNode
				* leftMaxNode = deleteNode->leftChild,
				* previousLeftMaxNode = deleteNode;
			while (leftMaxNode->rightChild)
			{
				previousLeftMaxNode = leftMaxNode;
				leftMaxNode = leftMaxNode->rightChild;
			}
			//创建替换deleteNode的节点
			dISTreeNode
				* insteadOfNode = new dISTreeNode(leftMaxNode->element, deleteNode->leftChild, deleteNode->rightChild, deleteNode->leftSize - 1);
			//替换旧的节点
			if (!previousDeleteNode)
				root = insteadOfNode;
			else
			{
				if (deleteNode == previousDeleteNode->leftChild)
					previousDeleteNode->leftChild = insteadOfNode;
				else
					previousDeleteNode->rightChild = insteadOfNode;
			}
			//修改previousDeleteNode和deleteNode指向为leftMaxNode及其父节点
			if (previousLeftMaxNode == deleteNode)
				previousDeleteNode = insteadOfNode;
			else
				previousDeleteNode = previousLeftMaxNode;
			delete deleteNode;
			deleteNode = leftMaxNode;
		}

		//处理删除节点只有一个或者没有子节点
		dISTreeNode
			* childNode;
		if (deleteNode->leftChild)
			childNode = deleteNode->leftChild;
		else
			childNode = deleteNode->rightChild;
		//如果要删除的节点为root节点，
		if (deleteNode == root)
			root = childNode;
		else
		{
			if (deleteNode == previousDeleteNode->leftChild)
				previousDeleteNode->leftChild = childNode;
			else
				previousDeleteNode->rightChild = childNode;
		}
		//更新左转节点的leftSize值
		while (!nodeStack.empty())
		{
			nodeStack.top()->leftSize--;
			nodeStack.pop();
		}
		delete deleteNode;
		--treeSize;
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair)
	{
		dISTreeNode
			* currentNode = root,
			* previousCurrentNode = nullptr,
			* insertNode = new dISTreeNode(thePair);

		//存放需要修改leftSize的节点
		std::stack<dISTreeNode*> nodeStack;

		while (currentNode)
		{
			previousCurrentNode = currentNode;
			if (thePair.first <= currentNode->element.first)
			{
				nodeStack.push(currentNode);
				currentNode = currentNode->leftChild;
			}
			else
				currentNode = currentNode->rightChild;
		}
		//如果root节点为空
		if (!root)
		{
			root = insertNode;
			treeSize++;
			return;
		}

		if (thePair.first <= previousCurrentNode->element.first)
			previousCurrentNode->leftChild = insertNode;
		else
			previousCurrentNode->rightChild = insertNode;
		//更新左转节点的leftSize值
		while (!nodeStack.empty())
		{
			nodeStack.top()->leftSize++;
			nodeStack.pop();
		}

		treeSize++;
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::ascend()
	{
		visit = output;
		inOrder(root);
	}

	template<typename K, typename E>
	inline std::pair<const K, E>* dIndexedBinarySearchTree<K, E>::get(const int theIndex) const
	{
		//checkIndex
		if (theIndex < 0 || theIndex >= treeSize)
			throw std::logic_error("index error");
		dISTreeNode
			* currentNode = root;
		int currentIndex = currentNode->leftSize;
		while (currentNode)
		{
			if (theIndex == currentIndex)
				return &currentNode->element;
			if (theIndex < currentIndex)
			{
				currentIndex = currentIndex - (currentNode->leftSize - currentNode->leftChild->leftSize);
				currentNode = currentNode->leftChild;
			}
			else
			{
				currentIndex = currentIndex + currentNode->rightChild->leftSize + 1;
				currentNode = currentNode->rightChild;
			}
		}

		return nullptr;
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::deleteByIndex(const int theIndex)
	{
		//checkIndex
		if (theIndex < 0 || theIndex >= treeSize)
			throw std::logic_error("index error");
		dISTreeNode
			* deleteNode = root,
			* previousDeleteNode = nullptr;
		std::stack<dISTreeNode*> nodeStack;
		int currentIndex = root->leftSize;
		while (deleteNode && theIndex != currentIndex)
		{
			previousDeleteNode = deleteNode;
			if (theIndex < currentIndex)
			{
				nodeStack.push(deleteNode);
				currentIndex = currentIndex - (deleteNode->leftSize - deleteNode->leftChild->leftSize);
				deleteNode = deleteNode->leftChild;
			}
			else
			{
				currentIndex = currentIndex + deleteNode->rightChild->leftSize + 1;
				deleteNode = deleteNode->rightChild;
			}
		}
		if (!deleteNode) return;
		//删除节点有两个子节点
		if (deleteNode->leftChild && deleteNode->rightChild)
		{
			dISTreeNode
				* leftMaxNode = deleteNode->leftChild,
				* previousLeftMaxNode = deleteNode;

			while (leftMaxNode->rightChild)
			{
				previousLeftMaxNode = leftMaxNode;
				leftMaxNode = leftMaxNode->rightChild;
			}
			//建立代替节点
			dISTreeNode
				* insteadOfNode = new  dISTreeNode(leftMaxNode->element, deleteNode->leftChild, deleteNode->rightChild, deleteNode->leftSize - 1);
			if (!previousDeleteNode)
				root = insteadOfNode;
			else
				if (deleteNode == previousDeleteNode->leftChild)
					previousDeleteNode->leftChild = insteadOfNode;
				else
					previousDeleteNode->rightChild = insteadOfNode;
			//更改previousDeleteNode和deleteNode
			if (previousLeftMaxNode == deleteNode)
				previousDeleteNode = insteadOfNode;
			else
				previousDeleteNode = previousLeftMaxNode;
			delete deleteNode;
			deleteNode = leftMaxNode;
		}
		//处理删除节点有一个或者没有子节点
		dISTreeNode
			* childNode;
		if (deleteNode->leftChild)
			childNode = deleteNode->leftChild;
		else
			childNode = deleteNode->rightChild;
		
		if (deleteNode == root)
			root = childNode;
		else
		{
			if (deleteNode == previousDeleteNode->leftChild)
				previousDeleteNode->leftChild = childNode;
			else
				previousDeleteNode->rightChild = childNode;
		}
		while (!nodeStack.empty())
		{
			nodeStack.top()->leftSize--;
			nodeStack.pop();
		}
		delete deleteNode;
		--treeSize;
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::output(dISTreeNode* theNode)
	{
		cout << "KEY: " << theNode->element.first << "\t" << "VALUE: " << theNode->element.second << endl;
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::inOrder(dISTreeNode* theNode)
	{
		if (theNode)
		{
			inOrder(theNode->leftChild);
			visit(theNode);
			inOrder(theNode->rightChild);
		}
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::postOrder(dISTreeNode* theNode)
	{
		if (theNode)
		{
			postOrder(theNode->leftChild);
			postOrder(theNode->rightChild);
			visit(theNode);
		}
	}

	template<typename K, typename E>
	inline void dIndexedBinarySearchTree<K, E>::deleteNode(dISTreeNode* theNode)
	{
		delete theNode;
	}

}



































