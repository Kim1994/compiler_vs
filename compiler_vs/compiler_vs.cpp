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
	return 0;
}


