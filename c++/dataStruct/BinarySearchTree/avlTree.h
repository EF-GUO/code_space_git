#pragma once

#include "indexedBSTree.h"
#include "binaryTreeNode.h"

namespace avlTree
{
	template<typename K, typename E>
	class avlTree :public indexedBSTree<K, E>
	{
		using avlNode = binaryTreeNode<std::pair<const K, E>>;
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
		avlNode
			* root;
		int
			treeSize,
			bf;		//Æ½ºâÒò×Ó
		static void (*visit)(avlNode* theNode);
		//static private methods
		avlNode* rotate(avlNode* theNode);
		
		static void output(avlNode* theNode);
		static void inOrder(avlNode* theNode);
		static void postOrder(avlNode* theNode);
		static void deleteNode(avlNode* theNode);
	};
	void (*avlTree<int, int>::visit)(avlTree::avlNode* theNode);

	template<typename K, typename E>
	inline void avlTree<K, E>::insert(const std::pair<const K, E>& thePair)
	{
		//
	}

}





