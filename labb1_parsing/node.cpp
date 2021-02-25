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

std::string node::getname() {
	return "basenode";
}

std::string pattern_node::getname()  {
	return "pattern_node";
}

std::string str_node::getname() {
	return "str_node(" + ch + ")";
}

std::string or_node::getname() {
	return "or_node";
}

std::string star_node::getname()
{
	return "star_node("+ ch + ")";
}

void counter_node::setcounter(int count)
{
	repeats = count;
}

std::string counter_node::getname()
{
	return "counter_node("+ch+", " + std::to_string(repeats)+")";
}
