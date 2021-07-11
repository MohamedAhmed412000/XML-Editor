#include "Tree.h"

Tree::Tree(){
	root = nullptr;
}
	
bool Tree::is_empty(){
	return root==nullptr;
}

int Tree::countchildren(TreeNode* node){
	return node->children.size();
}

int Tree::countsimiliar(TreeNode* node, string tag_n){
	int count = 0;
	for(int i = 0; i < countchildren(node); i++){
		if(node->children[i]->Tag_Name == tag_n)
			count++;
	}
	return count;
}

int Tree::countattributes(TreeNode* node){
	return node->attributes.size();
}


