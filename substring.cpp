#include "substring.h"


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
