#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>

class node {

	

	virtual bool evaluate(std::string::iterator& first, std::string::iterator last) {

	}

	std::vector<node*> children;
};

class pattern_node:node {

};

class str_node : node {

};

class or_node : node {

};



#endif
