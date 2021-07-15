#ifndef TREE_H
#define TREE_H

#include "Headers.h"
#include "Helper_Functions.h"

struct Attribute{
	string Name, Value;
};

class TreeNode{
public:
	bool Data, Error, visited;
	string Tag_Name, Tag_Value;
	vector<Attribute> attributes;
	vector<TreeNode *> children;
	TreeNode* Parent;

	TreeNode(string n = "", string v = ""){
		Tag_Name = n;
		Tag_Value = v;
		if(Tag_Value == "")	Data = false;
		else Data = true;
		Error = false;
		visited = false;
	}

	void insert_node(string Open_Tag){
		Tag_Name = "";
		string str;
		Attribute temp;
		for (unsigned int i = 1; i < Open_Tag.length(); i++){
			while (Open_Tag[i] != ' ' && Open_Tag[i] != '>'){
				Tag_Name += Open_Tag[i++];
			}
			while (i+1 < Open_Tag.length()){
				str = "";
				while (Open_Tag[i] == ' ')	i++;
				while (Open_Tag[i] != ' ' && Open_Tag[i] != '=')	str += Open_Tag[i++];
				temp.Name = str;
				str = "";
				while (Open_Tag[i] == ' ' || Open_Tag[i] == '=' || Open_Tag[i] == '\'' || Open_Tag[i] == '"' || Open_Tag[i] == '\\') i++;
				while (Open_Tag[i] != '\'' && Open_Tag[i] != '"' && Open_Tag[i] != '\\')	str += Open_Tag[i++];
				temp.Value = str;
				i++;
				attributes.push_back(temp);
			}
		}
	}
};

class Tree {
private:
	TreeNode* root;
	string ptr_xml2json(TreeNode* node, string&obj, bool x, int level);
	string ptr_minifying(TreeNode* node, string&mini);
	string ptr_View(TreeNode* node, string&V);
    void Pre_Order_Traverse(TreeNode* node, string&str, int level);
public:
	Tree();
	bool is_empty();
	int countchildren(TreeNode* node);
	int countsimiliar(TreeNode* node, string tag_n, stack<TreeNode*>& Similiars);
	int countattributes(TreeNode* node);
    void insert(vector<string> Data, vector<int> Error);
	void form(stack<TreeNode*>&Similiars,int &g, string&obj, int level);
	string xml2json();
	string minifying();
	string View();
    string Pre_Order();
    int Get_Siblings(TreeNode* node);
    TreeNode *getRoot() const;
    void setRoot(TreeNode *value);
};

string Tabs(int x);

#endif // TREE_H
