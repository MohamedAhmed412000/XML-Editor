#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;
string Erase_Spaces(string str);
string Get_Tag(string Open_Tag);
bool Compare_Tags(string Open_Tag, string Close_Tag);
int checking_errors(vector<string>&strr, vector<string>&modified, vector<int>&error);
int vector_parse(string str, vector<string>&strr);