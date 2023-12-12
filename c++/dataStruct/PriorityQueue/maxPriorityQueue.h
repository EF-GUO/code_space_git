#pragma once


template<typename T>
class maxPriorityQueue
{
public:
	virtual ~maxPriorityQueue(){}
	virtual bool empty() const = 0;
			//���ҽ�����ǰ������ȼ�����Ϊ�շ���true,���򷵻�false
	virtual int size() const = 0;
			//���ص�ǰ���е�Ԫ�ظ���
	virtual const T& top() = 0;
			//���ص�ǰ���еĸ��ڵ�Ԫ��ֵ������
	virtual void pop() = 0;
			//ɾ������Ԫ��
	virtual void push(const T& theElement) = 0;
			//����Ԫ��theElement
};