//
//  regex.cpp
//  compiler
//
//  Created by han.jin on 15/11/25.
//  Copyright © 2015年 han.jin. All rights reserved.
//
#include "stdafx.h"
#include "regex.h"

using namespace std;

typedef struct NodeTree{
	struct NodeTree *node1;
	struct NodeTree *node2;
	struct NodeTree *p;
	char token;
} NodeTree;

stack<NodeTree> NodeStack;
stack<char> mark;

NodeTree* equalpoint(NodeTree node){
	NodeTree *re = new NodeTree;
	re->node1 = node.node1;
	re->node2 = node.node2;
	re->p = node.p;
	re->token = node.token;
	return re;
}
void markdo(char a){
	switch (a) {
	case '(':
		mark.push(a);
		break;
	case '*':{
				 NodeTree *node = new NodeTree;
				 node->p = NULL;
				 node->node1 = equalpoint(NodeStack.top());
				 node->node2 = NULL;
				 node->token = '*';
				 NodeStack.pop();
				 NodeStack.push(*node);
				 break;
	}

	case ')':
		while (mark.top() != '('){
			markdo(mark.top());
		}
		mark.pop();
		break;

	case '|':{
				 mark.pop();
				 NodeTree *node = new NodeTree;
				 node->p = NULL;
				 node->node2 = equalpoint(NodeStack.top());
				 NodeStack.pop();
				 node->node1 = equalpoint(NodeStack.top());
				 NodeStack.pop();
				 node->token = '|';
				 NodeStack.push(*node);
				 break;
	}
	case '+':{
				 mark.pop();
				 NodeTree *node = new NodeTree;
				 node->p = NULL;
				 node->node2 = equalpoint(NodeStack.top());
				 NodeStack.pop();
				 node->node1 = equalpoint(NodeStack.top());
				 NodeStack.pop();
				 node->token = '+';
				 NodeStack.push(*node);
				 break;
	}
	default:
		break;
	}
}

void creattree(string in){
	istringstream iss(in);
	char c;
	iss >> c;
	while (iss){
		if (c == '+' || c == '|' || c == '*' || c == '(' || c == ')'){
			if (c == '|'){
				while (!mark.empty() && mark.top() == '+') {
					markdo(mark.top());
				}
				mark.push('|');
				iss >> c;
				continue;
			}
			markdo(c);
		}
		else{
			NodeTree *node = new NodeTree;
			node->p = NULL;
			node->node1 = NULL;
			node->node2 = NULL;
			node->token = c;
			NodeStack.push(*node);
		}
		if (c == '(') {
			iss >> c;
			continue;
		}
		if (iss >> c){
			if (c != '*'&&c != '|'&&c != ')')
				mark.push('+');
		}
		else break;
	}
	while (!mark.empty()){
		markdo(mark.top());
	}
}


