// substring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<vector>
#include<stack>
#include"substring.h"
using namespace std;
string Erase_Spaces(string str) {
	int count = 0, start, end;
	while (str[count] == ' ' || str[count] == '\n' || str[count] == '\t') {
		count++;
	}
	start = count;
	if (start == str.length())
		return "";
	count = str.length() - 1;
	while (str[count] == ' ' || str[count] == '\n' || str[count] == '\t') {
		count--;
	}
	end = count;
	return str.substr(start, end - start + 1);
}
string Get_Tag(string Open_Tag) {
	string open = "";
	for (int i = 1; i < Open_Tag.length(); i++) {
		while (Open_Tag[i] != ' ' && Open_Tag[i] != '>') {
			open += Open_Tag[i++];
		}
		break;
	}
	return open;
}
bool Compare_Tags(string Open_Tag, string Close_Tag) {
	string open = "";
	open = Get_Tag(Open_Tag);
	return (Erase_Spaces(open) == Erase_Spaces(Close_Tag.substr(2, Close_Tag.length() - 3)));
}
int checking_errors(vector<string>&strr, vector<string>&modified, vector<int>&error)
{
	int current = 0;
	bool check = false;
	stack<string> s;
	string nn = "";
	for (int i = 0; i < strr.size(); i++)
	{
		if (current == i - 2)
			check = false;
		if (strr[i][0] != '<')
		{
			modified.push_back(strr[i]);
		}
		if (strr[i][0] == '<'&&strr[i][1] != '/')
		{
			if (i != 0 && strr[i - 1][0] != '<')
			{
				error.push_back(i);
				nn = s.top();
				nn.insert(1, "/");
				modified.push_back(nn);
				s.pop();
			}
			s.push(strr[i]);
			modified.push_back(strr[i]);
		}
		if (strr[i][0] == '<'&&strr[i][1] == '/')
		{
			string er = s.top();
			//strr[i].erase(1, 1);
			if (Compare_Tags(er, strr[i]))
			{
				s.pop();
				modified.push_back(strr[i]);
			}
			else
			{
				current = i;
				string er = s.top();
				string app = er.insert(1, "/");
				modified.push_back(app);
				s.pop();
				if (!check)
				{
					error.push_back(i);
				}
				check = true;
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
		s.pop();
	}
	return error.size();
}
int vector_parse(string str, vector<string>&strr)
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
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
