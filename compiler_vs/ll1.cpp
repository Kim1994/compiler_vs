#include "stdafx.h"
#include "ll1.h"

map<string, vector<string>> first;
map <string, vector<int>> first_list;
map<string, vector<string>> follow;
map<int,string> List_U;
map<int,string> List_T;
vector<vector<string>> in;
vector<string> M[10][10];
vector<string> split(string str, string pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

void getfirst(string U)
{
	for (int in_i=0; in_i < in.size(); in_i++)
	{
		vector<string> List=in[in_i];
		if (List[0] == U){
			for (int i = 1; i < List.size();i++)
			{
				if (List[i][0] != '~')
				{
					if (find(first[U].begin(), first[U].end(), List[1]) == first[U].end()){
						first[U].push_back(List[1]);
						first_list[U].push_back(in_i);
					}
					break;
				}
				getfirst(List[i]);
				for (int j = 0; j < first[List[i]].size(); j++)
				{
					if (find(first[U].begin(), first[U].end(), first[List[i]][j]) == first[U].end()){
						first[U].push_back(first[List[i]][j]);
						first_list[U].push_back(in_i);
					}
				}
				if (find(first[List[i]].begin(), first[List[i]].end(), "") == first[List[i]].end())
					break;
			}
		}
	}
}

void getfollow()
{
	for (int i = 0; i < in.size();i++)
	{
		for (int j = 1; j < in[i].size()-1; j++)
		{
			if (in[i][j][0] == '~')
			{
				if (in[i][j + 1][0] != '~'){
					if (find(follow[in[i][j]].begin(), follow[in[i][j]].end(), in[i][j + 1]) == follow[in[i][j]].end())
						follow[in[i][j]].push_back(in[i][j + 1]);
				}
				else{
					for (int first_i = 0; first_i < first[in[i][j]].size(); first_i++)
					if (first[in[i][j+1]][first_i]!=""&& find(follow[in[i][j]].begin(), follow[in[i][j]].end(), first[in[i][j+1]][first_i]) == follow[in[i][j]].end())
						follow[in[i][j]].push_back(first[in[i][j+1]][first_i]);
				}
			}
		}
	}
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < in.size(); i++)
		{
			if (in[i][in[i].size() - 1][0] == '~'){
				for (int follow_i = 0; follow_i < follow[in[i][0]].size(); follow_i++){
					if (find(follow[in[i][in[i].size() - 1]].begin(), follow[in[i][in[i].size() - 1]].end(), follow[in[i][0]][follow_i]) == follow[in[i][in[i].size() - 1]].end()){
						follow[in[i][in[i].size() - 1]].push_back(follow[in[i][0]][follow_i]);
						flag = 1;
					}
				}
				if (in[i].size() > 2 && in[i][in[i].size() - 2][0] == '~'&&find(first[in[i][in[i].size() - 1]].begin(), first[in[i][in[i].size() - 1]].end(), "") != first[in[i][in[i].size() - 1]].end()){
					for (int follow_i = 0; follow_i < follow[in[i][0]].size(); follow_i++){
						if (find(follow[in[i][in[i].size() - 2]].begin(), follow[in[i][in[i].size() - 2]].end(), follow[in[i][0]][follow_i]) == follow[in[i][in[i].size() - 2]].end()){
							follow[in[i][in[i].size() - 2]].push_back(follow[in[i][0]][follow_i]);
							flag = 1;
						}
					}
				}
			}
		}
	}
}

void FirstAndFollow()
{
	string s;
	
	vector<string> s_formet;
	vector<string> s_formet2;
	int first = 1;
	int count_u = 0, count_t = 0;
	while (1)
	{
		getline(cin, s);
		if (s == "end")
			break;
		s_formet = split(s, "->");
		s_formet2 = split(s_formet[1], " ");
		vector<string> temp;
		temp.push_back(s_formet[0]);

		map<int, string>::iterator it_u = List_U.begin();
		for (; it_u != List_U.end(); it_u++){
			if (it_u->second == temp[0])
				break;
		}
		if (it_u == List_U.end())
			List_U[count_u++] = temp[0];

		if (s_formet2.size() == 0)
			s_formet2.push_back("");
		for (int i = 0; i < s_formet2.size(); i++){
			temp.push_back(s_formet2[i]);
			if (s_formet2[i][0] != '~'){
				map<int, string>::iterator it_t = List_T.begin();
				for (; it_t != List_T.end(); it_t++){
					if (it_t->second == s_formet2[i])
						break;
				}
				if (it_t == List_T.end())
					List_T[count_t++] = s_formet2[i];
			}
		}
		in.push_back(temp);

		if (first){
			follow[temp[0]].push_back("$");
			first = 0;
		}
	}
	List_T[count_t] = "$";

	
	for (int i=0; i < List_U.size(); i++)
	{
		getfirst(List_U[i]);
	}
}

