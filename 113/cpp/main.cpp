#include <iostream>
#include <vector>

using namespace std;

/** 二叉树结点定义 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int> > pathSum(TreeNode* root, int sum) {
	    vector<vector<int> > result;
		vector<int> path;
		pathSum(result, path, root, sum);
		return result;
    }

private:
    void pathSum(vector<vector<int> > &result, vector<int> path, TreeNode* root, int sum) {
		if (root == NULL) return;
	    path.push_back(root->val);
		sum -= root->val;
		if (sum == 0 && root->left == NULL && root->right == NULL) {
			result.push_back(path);
			return;
		}
		pathSum(result, path, root->left, sum);
		pathSum(result, path, root->right, sum);
	}
};

int main() {
	TreeNode n1(5), n2(4), n3(8), n4(11), n5(13), n6(4), n7(7), n8(2), n9(5), n10(1);
	n1.left = &n2; n1.right = &n3;
	n2.left = &n4;
	n3.left = &n5;
	n3.right = &n6;
	n4.left = &n7; n4.right = &n8;
    n6.left = &n9; n6.right = &n10;
    Solution s;
    vector<vector<int> > result = s.pathSum(&n1, 22);
	for (vector<vector<int> >::iterator it = result.begin(); it != result.end(); ++it) {
    	cout << "[";
		for (vector<int>::iterator itInt = it->begin(); itInt != it->end(); ++itInt) cout << *itInt << ", ";
		cout << "]," << endl;
    }
		
	return 0;
}
