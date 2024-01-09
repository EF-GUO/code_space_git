#pragma once
#include "minHeap.h"
#include "linkedBinaryTree.h"
#include "node.h"

template<typename T>
linkedBinaryTree<int>* getHuffmanTree(std::vector<int>& weight, int n)
{
	nodeSet::huffmanNode<T>* hNodeList = new nodeSet::huffmanNode<T>[n + 1];
	for (int i = 1; i <= n; i++)
	{
		//hNodeList[i].weight = weight[i - 1];
		hNodeList[i].weight = weight.at(i-1);
		hNodeList[i].tree = new linkedBinaryTree<int>;
		hNodeList[i].tree->root = new nodeSet::binaryTreeNode<int>(i);
	}

	heap::minHeap<nodeSet::huffmanNode<T>> heap;
	heap.Initialize(hNodeList, n, n + 1);

	//	  x��y����ǰȨֵ��С������huffmanTreeNode
	//	merged���ϲ���Ľ��
	//		 z����������������ϲ���Ķ�����	
	nodeSet::huffmanNode<T> x, y, merged;
	linkedBinaryTree<int>* z;
	for (int i = 1; i < n; i++)
	{
		x = heap.top(); heap.pop();
		y = heap.top(); heap.pop();

		z = new linkedBinaryTree<int>;
		z->makeTree(0, *x.tree, *y.tree);

		merged.weight = x.weight + y.weight;
		merged.tree = z;

		heap.push(merged);
		delete x.tree;
		delete y.tree;
	}

	return heap.top().tree;
}






























