#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>

struct node {
	void add(node* child) {
		children.push_back(child);
	}
	void print();
	virtual std::string getname();

	virtual bool evaluate(std::string::iterator& first, std::string::iterator last) {
		return true;
	}
	int generation =0;
	std::vector<node*> children;
};

struct pattern_node:node {
	std::string getname() override;
};

struct str_node : node {
	str_node(std::string s):ch(s){}
	std::string getname() override;
	std::string ch;
};

struct or_node : node {
	or_node(node* str1, node* str2) {
		add(str1);
		add(str2);
	}
	std::string getname() override;
};

struct star_node : node {
	star_node(std::string s):ch(s) {}
	std::string ch;
	std::string getname() override;
};
struct counter_node : node {
	counter_node(std::string s) :ch(s) {}
	std::string ch;
	int repeats = 1;
	void setcounter(int count);
	std::string getname() override;
};
struct group_node : node {
	
	
	
	
	std::string getname() override;
};


#endif
