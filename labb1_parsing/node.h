#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>
#include <iostream>

using it = std::string::iterator;


struct node {
	void add(node* child) {
		children.push_back(child);
	}

	//printar funktionen
	void print();

	//visar mösntermatchningen
	void view_match();

	//sätter ignore status för alla barn \I
	void set_ignore_status();

	//hämtar typen av nod för utskrift
	virtual std::string getname();

	//sätter gruppnummer för alla gruppens barn
	void set_group(int n);

	virtual bool evaluate(it& first, it last) {
		for (auto ch : children) {
			auto result = ch->evaluate(first, last);
			if (!result) {
				return false;
			}

		}
		return true;
	}
	int groupnumber = 0; // gruppnummer för ()  \O{n}
	static int groupcounter; // räknar för att hålla koll på antalet grupper
	static std ::string match; // matchning
	static std::vector<std::string> groups; // vector för att lagra matchningar från olika paranteser
	int generation =0; // nodens generation för utskrift
	std::vector<node*> children; // nodens barn
	bool ignore_status= false; // ignore status \I
	
};

struct pattern_node:node {
	std::string getname() override;
	pattern_node() {
		groups.push_back("");
	}
	void set_input(std::string in){
		input = in;
	}

	bool evaluate() {
		auto first = input.begin();
		auto last = input.end();
		return evaluate(first, last);
	}
	bool evaluate(it& first,it  last) override {
		while (!node::evaluate(first, last)) {
			if (first != last) {
				++first;
			}
			groups[groupcounter] = "";
			match = "";
			if (first == last) {
				return false;
			}
			
			
		}
		int i = 0;
		for (auto g: groups) {
			std::cout << i <<" " << g << std::endl;
			i++;
		}
		return true;
	}
	


	std::string input;
};

struct str_node : node {
	str_node(std::string s):ch(s){}
	std::string getname() override;

	bool evaluate(it& first,it last) override {
		
		return node::evaluate(first, last);
	}
	std::string ch;
};

struct or_node : node {
	or_node(node* str1, node* str2) {
		add(str1);
		add(str2);
	}
	bool evaluate(it& first, it last) override{
		auto firstpath = children[0]->evaluate(first,last);
		if (firstpath)
			return true;
		auto secondpath = children[1]->evaluate(first, last);
		return secondpath;
	}
	std::string getname() override;
};

struct star_node : node {
	star_node(std::string s):ch(s) {
		breakchar = '¤';
	}
	std::string ch;
	std::string getname() override;
	void setbreak(std::string c);
	char breakchar;
	char check(it first) {
		return *first;
	}
	bool evaluate(it& first, it last) override {
		if (first == last) {
			return false;
		}
		bool status = false;
		
		while (children[0]->evaluate(first,last)) {
			
			if (first == last) {
				return true;
			}
			if (check(first) == breakchar) {
				return true;
			}
			
			status = true;
			
		}
		
		return status;
	}
};

struct counter_node : node {
	counter_node(std::string s) :ch(s) {}
	std::string ch;
	int repeats = 1;
	void setcounter(int count);
	std::string getname() override;
	bool evaluate(it& first, it last) override {

		for (int i=0; i < repeats; ++i) {
			if (!children[0]->evaluate(first, last)) {
				return false;
			}
			
		}
		
		return true;
	}

};

struct group_node : node {
	
	
	
	group_node() {
		groups.push_back("");
		groupcounter++;
		groupnumber = groupcounter;
	}
	std::string getname() override;
	bool evaluate(it& first, it last) override {

		set_group(groupnumber);
		return node::evaluate(first, last);
	}
};
struct expr_node : node {




	std::string getname() override;
};
struct subexpr_node : node {

	subexpr_node() {
		
	}


	std::string getname() override;
};
struct whichgroup_node : node {
	whichgroup_node(int count) : counter(count) {}

	//evlautate sätter match = paranteser(counter)


	int counter;
	void setcounter(int count);
	std::string getname() override;

	bool evaluate(it& first, it last) override {
		match = groups[counter];
		return true;
	}
};
struct ignore_node : node {

	

	bool evaluate(it& first, it last) override {
		set_ignore_status();
		return node::evaluate(first, last);
	}


	std::string getname() override;
};
struct any_node : node {



	bool evaluate(it& first, it last) override {
		match += *first;
		groups[groupnumber] += *first;
		first++;
		return true;
	}


	std::string getname() override;
};
struct char_node : node {

	char_node(std::string s): ch(s){}

	bool evaluate(it& first, it last) override {
		
		if (ignore_status) {

			if (tolower(*first) != tolower(*ch.begin())) {
				return false;
			}
		}
		else {
			if (*first != *ch.begin()) {
				return false;
			}
		}
		match += ch;
		groups[groupnumber] += ch;
		std::cout << match << std::endl;
		first++;
		
		
		
		return true;
	}
	std::string ch;

	std::string getname() override;
};


#endif

