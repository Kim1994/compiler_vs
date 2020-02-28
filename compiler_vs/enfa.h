#ifndef enfa_h
#define enfa_h


#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct enfanode;
typedef struct enfaedge{
	string match;
	enfanode *start;
	enfanode *end;
} enfaedge;

typedef struct enfanode{
	vector<enfaedge*> in;
	vector<enfaedge*> out;
	bool FinalStatus;
} enfanode;




vector<enfanode*> createnfa(NodeTree *nodetree);
enfanode* enfa2nfa(vector<enfanode*> enfa);
enfanode* nfa2dfa(enfanode* nfa);

#endif