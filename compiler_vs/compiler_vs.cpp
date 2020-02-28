// compiler_vs.cpp : �������̨Ӧ�ó������ڵ㡣
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
			cout << "ƥ��ʧ��" << endl;
			flag = -1;
			break;
		}
	}
	if (flag != -1)
	{
		if (start->FinalStatus == true){
			cout << "ƥ��ɹ�" << endl;
		}
		else{
			cout << "�ǲ��ǻ�û�����ꣿ��"<<endl;
		}
	}
	return 0;
}


