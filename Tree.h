#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
using namespace std;

string obj={};
string mini={};
string V={};
static var=0;

struct Attribute{
	string Name, Value;
};

class TreeNode{
public:
	string Tag_Name, Tag_Value;
	vector<Attribute> attributes;
	vector<TreeNode *> children;
	bool visited = false;
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
	int countsimiliar(TreeNode* node, string tag_n, stack<TreeNode*>& Similiars);
	int countattributes(TreeNode* node);
	void form(stack<TreeNode*> &Similiars,int &g,string &obj);
	void xml2json(TreeNode* node,string &obj);
	void minifying(TreeNode* node);
	void View(TreeNode* node);
	//int Node_hight(TreeNode* node); //get the hight of that node
	//int Tree_hight(TreeNode* node); //get the hight of the all tree
	//int Nodes_number(TreeNode* node);//get the number of all nodes
};

#endif // TREE_H