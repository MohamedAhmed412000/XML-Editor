// substring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;
int checking_errors(vector<string>&strr,vector<string>&modified,int &counter)
{
	vector<int>error;
	stack<string> s;
	string nn = "";
	for (int i = 0; i < strr.size(); i++)
	{
		if (strr[i][0] != '<')
		{
			modified.push_back(strr[i]);
			counter++;
		}
		if (strr[i][0] == '<'&&strr[i][1] != '/')
		{
			if (i != 0 && strr[i - 1][0] != '<')
			{
				error.push_back(i);
				nn = s.top();
				nn.insert(1, "/");
				modified.push_back(nn);
				counter++;
				s.pop();
			}
			s.push(strr[i]);
			modified.push_back(strr[i]);
			counter++;
		}
		if (strr[i][0] == '<'&&strr[i][1] == '/')
		{
			string er = s.top();
			string neww;
			neww = strr[i];
			strr[i].erase(1, 1);
			if (strr[i] == er)
			{
				s.pop();
				modified.push_back(neww);
				counter++;
			}
			else
			{
				error.push_back(i);
				string er = s.top();
				string app = er.insert(1, "/");
				modified.push_back(app);
				counter++;
				s.pop();
			}
		}
	}
	for (int i = 0; i < strr.size(); i++)
	{
		if (s.empty())
			break;
		string m = s.top();
		m.insert(1, "/");
		modified.push_back(m);
		counter++;
		s.pop();
	}
	return error.size();
}
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
	
	int errors = 0;
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
	total=vector_parse(str,strr);
	errors = checking_errors(strr,modified,counter);
/*	for (int i = 0; i < total; i++)
	{
		cout << strr[i] << endl;
	}*/
	cout << "modified vector" << endl;
	
	for (int i = 0; i < counter; i++)
	{
		cout << modified[i] << endl;
	}
	cout << errors << endl;

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
