#pragma once

#include <iostream>
#include <stack>
#include "binaryTreeNode.h"
#include "indexedBSTree.h"

namespace dISTree {

	using std::cout;
	using std::endl;

	//�����ظ�������������������
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
		//�����������ӡ������нڵ�
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


		//�����Ҫ�޸�leftSize�Ľڵ�
		std::stack<dISTreeNode*> nodeStack;

		//�ҵ���ɾ���ڵ㼰�丸�ڵ�
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
		//û���ҵ���Ҫɾ���Ľڵ�
		if (!deleteNode)
			return;
		//�����ɾ���Ľڵ��������ӽڵ㣬����ת��Ϊ===��ɾ��ֻ��һ���ӽڵ�Ľڵ�
		if (deleteNode->leftChild && deleteNode->rightChild)
		{
			//�ñ�ɾ���ڵ�����������ڵ��滻��ǰ��Ҫɾ���Ľڵ�
			dISTreeNode
				* leftMaxNode = deleteNode->leftChild,
				* previousLeftMaxNode = deleteNode;
			while (leftMaxNode->rightChild)
			{
				previousLeftMaxNode = leftMaxNode;
				leftMaxNode = leftMaxNode->rightChild;
			}
			//�����滻deleteNode�Ľڵ�
			dISTreeNode
				* insteadOfNode = new dISTreeNode(leftMaxNode->element, deleteNode->leftChild, deleteNode->rightChild, deleteNode->leftSize - 1);
			//�滻�ɵĽڵ�
			if (!previousDeleteNode)
				root = insteadOfNode;
			else
			{
				if (deleteNode == previousDeleteNode->leftChild)
					previousDeleteNode->leftChild = insteadOfNode;
				else
					previousDeleteNode->rightChild = insteadOfNode;
			}
			//�޸�previousDeleteNode��deleteNodeָ��ΪleftMaxNode���丸�ڵ�
			if (previousLeftMaxNode == deleteNode)
				previousDeleteNode = insteadOfNode;
			else
				previousDeleteNode = previousLeftMaxNode;
			delete deleteNode;
			deleteNode = leftMaxNode;
		}

		//����ɾ���ڵ�ֻ��һ������û���ӽڵ�
		dISTreeNode
			* childNode;
		if (deleteNode->leftChild)
			childNode = deleteNode->leftChild;
		else
			childNode = deleteNode->rightChild;
		//���Ҫɾ���Ľڵ�Ϊroot�ڵ㣬
		if (deleteNode == root)
			root = childNode;
		else
		{
			if (deleteNode == previousDeleteNode->leftChild)
				previousDeleteNode->leftChild = childNode;
			else
				previousDeleteNode->rightChild = childNode;
		}
		//������ת�ڵ��leftSizeֵ
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

		//�����Ҫ�޸�leftSize�Ľڵ�
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
		//���root�ڵ�Ϊ��
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
		//������ת�ڵ��leftSizeֵ
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
		//ɾ���ڵ��������ӽڵ�
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
			//��������ڵ�
			dISTreeNode
				* insteadOfNode = new  dISTreeNode(leftMaxNode->element, deleteNode->leftChild, deleteNode->rightChild, deleteNode->leftSize - 1);
			if (!previousDeleteNode)
				root = insteadOfNode;
			else
				if (deleteNode == previousDeleteNode->leftChild)
					previousDeleteNode->leftChild = insteadOfNode;
				else
					previousDeleteNode->rightChild = insteadOfNode;
			//����previousDeleteNode��deleteNode
			if (previousLeftMaxNode == deleteNode)
				previousDeleteNode = insteadOfNode;
			else
				previousDeleteNode = previousLeftMaxNode;
			delete deleteNode;
			deleteNode = leftMaxNode;
		}
		//����ɾ���ڵ���һ������û���ӽڵ�
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



































