#include "stdafx.h"
#include "enfa.h"
#include "regex.h"


enfanode *Start=NULL;
enfanode *End = NULL;

vector<enfanode*> or(NodeTree *nodetree, vector<enfanode*> N1, vector<enfanode*> N2){
	enfanode *s = new enfanode;
	enfanode *e = new enfanode;
	enfaedge *lin1 = new enfaedge;
	enfaedge *lin2 = new enfaedge;
	enfaedge *lout1 = new enfaedge;
	enfaedge *lout2 = new enfaedge;
	s->in.push_back(lin1);
	s->in.push_back(lin2);
	s->FinalStatus = 0;
	lin1->start = s;
	lin1->end = N1[0];
	lin1->match = '\0';
	lin2->start = s;
	lin2->end = N2[0];
	lin2->match = '\0';
	e->in.push_back(lout1);
	e->in.push_back(lout2);
	e->FinalStatus = 1;
	lout1->start = N1[1];
	lout1->end = e;
	lout1->match = '\0';
	lout2->start = N2[1];
	lout2->end = e;
	lout2->match = '\0';
	N1[1]->FinalStatus = 0;
	N2[1]->FinalStatus = 0;
	vector<enfanode*> re;
	re.push_back(s);
	re.push_back(e);
	return re;
}
vector<enfanode*> loop(NodeTree *nodetree, vector<enfanode*> N1){
	enfanode *s = new enfanode;
	enfaedge *lin = new enfaedge;
	enfaedge *lout = new enfaedge;
	s->out.push_back(lin);
	s->in.push_back(lout);
	s->FinalStatus = 1;
	lin->start = s;
	lin->end = N1[0];
	lin->match = '\0';
	lout->start = N1[1];
	lout->end = s;
	lout->match = '\0';
	N1[1]->FinalStatus = 0;
	vector<enfanode*> re;
	re.push_back(s);
	re.push_back(s);
	return re;
}
vector<enfanode*> add(NodeTree *nodetree, vector<enfanode*> N1, vector<enfanode*> N2){
	enfaedge *l = new enfaedge;
	l->start = N1[1];
	l->end = N2[0];
	l->match = '\0';
	N1[1]->out.push_back(l);
	N2[0]->in.push_back(l);
	N1[1]->FinalStatus = 0;
	vector<enfanode*> re;
	re.push_back(N1[0]);
	re.push_back(N2[1]);
	return re;
}
vector<enfanode*> other(NodeTree *nodetree){
	enfanode *s = new enfanode;
	enfanode *e = new enfanode;
	enfaedge *l = new enfaedge;
	l->start = s;
	l->end = e;
	l->match = nodetree->token;
	s->FinalStatus = 0;
	s->out.push_back(l);
	e->FinalStatus = 1;
	e->in.push_back(l);
	vector<enfanode*> re;
	re.push_back(s);
	re.push_back(e);
	return re;
}

vector<enfanode*> createnfa(NodeTree *nodetree){
	if (nodetree != NULL){
		vector<enfanode*> N1=createnfa(nodetree->node1);
		vector<enfanode*> N2=createnfa(nodetree->node2);
		switch (nodetree->token)
		{
		case '+':
			return add(nodetree,N1,N2);
			break;
		case '|':
			return or(nodetree, N1, N2);
			break;
		case'*':
			return loop(nodetree, N1);
			break;
		default:
			return other(nodetree);
			break;
		}
	}
	vector<enfanode*> re;
	return re;
}