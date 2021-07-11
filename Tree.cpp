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


void Tree::xml_to_json(TreeNode* node){
	
	obj+="\"" + node->Tag_Name + "\"";
	obj+=": {";
	int numbers=countattributes(node);
	for(int i=0; i < number;i++){
		obj+="\"" +"@"+ node->attributes[i].Name + "\"";
		obj+=": {";
		obj+="\"" +"@"+ node->attributes[i].Value + "\"";
		obj+=",";
	}
	obj+="\"" + "#"+ "text" + "\"" +": ";
	obj+="\"" + node->Tag_Value + "\"" + "}";
	for(int i = 0; i < countchildren(node); i++){
		if(node->children==nullptr){
			return;
		}
		else{
			xml_to_json(node->children[i]);//recursion
		}
	}
	
}


