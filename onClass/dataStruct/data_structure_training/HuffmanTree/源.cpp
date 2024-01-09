//#include <iostream>
//#include <cctype>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <map>
//#include "minHeap.h"
//#include "huffmanTree.h"
//
//void getHuffmanCode(
//	const nodeSet::binaryTreeNode<int>* const node,
//	char* unique_str,
//	std::map<char, std::string>& mapping,
//	std::string str = ""
//);
//
////void getHuffmanCode(nodeSet::binaryTreeNode<int>* node, char* str_unique, std::map<char, std::vector<bool>>& mapping, std::vector<bool> code = std::vector<bool>());
//
//
//std::string coding(std::map<char, std::string>& mapping, std::string& str);
//std::string decoding(const linkedBinaryTree<int>* const hfTree, const char* const str_unique, std::string str);
//
//int main()
//{
//	using namespace std;
//
//	string str;
//	cout << "Enter the string: ";
//	getline(cin, str);
//
//	vector<int>* str_count = new vector<int>{};
//	vector<char>* str_unique = new vector<char>;
//	int unique_size = 0;
//
//	for (int i = 0; i < str.size(); i++)
//	{
//		bool flag = false;
//		for (int j = 0; j < unique_size; j++)
//		{
//			if (str[i] == str_unique->at(j))
//			{
//				flag = true;
//				str_count->at(j)++;
//				break;
//			}
//		}
//		if (!flag)
//		{
//			str_unique->at(unique_size) = str[i];
//			str_count->at(unique_size++)++;
//		}
//	}
//
//	cout << "字符出现的次数" << endl;
//	for (int i = 0; i < unique_size; i++)
//		cout << str_unique->at(i) << ": " << str_count->at(i) << endl;
//
//	linkedBinaryTree<int>* hfTree = getHuffmanTree<int>(str_count, unique_size);
//
//	map<char, string> mapping;
//
//	getHuffmanCode(hfTree->getRoot(), str_unique, mapping);
//
//	cout << "字符对应的Huffman编码" << endl;
//	for (auto ele : mapping)
//		cout << ele.first << " : " << ele.second << endl;
//
//	cout << endl;
//
//	cout << "字符串\" " << str << "  \"转换为huffman编码为" << endl;
//
//	cout << coding(mapping, str) << endl;
//
//	cout << "对其解码结果为: " << endl;
//	cout << decoding(hfTree, str_unique, coding(mapping, str)) << endl;
//
//	delete hfTree;
//}
//
//
////输入原始字符串并返回构建的霍夫曼树
//linkedBinaryTree<int>* initializeHfTree(int* str_count, char* str_unique, int& size)
//{
//	using namespace std;
//
//	string str;
//	cout << "Enter the string: ";
//	getline(cin, str);
//
//	str_count = new int[str.size()] {};
//	str_unique = new char[str.size()];
//	int unique_size = 0;
//
//	for (int i = 0; i < str.size(); i++)
//	{
//		bool flag = false;
//		for (int j = 0; j < unique_size; j++)
//		{
//			if (str[i] == str_unique[j])
//			{
//				flag = true;
//				str_count[j]++;
//				break;
//			}
//		}
//		if (!flag)
//		{
//			str_unique[unique_size] = str[i];
//			str_count[unique_size++]++;
//		}
//	}
//
//	cout << "字符出现的次数" << endl;
//	for (int i = 0; i < unique_size; i++)
//		cout << str_unique[i] << ": " << str_count[i] << endl;
//
//	linkedBinaryTree<int>* hfTree = getHuffmanTree<int>(str_count, unique_size);
//
//	map<char, string> mapping;
//
//	getHuffmanCode(hfTree->getRoot(), str_unique, mapping);
//
//	cout << "字符对应的Huffman编码" << endl;
//	for (auto ele : mapping)
//		cout << ele.first << " : " << ele.second << endl;
//
//	cout << endl;
//}
//
//
//
////得到对应编码函数
//void getHuffmanCode(
//	const nodeSet::binaryTreeNode<int>* const node,
//	char* str_unique,
//	std::map<char, std::string>& mapping,
//	std::string str)
//{
//	if (!node->leftChild && !node->rightChild)
//		mapping[str_unique[node->element - 1]] = str;
//	else
//	{
//		getHuffmanCode(node->leftChild, str_unique, mapping, str + '0');
//		getHuffmanCode(node->rightChild, str_unique, mapping, str + '1');
//	}
//}
//
////编码
//std::string coding(std::map<char, std::string>& mapping, std::string& str)
//{
//	std::string result;
//
//	for (auto ele : str)
//		result += mapping[ele];
//	return result;
//}
//
//
////解码
//std::string decoding(const linkedBinaryTree<int>* const hfTree, const char* const str_unique, std::string str)
//{
//	const nodeSet::binaryTreeNode<int>* currentNode = hfTree->getRoot();
//	std::string result;
//
//	for (auto ele : str)
//	{
//		if (ele == '0')
//			currentNode = currentNode->leftChild;
//		else
//			currentNode = currentNode->rightChild;
//
//		if (!currentNode->leftChild && !currentNode->rightChild)
//		{
//			result.push_back(str_unique[currentNode->element - 1]);
//			currentNode = hfTree->getRoot();
//		}
//	}
//	return result;
//}
//
//
//
////
////int main()
////{
////	
////
////}
//
//
//
//void start()
//{
//	using namespace std;
//
//	linkedBinaryTree<int>* hfTree = nullptr;
//	int* str_count = nullptr;
//	char* str_unique = nullptr;
//	int size = 0;
//
//	while (true)
//	{
//		int choice;
//		cout << "================================================================" << endl;
//		cout << "=================HuffmanTree 编码===============================" << endl;
//		cout << "================================================================" << endl;
//		cout << "=                                               ================" << endl;
//		cout << "=  1、输入字符串构建霍夫曼树					 ================" << endl;
//		cout << "=  2、根据现有的编码表输入字符串进行编码        ================" << endl;
//		cout << "=                                               ================" << endl;
//		cout << "===============================written by 左俊 2024-1-9=========" << endl;
//		cout << "================================================================" << endl;
//		cout << "请输入你的选择: " << endl;
//		cin >> choice;
//
//		switch (choice)
//		{
//		case 1:
//			//构建霍夫曼树
//			break;
//		case 2:
//			//根据现有编码表输入字符串进行编码
//			break;
//
//		default:
//			break;
//		}
//	}
//
//
//	delete hfTree;
//}