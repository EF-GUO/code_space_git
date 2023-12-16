#pragma once
#include <iostream>



//abstractClass
template<typename K, typename E>
class bSTree
{
public:
	virtual ~bSTree(){}
	virtual bool empty() const = 0;
	virtual int size() const = 0;

	virtual std::pair<const K, E>* find(const K&) const = 0;
	virtual void erase(const K&) = 0;
	virtual void insert(const std::pair<const K, E>&) = 0;

	virtual void ascend() = 0;	//按关键字升序输出这棵二叉搜索树
};





















































