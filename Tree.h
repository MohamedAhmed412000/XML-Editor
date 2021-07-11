#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
using namespace std;

struct Attribute{
	string Name, Value;
};

class TreeNode{
public:
	string Tag_Name, Tag_Value;
	vector<Attribute> attributes;
	vector<TreeNode *> children;
	TreeNode(string n = "", string v = ""){
		Tag_Name = n;
		Tag_Value = v;
	}
};

class Tree {
private:
	TreeNode* root;
public:
	Tree();
	bool is_empty();
	int countchildren(TreeNode* node);
	int countsimiliar(TreeNode* node, string tag_n);
	int countattributes(TreeNode* node);
};

#endif // TREE_H