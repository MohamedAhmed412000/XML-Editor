#include "Tree.h"

Tree::Tree(){
	root = nullptr;
}

string Tabs(int x){
	string str = "";
	for (int i = 0; i < x; i++)
		str += "\t";
	return str;
}

bool Tree::is_empty(){
	return root==nullptr;
}

int Tree::countchildren(TreeNode* node){
	return node->children.size();
}

int Tree::Get_Siblings(TreeNode* node){
    if (node->Parent == nullptr)
        return 0;
    else
        return Tree::countchildren(node->Parent)-1;
}

int Tree::countsimiliar(TreeNode* node, string tag_n, stack<TreeNode*>& Similiars){
	int count = 0;
	for(int i = 0; i < countchildren(node); i++){
		if(node->children[i]->Tag_Name == tag_n){
			Similiars.push(node->children[i]);
			count++;
		}
	}
	return count;
}

int Tree::countattributes(TreeNode* node){
	return node->attributes.size();
}

void Tree::insert(vector<string> Data, vector<int> Error){
	TreeNode* cur = root;
	int count = 0;
	for (unsigned int i = 0; i < Data.size(); i++){
		// Adding Node with Openning Tag 
		if(Get_Type(Data[i]) == 'O'){
			// If Root is empty (First element comes)
			if (cur == nullptr){
				cur = new TreeNode;
				root = cur;
				cur->insert_node(Data[i]);
				cur->Parent = nullptr;
                if (!Error.empty()){
                    if(Error[count] == i){
                       cur->Error = true;
                       count++;
                    }
                }
			}
			// Adding General Node
			else{
				TreeNode* child = new TreeNode;
				child->insert_node(Data[i]);
				child->Parent = cur;
				cur->children.push_back(child);
				cur->Data = false;
				cur->Tag_Value = "";
				cur = child;
                if (!Error.empty()){
                    if(Error[count] == i){
                       cur->Error = true;
                       count++;
                    }
                }
			}
		}
		// Adding Data(Tag Value) to current Node
		else if (Get_Type(Data[i]) == 'V'){
			cur->Tag_Value = Data[i];
			cur->Data = true;
		}
		// Return to Parent Node when comes closing Tag
		else if (Get_Type(Data[i]) == 'C'){
			cur = cur->Parent;
            if (!Error.empty()){
                if(Error[count] == i){
                   cur->Error = true;
                   count++;
                }
            }
		}
	}
}

TreeNode *Tree::getRoot() const
{
    return root;
}

void Tree::setRoot(TreeNode *value)
{
    root = value;
}

string Tree::ptr_xml2json(TreeNode* node, string&obj, bool x, int level){
    stack<TreeNode*> Similiars;
       int g=countchildren(node);
       int n = countattributes(node);
       int h=Get_Siblings(node);
       //int flag=g;
       if(x){
           obj +="\n";
           obj += Tabs(level);
       }
       obj += "\"" + node->Tag_Name + "\": " ;
       if(g>0) obj += "{";
       if(n>=0)
       {
           for(int i=0;i<n;i++)
           {
               if(i==0){obj+="\n";}
               obj += Tabs(level+1);
               obj+=  "\"";
               obj+= 64;
               obj+= node->attributes[i].Name + "\"" + ": ";
               obj+="\"" + node->attributes[i].Value + "\"";
               obj+=",";
               if(i!=n-1){obj+="\n";}
           }
       }
       if(node->Tag_Value != ""){
           obj+="\"" + node->Tag_Value + "\"";
           if(h>0){//h>1
               obj += ",";
               obj +="\n";
           }
       }
       if(g==0)	return obj;
       for(int i = 0; i < g; i++){
           int m = countsimiliar(node,node->children[i]->Tag_Name,Similiars);
           if(m==1){
               Similiars.pop();
               ptr_xml2json(node->children[i], obj, true, level+1);
           }
           else if(m>1&&(node->children[i]->visited==false)){
               form(Similiars,g, obj, level+1);
           }
       }
       if(g>0)	obj += Tabs(level+1)+ "}\n";
       return obj;

}

void Tree::form(stack<TreeNode*>&Similiars,int &g, string&obj, int level){
   int i=0;
   obj+= "\n"+ Tabs(level) +"\"" + Similiars.top()->Tag_Name + "\" :";
   obj+="\n"+Tabs(level)+"[";
   obj+="\n";
   while(!(Similiars.empty())){
       int n = countattributes(Similiars.top());
       int f = countchildren(Similiars.top());
       if(i==0){obj+=Tabs(level+1);}
       obj+="{";//Tabs(level) +
       if(n>=0){
           for(int i=0;i<n;i++){
               if(i==0){obj+="\n";}
               obj += Tabs(level+1);
               obj+="\"";
               obj+= 64;
               obj+= Similiars.top()->attributes[i].Name + "\"";
               obj+="\"" + Similiars.top()->attributes[i].Value + "\"";
               obj+=",";
               if(i!=n-1){obj+="\n";}
           }
       }
       if(f > 0){
           for(int i=0;i<f;i++){
               ptr_xml2json(Similiars.top()->children[i], obj, false, level+1);
           }
       }
       if(Similiars.top()->Tag_Value == ""){
           obj+="}";
       }
       else{
           obj +="\"";
           obj += 35;
           obj += "text";
           obj += "\"";
           obj += ": ";
           obj+="\"" + Similiars.top()->Tag_Value + "\"" + "}";
       }
       Similiars.top()->visited = true;
       Similiars.pop();
       i++;
       if(!Similiars.empty()) obj += ", ";
   }
   obj+="\n"+Tabs(level)+"]\n";
}

string Tree::xml2json(){
	string obj = "";
	return "{\n"+Tree::ptr_xml2json(Tree::root, obj, true, 1)+"}\n";
}

string Tree::Pre_Order(){
    string str = "";
    Tree::Pre_Order_Traverse(root, str, 0);
    return str;
}

void Tree::Pre_Order_Traverse(TreeNode* node, string&str, int level){
    if(node == nullptr) return;
    if(node->Data == true){
        str += Tabs(level)+ "<"+node->Tag_Name;
        if(node->attributes.size() != 0) str +=" ";
        for(unsigned i = 0; i < node->attributes.size(); i++){
            str += "\""+node->attributes[i].Name+"\"=\""+node->attributes[i].Value+"\"";
            if (i < node->attributes.size()-1) str+=" ";
        }
        str += ">"+node->Tag_Value+"</"+node->Tag_Name+">\n";
    }
    else{
        str += Tabs(level)+ "<"+node->Tag_Name;
        if(node->attributes.size() != 0) str +=" ";
        for(unsigned i = 0; i < node->attributes.size(); i++){
            str += "\""+node->attributes[i].Name+"\"=\""+node->attributes[i].Value+"\"";
            if (i < node->attributes.size()-1) str+=" ";
        }
        str += ">\n";
        for(unsigned int i = 0; i < node->children.size(); i++){
            Tree::Pre_Order_Traverse(node->children[i], str, level+1);
        }
        str += Tabs(level)+ "</"+node->Tag_Name+">\n";
    }
}


