#pragma once

#include "bSTree.h"

template<typename K,typename E>
class indexedBSTree :public bSTree<K, E>
{
public:
		//根据给定的索引，返回其数对的指针
	virtual std::pair<const K, E>* get(const int) const = 0;
		//根据给定的索引，删除其数对
	virtual void deleteByIndex(const int) = 0;


};



