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
	return 0;
}


