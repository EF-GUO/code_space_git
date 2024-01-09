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


#include <iostream>
#include "avlTree.h"


int main()
{
	using namespace std;
	using avlTree::avlTree;

	avlTree<int, int>* demo = new avlTree<int, int>;

	for (size_t i = 1; i <= 15; i++)
		demo->insert(make_pair(i, 0));

	demo->ascend();

	cout << endl << endl << endl;

	demo->levelOrder();
	delete demo;

}




























