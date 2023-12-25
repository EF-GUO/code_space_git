#include <iostream>



using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
ListNode* rotateRight(ListNode* head, int k);

void outPut(ListNode* node);


int main()
{
	ListNode* first = new ListNode(1);
	ListNode* currentNode = first;
	currentNode->next = new ListNode(2);	currentNode = currentNode->next;
	currentNode->next = new ListNode(3);	currentNode = currentNode->next;
	currentNode->next = new ListNode(4);	currentNode = currentNode->next;
	currentNode->next = new ListNode(5);	currentNode = currentNode->next;
    outPut(first);
    cout << endl << endl;
    first = rotateRight(first, 2);
    outPut(first);



}





ListNode* rotateRight(ListNode* head, int k) {
    //前链表的头
    ListNode* theHead = head;
    int count = 1;
    while (head->next && count != k)
    {
        count++;
        head = head->next;
    }
    ListNode* nextNode = head->next,*returnNode = head->next;
    head->next = nullptr;
    if (count != k)
        return theHead;

    while (nextNode->next)
        nextNode = nextNode->next;
    nextNode->next = theHead;
    return returnNode;
}

void outPut(ListNode* node)
{
    while (node)
    {
        cout << node->val << " ";
        node = node->next;
    }
}

