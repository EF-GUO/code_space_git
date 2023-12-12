#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};



void flatten(TreeNode* root) {
	if (!root)
		return;

	std::stack<TreeNode*> theStack;
	std::queue<TreeNode*> theQueue;
	TreeNode* result = nullptr;

	while (root || !theStack.empty())
	{
		while (root)
		{
			theQueue.push(root);
			theStack.push(root);
			root = root->left;
		}

		root = theStack.top();
		theStack.pop();
		root = root->right;
	}

	root = theQueue.front();
	TreeNode* currentNode = root;
	theQueue.pop();
	while (!theQueue.empty())
	{
		currentNode->right = theQueue.front();
		theQueue.pop();
		currentNode = currentNode->right;
	}

}



int main()
{
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(4);
	root->right = new TreeNode(5);
	root->right->right = new TreeNode(6);
	flatten(root);


}
