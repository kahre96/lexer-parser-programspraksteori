#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>

class node {

	void add(node* child) {
		children.push_back(child);
	}

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
