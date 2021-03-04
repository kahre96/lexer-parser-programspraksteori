#include "node.h"
#include <iostream>

void node::print() {
	for (int i = 0; i < generation; i++) {
		std::cout << "    ";
	}
	std::cout << this->getname() << std::endl;
	for (auto child : children) {
		child->generation = this->generation + 1;
		child->print();
	}
}
std::string node::match = "";
int node::groupcounter = 0;
std::vector<std::string> node::groups;

std::string node::getname() {
	return "basenode";
}
void node::set_group(int n)
{
	groupnumber = n;
	for (auto child : children) {
		child-> set_group(n);
	}

}
void node::view_match() {
	std::cout <<"Resultat av matchningen: " << match << std::endl;
}

void node::set_ignore_status()
{
	ignore_status = true;

	for (auto child : children) {
		child->set_ignore_status();
	}
}

std::string pattern_node::getname()  {
	return "pattern_node";
}

std::string str_node::getname() {
	return "str_node";
}

std::string or_node::getname() {
	return "or_node";
}

std::string star_node::getname()
{
	return "star_node";
}

void star_node::setbreak(std::string c)
{
	breakchar = c[0];
}

void counter_node::setcounter(int count)
{
	repeats = count;
}

std::string counter_node::getname()
{
	return "counter_node(" + std::to_string(repeats)+")";
}

std::string group_node::getname()
{
	return "group_node("+ std::to_string(groupnumber) +")";
}

std::string expr_node::getname()
{
	return "expr_node";
}

std::string subexpr_node::getname()
{
	return "subexpr_node";
}

void whichgroup_node::setcounter(int count)
{
	counter = count;
}

std::string whichgroup_node::getname()
{
	return "whichgroup_node("+ std::to_string(counter) +")";
}

std::string ignore_node::getname()
{
	return "ignore_node";
}

std::string any_node::getname()
{
	return "any_node";
}

std::string char_node::getname()
{
	return "char_node(" + ch + ")";
}
