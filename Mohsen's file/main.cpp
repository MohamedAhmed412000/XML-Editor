#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include"substring.h"
using namespace std;
int main()
{

	int errors = 0;
	vector<int>error;
	string str = "<users>                                           "
		"    <user>                                                 "
		"        <id>1                                              "
		"        <name>user1</name>                                 "
		"        <posts>                                            "
		"            <post>                                         "
		"			    Lorem and me have gone to paris.            "
		"			</post>                                         "
		"			<post>                                          "
		"			     me,and my 2friends have gone to home       "
		"			</post>                                         "
		"		 </posts>                                           "
		"		 <followers>                                        "
		"                <follower>                                 "
		"			    <name> 2 </id>                              "
		"			</follower>                                     "
		"			<follower>                                      "
		"			    <id> 4 </id>                                "
		"			</follower>                                     "
		"	  </user>                                               "
		"</users>                                                   ";
	vector<string> strr;
	int total = 0;
	int counter = 0;
	int k = 0;
	vector<string>modified;
	total = vector_parse(str, strr);
	errors = checking_errors(strr, modified, error);
	/*	for (int i = 0; i < total; i++)
		{
			cout << strr[i] << endl;
		}*/
	cout << "modified vector" << endl;

	for (int i = 0; i < modified.size(); i++)
	{
		cout << modified[i] << endl;
	}
	cout << errors << endl;
	for (int i = 0; i < errors; i++)
	{
		cout << error[i] << endl;
	}
}
