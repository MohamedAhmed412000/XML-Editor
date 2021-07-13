// substring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<vector>
using namespace std;
int vector_parse(string str,vector<string>&strr)
{
	string newstr = "";
	string final = "";
	bool a = false;
	bool b = false;
	bool c = false;
	bool d = false;
	bool e = false;
	int j = 0;
	//cout << str.length() << endl;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			continue;
		}
		if (str[i] == '<')
		{
			b = false;
			a = true;
			newstr += str[i];
			continue;
		}
		if (str[i] == '>')
		{
			a = false;
			b = true;
			newstr += str[i];
			continue;
		}
		if (a)
		{
			newstr += str[i];
		}
		if (b&&str[i] != '<')
		{
			if ((str[i] >= 65 && str[i] <= 92) || (str[i] >= 97 && str[i] <= 122) || str[i] == 44 || str[i] == 46 || (str[i] >= 48 && str[i] <= 57))
				newstr += str[i];
		}
	}
	//cout << str << endl;
//cout << newstr << endl;
	//cout << newstr.length() << endl;
	for (int i = 0; i < newstr.length(); i++)
	{
		if (newstr[i] == '<')
		{
			if (e)
			{
				strr.push_back(final);
				j++;
				final = "";
				e = false;
			}
			final += newstr[i];
			c = true;
			d = false;
			continue;
		}
		if (newstr[i] == '>')
		{
			d = true;
			c = false;
			final += newstr[i];
			strr.push_back(final);
			j++;
			final = "";
			continue;
		}
		if (c)
		{
			final += newstr[i];
		}
		if (d)
		{
			e = true;
			final += newstr[i];
		}

	}
	return j;
}
int main()
{
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
		"			    <name> 2 </id>                              "
		"			</follower>                                     "
		"			<follower>                                      "
		"			    <id> 4 </id>                                "
		"			</follower>                                     "
		"	  </user>                                               "
		"</users>                                                   ";
	vector<string> strr;
	int total = 0;
	total=vector_parse(str,strr);

	for (int i = 0; i < total; i++)
	{
		cout << strr[i] << endl;
	}

	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
