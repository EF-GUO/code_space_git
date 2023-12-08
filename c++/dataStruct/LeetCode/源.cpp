#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{


}





//107.¶þ²æÊ÷µÄ²ãÐò±éÀúII

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> result;
		if (!root)
			return result;

		stack<int> theStack;
		TreeNode* currentNode = root;
		while (true)
		{

		}


	}



};

