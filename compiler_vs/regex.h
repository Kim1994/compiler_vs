//
//  regex.hpp
//  compiler
//
//  Created by han.jin on 15/11/25.
//  Copyright © 2015年 han.jin. All rights reserved.
//

#ifndef regex_h
#define regex_h

#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

typedef struct NodeTree{
	struct NodeTree *node1;
	struct NodeTree *node2;
	struct NodeTree *p;
	char token;
} NodeTree;

NodeTree* creattree(string in);

#endif /* regex_hpp */
