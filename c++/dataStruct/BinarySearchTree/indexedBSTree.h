#pragma once

#include "bSTree.h"

template<typename K,typename E>
class indexedBSTree :public bSTree<K, E>
{
public:
		//���ݸ��������������������Ե�ָ��
	virtual std::pair<const K, E>* get(const int) const = 0;
		//���ݸ�����������ɾ��������
	virtual void deleteByIndex(const int) = 0;


};