void getmap()
{
	int p_u, p_t;
	int flag_em = 0, flag_money = 0;
	for (int in_i = 0; in_i < in.size(); in_i++)
	{
		flag_em = 0 ;
		flag_money = 0;
		vector<string> List = in[in_i];
		vector<string> temp;
		for (int i_temp = 1; i_temp < List.size(); i_temp++)
			temp.push_back(List[i_temp]);
		map<int, string>::iterator it_u = List_U.begin();
		for (; it_u != List_U.end(); it_u++){
			if (it_u->second == List[0]){
				p_u = it_u->first;
				break;
			}
		}
		for (int first_i = 0; first_i < first[List[0]].size(); first_i++)
		{
			if (first_list[List[0]][first_i] == in_i){
				map<int, string>::iterator it_t = List_T.begin();
				for (; it_t != List_T.end(); it_t++){
					if (it_t->second == first[List[0]][first_i]){
						p_t = it_t->first;
						break;
					}
				}
				M[p_u][p_t] = temp;
			}
			if (first[List[0]][first_i] == ""){
				flag_em = 1;
				for (int follow_i = 0; follow_i < follow[List[0]].size(); follow_i++)
				{
					map<int, string>::iterator it_t = List_T.begin();
					for (; it_t != List_T.end(); it_t++){
						if (it_t->second == follow[List[0]][follow_i]){
							p_t = it_t->first;
							break;
						}
					}
					M[p_u][p_t] = temp;
				}
			}
		}
	}
}

bool ll1()
{
	int Usize = List_U.size();
	
	stack<string> A;
	A.push("$");
	A.push(List_U[0]);
	string s[100];
	for (int i = 0; i < 100; i++){
		cin >> s[i];
		if (s[i] == "$")
			break;
	}
	int p = 0;
	int flag = 0;
	while (A.top() != "$")
	{
		while (A.top()[0] == '~')
		{
			int U_i;
			for (U_i = 0; U_i < 10; U_i++)
			{
				if (List_U[U_i] == A.top())
					break;
			}
			int T_i;
			for (T_i = 0; T_i < 10; T_i++)
			{
				if (List_T[T_i] == s[p])
					break;
			}
			A.pop();
			if (U_i == 10 && U_i == 10)
			{
				flag = 1;
				break;
			}
			vector<string>::reverse_iterator it = M[U_i][T_i].rbegin();
			for (; it != M[U_i][T_i].rend(); it++)
			{
				A.push(*it);
			}
		}
		if (flag)
			break;
		else
		{
			if (A.top() == ""){
				A.pop();
				continue;
			}
			if (A.top() == s[p]){
				p++;
				A.pop();
			}
			else{
				flag = 1;
				break;
			}
		}	
	}
	if (flag){
		cout << "²»Æ¥Åä";
	}
	else{
		cout << "Æ¥Åä";
	}
	
	return 0;
}



//int main()
//{
//	FirstAndFollow();
//
//	cout << "first" << endl;
//	map<string, vector<string>>::iterator itfirst = first.begin();
//	for (; itfirst != first.end(); itfirst++){
//		cout << itfirst->first<<":";
//		for (int i = 0; i < itfirst->second.size(); i++){
//			if (itfirst->second[i] == "")
//				cout << "_("<<first_list[itfirst->first][i]<<") ";
//			else
//				cout << itfirst->second[i] << "(" << first_list[itfirst->first][i] << ") "<<" ";
//		}
//		cout<<endl;
//	}
//	getfollow();
//
//	cout << "follow" << endl;
//	itfirst = follow.begin();
//	for (; itfirst != follow.end(); itfirst++){
//		cout << itfirst->first << ":";
//		for (int i = 0; i < itfirst->second.size(); i++){
//			if (itfirst->second[i] == "")
//				cout << "_ ";
//			else
//				cout << itfirst->second[i] << " ";
//		}
//		cout << endl;
//	}
//
//	cout << "map" << endl;
//	getmap();
//	for (int i = 0; i < 10; i++)
//		cout << List_T[i];
//	cout << endl;
//	for (int i = 0; i < 10; i++){
//		cout << List_U[i];
//		for (int j = 0; j < 10; j++){
//			for (int ii = 0; ii < M[i][j].size(); ii++){
//				cout << M[i][j][ii] << " ";
//			}
//			cout << "|";
//		}
//		cout << endl;
//	}
//
//	ll1();
//}