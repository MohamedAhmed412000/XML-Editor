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

int Tree::countsimiliar(TreeNode* node, string tag_n, stack<TreeNode*>& Similiars){
	int count = 0;
	for(int i = 0; i < countchildren(node); i++){
	if(node->children[i]->Tag_Name == tag_n)
			Similiars.push(node->children[i]);
			count++;
		}
	return count;
}

int Tree::countattributes(TreeNode* node){
	return node->attributes.size();
}


void Tree::form(stack<TreeNode*>&Similiars,int &g){
	int i=0;
	obj+="\"" + Similiars.top()->Tag_Name + "\"";
	obj+=": [";
	obj+="\n";
	while(!(Similiars.empty())){
		int n = countattributes(Similiars.top());
		obj+="\"" + Similiars.top()->Tag_Name + "\"";
		obj+=": {";
		if(n>=0){
			for(int i=0;i<n;i++){
				obj+="\"" +"@"+ Similiars.top()->attributes[i].Name + "\"";
				obj+="\"" + Similiars.top()->attributes[i].Value + "\"";
				obj+=",";
			}
		}
		if(Similiars.top()->Tag_Value!=nullptr){
			obj+="\"" + "#"+ "text" + "\"" +": ";
			obj+="\"" + Similiars.top()->Tag_Value + "\"" + "}";
			obj+="\n";
		}
		else{
			obj+="}";
		}
		Similiars.top()->visited = true;
		Similiars.pop();
		i++;
		g--;
	}
	obj+="]";
}


void Tree::xml2json(TreeNode* node){
	stack<TreeNode*> Similiars;
	g=countchildren(node);
	if(g==0){
		int n = countattributes(node);
		obj+="\"" + node->Tag_Name + "\"";
		obj+=": {";
		obj+="\n";
		if(n>=0){
			for(int i=0;i<n;i++){
				obj+="\"" +"@"+ node->attributes[i].Name + "\"";
				obj+="\"" + node->attributes[i].Value + "\"";
				obj+=",";
				obj+="\n";
			}
		} //if the tag does not have text
		if(node->Tag_Value!=nullptr){
			obj+="\"" + "#"+ "text" + "\"" +": ";
			obj+="\"" + node->Tag_Value + "\"" + "\n"+"}";
			obj+="\n";
		}
		else{
			obj+="\"" + "#"+ "text" + "\"" +": "+"NULL"+"}";
		}
		return;
	}

	for(int i = 0; i < g; i++){
		int m = countsimiliar(node,node->children[i],Similiars);
		if(m==1){
			xml2json(node->children[i]);
		}
		else if(m>1&&(node->children[i].visited==false)){
			form(Similiars,g); //not sure of that yet as i need to delete the similar nodes after we use it because if we don't it will be called forever
		}
	}
}

void Tree::minifying(TreeNode* node){
	g=countchildren(node);
	if(g==0){
		int n = countattributes(node);
		mini+="<" + node->Tag_Name;
		if(n>=0){
			for(int i=0;i<n;i++){
				mini+=" " +node->attributes[i].Name + "=";
				mini+="\""+ node->attributes[i].Value +"\" ";
			}
		}
		mini+=">";
		mini+=node->Tag_Value;
		mini+="/<" + node->Tag_Name+">";
		return;
	}
	for(int i = 0; i < g; i++){
			minifying(node->children[i]);
	}
}

