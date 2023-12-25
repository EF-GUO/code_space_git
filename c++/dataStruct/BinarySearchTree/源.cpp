//#include <iostream>
//
//#include "binarySearchTree.h"
//#include "indexedBinarySearchTree.h"
//#include "dIndexedBinarySearchTree.h"
//
//int main()
//{
//	using namespace std;
//	using DISTree = dISTree::dIndexedBinarySearchTree<int, int>;
//
//	DISTree* demo = new DISTree;
//
//	demo->insert(make_pair(15, 0));
//	demo->insert(make_pair(8, 0));
//	demo->insert(make_pair(22, 0));
//	demo->insert(make_pair(4, 0));
//	demo->insert(make_pair(12, 0));
//	demo->insert(make_pair(26, 0));
//	demo->insert(make_pair(2, 0));
//	demo->insert(make_pair(6, 0));
//	demo->insert(make_pair(10, 911));
//	demo->insert(make_pair(13, 0));
//
//	demo->ascend();
//	cout << endl << endl;
//
//	demo->deleteByIndex(8);
//
//	demo->ascend();
//	cout << endl << endl;
//
//	demo->insert(make_pair(2, 0));
//	demo->insert(make_pair(6, 0));
//	demo->insert(make_pair(10, 911));
//	demo->insert(make_pair(13, 0));
//
//	demo->ascend();
//	cout << endl << endl;
//
//	cout << demo->get(3)->first << "  " << demo->get(3)->second << endl;
//
//	delete demo;
//}
//
//
//





template<class E, class K>
AVLtree<E, K>& AVLtree<E, K>::Insert(const E& e)
{
	AVLNode<E, K>* p = root,
		* pp = 0,
		* A = 0,
		* PA;

	while (p) 
	{
		if (p->bf) 
		{
			A = p;
			PA = pp;
		}
		pp = p;

		if (e < p->data) 
			p = p->LeftChild;
		else if (e > p->data)
			p = p->RightChild;
		else 
			throw BadInput();
	}

	AVLNode<E, K>* r = new AVLNode<E, K>(e);
	if (root) 
	{
		if (e < pp->data) 
			pp->LeftChild = r;
		else 
			pp->RightChild = r;
	}
	else 
	{
		root = r;
		return *this;
	}


	if (A)
		if (A->bf < 0)
			if (e < A->data) 
			{
				A->bf = 0;
				FixBF(A->LeftChild, r, e);
			}
			else 
			{
				AVLNode<E, K>* B = A->RightChild;
				if (e > B->data) 
				{
					FixBF(B->RightChild, r, e);
					RRrotate(PA, A, B);
				}
				else 
				{
					FixBF(B->LeftChild, r, e);
					RLrotate(PA, A, B);
				}
			}
		else
			if (e > A->data) 
			{
				A->bf = 0;
				FixBF(A->RightChild, r, e);
			}
			else {

				AVLNode<E, K>* B = A->LeftChild;
				if (e < B->data) {
					FixBF(B->LeftChild, r, e);
					LLrotate(PA, A, B);
				}
				else {
					FixBF(B->RightChild, r, e);
					LRrotate(PA, A, B);
				}
			}
	else
		FixBF(root, r, e);

	return *this;
}
