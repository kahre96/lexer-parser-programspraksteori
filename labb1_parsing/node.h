#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>

struct node {
	void add(node* child) {
		children.push_back(child);
	}

	virtual bool evaluate(std::string::iterator& first, std::string::iterator last) {
		return true;
	}

	std::vector<node*> children;
};

struct pattern_node:node {

};

struct str_node : node {
	str_node(std::string s):ch(s){}

	std::string ch;
};

struct or_node : node {

};



#endif
