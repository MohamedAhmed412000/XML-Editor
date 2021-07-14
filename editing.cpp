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


int Tree::Get_Siblings(TreeNode* node){
	if (node->Parent == nullptr)
		return 0;
	else
		return Tree::countchildren(node->Parent)-1;
}