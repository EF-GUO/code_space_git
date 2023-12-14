#pragma once


#include "binaryTreeNode.h"
#include "linkedBinaryTree.h"

template<typename T>
class maxHblt :public linkedBinaryTree<T>
{
public:
	maxHblt() = default;

		//�ϲ�
	void meld(maxHblt<T>& theHblt);
private:
	void meld(binaryTreeNode<std::pair<int, T>>*& x, binaryTreeNode < std::pair<int, T>*& y);


};


