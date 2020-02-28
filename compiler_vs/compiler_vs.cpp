// compiler_vs.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	string a;
	cin >> a;
	NodeTree *node = creattree(a);
	vector<enfanode*> enfa = createnfa(node);
	cout << "done" << endl;
	enfanode* start = enfa2nfa(enfa);
	cout << "done" << endl;
	start = nfa2dfa(start);
	string str;
	cin >> str;
	istringstream iss(str);
	char c;
	int flag;
	while (iss >> c){
		flag = 0;
		for (vector<enfaedge*>::iterator it = start->out.begin(); it != start->out.end(); it++)
		{
			enfaedge* edgetemp = *it;
			if (edgetemp->match[0] == c)
			{
				flag = 1;
				start = edgetemp->end;
				break;
			}
		}
		if (flag == 0){
			cout << "匹配失败" << endl;
			flag = -1;
			break;
		}
	}
	if (flag != -1)
	{
		if (start->FinalStatus == true){
			cout << "匹配成功" << endl;
		}
		else{
			cout << "是不是还没有输完？？"<<endl;
		}
	}
	return 0;
}


