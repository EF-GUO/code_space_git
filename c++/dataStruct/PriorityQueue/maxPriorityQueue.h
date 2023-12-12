#pragma once


template<typename T>
class maxPriorityQueue
{
public:
	virtual ~maxPriorityQueue(){}
	virtual bool empty() const = 0;
			//当且仅当当前最大优先级队列为空返回true,否则返回false
	virtual int size() const = 0;
			//返回当前队列的元素个数
	virtual const T& top() = 0;
			//返回当前队列的根节点元素值的引用
	virtual void pop() = 0;
			//删除队首元素
	virtual void push(const T& theElement) = 0;
			//插入元素theElement
};