#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "minHeap.h"
#include "huffmanTree.h"

void getHuffmanCode(
	const nodeSet::binaryTreeNode<int>* const node,
	std::vector<char>& unique_str,
	std::map<char, std::string>& mapping,
	std::string str = ""
);

std::string coding(std::map<char, std::string>& mapping, std::string& str);
std::string decoding(const linkedBinaryTree<int>* const hfTree, std::vector<char>& str_unique, std::string str);




//得到对应编码函数
void getHuffmanCode(
	const nodeSet::binaryTreeNode<int>* const node,
	std::vector<char>& str_unique,
	std::map<char, std::string>& mapping,
	std::string str)
{
	if (!node->leftChild && !node->rightChild)
		mapping[str_unique.at(node->element - 1)] = str;
	else
	{
		getHuffmanCode(node->leftChild, str_unique, mapping, str + '0');
		getHuffmanCode(node->rightChild, str_unique, mapping, str + '1');
	}
}

//编码
std::string coding(std::map<char, std::string>& mapping, std::string& str)
{
	std::string result;

	for (auto ele : str)
		result += mapping[ele];
	return result;
}

//打印输出对应的编码表
void showCoding(const std::map<char, std::string>& mapping)
{
	std::cout << "字符对应的Huffman编码" << std::endl;
	for (auto ele : mapping)
		std::cout << ele.first << " : " << ele.second << std::endl;
}

//解码
std::string decoding(const linkedBinaryTree<int>* const hfTree, std::vector<char>& str_unique, std::string str)
{
	const nodeSet::binaryTreeNode<int>* currentNode = hfTree->getRoot();
	std::string result;

	for (auto ele : str)
	{
		if (ele == '0')
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;

		if (!currentNode->leftChild && !currentNode->rightChild)
		{
			result.push_back(str_unique.at(currentNode->element - 1));
			currentNode = hfTree->getRoot();
		}
	}
	return result;
}



linkedBinaryTree<int>* initializeHfTree(
	std::vector<int>& str_count,
	std::vector<char>& str_unique,
	std::map<char, std::string>& mapping,
	int& unique_size
)
{
	str_count.clear();
	str_unique.clear();
	mapping.clear();
	unique_size = 0;

	std::string str;
	std::cout << "Enter the string: ";

	while (std::cin.get() != '\n')
		continue;

	std::getline(std::cin, str);



	for (int i = 0; i < str.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < unique_size; j++)
		{
			if (str[i] == str_unique.at(j))
			{
				flag = true;
				str_count.at(j)++;
				break;
			}
		}
		if (!flag)
		{
			str_unique.push_back(str[i]);
			str_count.push_back(0);
			str_count.at(unique_size++)++;
		}
	}
	linkedBinaryTree<int>* hfTree = getHuffmanTree<int>(str_count, unique_size);
	getHuffmanCode(hfTree->getRoot(), str_unique, mapping);
	return hfTree;
}




void start()
{
	std::string str;
	std::vector<int> str_count;
	std::vector<char> str_unique;
	std::map<char, std::string> mapping;
	linkedBinaryTree<int>* hfTree = nullptr;

	int unique_size = 0;



	while (true)
	{
		int choice;
		std::cout << "================================================================" << std::endl;
		std::cout << "=================HuffmanTree 编码===============================" << std::endl;
		std::cout << "================================================================" << std::endl;
		std::cout << "=                                               ================" << std::endl;
		std::cout << "=  1、输入字符串构建霍夫曼树                    ================" << std::endl;
		std::cout << "=  2、根据现有的编码表输入字符串进行编码        ================" << std::endl;
		std::cout << "=  3、解码                                      ================" << std::endl;
		std::cout << "=  0、退出                                      ================" << std::endl;
		std::cout << "===============================written by 左俊 2024-1-9=========" << std::endl;
		std::cout << "================================================================" << std::endl;
		std::cout << "请输入你的选择: " << std::endl;
		std::cin >> choice;

		if (std::cin.fail() && !std::cin.eof())
		{
			std::cin.clear();
			while (std::cin.get() != '\n')
				continue;
		}

		switch (choice)
		{

		case 0:
			std::cout << "希望我们还有再见面的一天" << std::endl;
			system("pause");
			return;
		case 1:
			//构建霍夫曼树
			delete hfTree;
			hfTree = initializeHfTree(str_count, str_unique, mapping, unique_size);
			std::cout << "\033c";
			showCoding(mapping);
			break;
		case 2:
			std::cout << "\033c";
			//根据现有编码表输入字符串进行编码
			if (!hfTree)
			{
				std::cout << "当前编码表为空，请先构建编码表" << std::endl;
				system("pause");
				std::cout << "\033c";
			}
			else
			{
				while (std::cin.get()!='\n')
					continue;
				showCoding(mapping);
				std::cout << "请输入需要编码的字符串: " << std::endl;
				std::getline(std::cin, str);
				std::cout << "编码结果为: " << std::endl;
				std::cout << coding(mapping, str) << std::endl;
				system("pause");
				std::cout << "\033c";
			}
			break;

		case 3:
			//解码
			while (std::cin.get() != '\n')
				continue;
			showCoding(mapping);
			std::cout << "请输入编码： " << std::endl;
			std::getline(std::cin, str);

			std::cout << "原始字符串为: " << decoding(hfTree, str_unique, str) << std::endl;
			system("pause");
			std::cout << "\033c";
			break;

		default:
			std::cout << "\033c";
			break;
		}
	}


	delete hfTree;
}



int main()
{
	using namespace std;
	start();
}


