#include "stdafx.h"
#include "enfa.h"
#include "regex.h"

enfanode* enfa2nfa(vector<enfanode*> enfa)
{
	stack<enfanode*> nodeStack;
	nodeStack.push(enfa[0]);
	stack<enfanode*> unvaluable;
	vector<enfanode*> nodelist;
	nodelist.push_back(enfa[0]);
	while (!nodeStack.empty())
	{
		enfanode* temp = nodeStack.top();
		nodeStack.pop();
		unvaluable.push(temp);
		while (!unvaluable.empty())
		{
			enfanode* valuable = unvaluable.top();
			unvaluable.pop();
			if (valuable->out.size() == 0)
			{
				continue;
			}
			for (vector<enfaedge*>::iterator it = valuable->out.begin(); it != valuable->out.end();it++)
			{
				enfaedge* edgetemp = *it;
				if (edgetemp->match != ""){
					if (edgetemp->start != temp){
						enfaedge* newedge = new enfaedge;
						newedge->start = temp;
						newedge->end = edgetemp->end;
						newedge->match = edgetemp->match;
						temp->out.push_back(newedge);
						newedge->end->in.push_back(newedge);
					}
					if (find(nodelist.begin(), nodelist.end(), edgetemp->end) == nodelist.end()){
						nodeStack.push(edgetemp->end);
						nodelist.push_back(edgetemp->end);
					}
				}
				else{
					enfanode* nodetemp = edgetemp->end;
					if (nodetemp->FinalStatus == true){
						temp->FinalStatus = true;
					}
					unvaluable.push(nodetemp);
				}
			}
		}
		vector<enfaedge*>::iterator it = temp->out.begin();
		while (it != temp->out.end())
		{
			enfaedge* edgetemp = *it;
			if (edgetemp->match == ""){
				it = temp->out.erase(it);
			}
			else{
				it++;
			}
		}
	}
	return enfa[0];
}

enfanode* nfa2dfa(enfanode* nfa)
{
	stack<enfanode*> L;
	vector<vector<enfanode*>> D;
	L.push(nfa);
	vector<enfanode*> starttemp;
	starttemp.push_back(nfa);
	D.push_back(starttemp);
	map<vector<enfanode*>, enfanode*> nodelist2node;
	while (!L.empty())
	{
		enfanode* temp = L.top();
		L.pop();
		map<string, vector<enfanode*>> charmap;
		for (vector<enfaedge*>::iterator it = temp->out.begin(); it != temp->out.end(); it++)
		{
			enfaedge* edgetemp = *it;
			charmap[edgetemp->match].push_back(edgetemp->end);
		}
		map<string, vector<enfanode*>>::iterator iter;
		for (iter = charmap.begin(); iter != charmap.end(); iter++)
		{
			vector<enfanode*> nodelisttemp=iter->second;
			if (find(D.begin(), D.end(), nodelisttemp) == D.end()){
				D.push_back(nodelisttemp);
				if (iter->second.size() == 1){
						L.push(nodelisttemp[0]);
				}
				else{
					enfanode* newnode = new enfanode;
					newnode->FinalStatus = false;
					for (vector<enfanode*>::iterator it = nodelisttemp.begin(); it != nodelisttemp.end(); it++)
					{
						enfanode* nodetemp = *it;
						for (vector<enfaedge*>::iterator itedge = nodetemp->out.begin(); itedge != nodetemp->out.end(); itedge++)
						{
							enfaedge* edgeintemp = *itedge;
							newnode->out.push_back(edgeintemp);
							edgeintemp->start = newnode;
						}
						if (nodetemp->FinalStatus == true)
							newnode->FinalStatus = true;
						vector<enfaedge*>::iterator itdel = temp->out.begin();
						while (itdel != temp->out.end())
						{
							enfaedge* edgetemp = *itdel;
							if (edgetemp->end == nodetemp){
								itdel = temp->out.erase(itdel);
							}
							else{
								itdel++;
							}
						}
					}
					enfaedge* newedge = new enfaedge;
					newedge->start = temp;
					newedge->match = iter->first;
					newedge->end = newnode;
					temp->out.push_back(newedge);
					nodelist2node[nodelisttemp] = newnode;
					L.push(newnode);
				}
			}
			else{
				if (iter->second.size() != 1){
					enfaedge* newedge = new enfaedge;
					newedge->start = temp;
					newedge->match = iter->first;
					newedge->end = nodelist2node[nodelisttemp];
					temp->out.push_back(newedge);
					enfanode* newnode = new enfanode;
					for (vector<enfanode*>::iterator it = nodelisttemp.begin(); it != nodelisttemp.end(); it++)
					{
						enfanode* nodetemp = *it;
						vector<enfaedge*>::iterator itdel = temp->out.begin();
						while (itdel != temp->out.end())
						{
							enfaedge* edgetemp = *itdel;
							if (edgetemp->end == nodetemp){
								itdel = temp->out.erase(itdel);
							}
							else{
								itdel++;
							}
						}
					}
				}
			}
		}
	}
	return nfa;
}