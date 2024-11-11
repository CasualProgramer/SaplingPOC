#ifndef ast_h
#define ast_h

#include <iostream>
#include <string>
#include <vector>

enum class nodeType {
	_if,
	_else,
	_while,
	variable,
	function,
	print,
	input,
	loop,
	_return,
	close,
	newFile,
	condition,
	location,
	reservedFunc,
	_array,
	array_contents,
	map_keys,
	map,
	alreadyVar
};
class node {
public:
	nodeType type;
	std::vector<node> innerNodes;
	size_t i;
	std::vector<std::string> values;
	size_t v;
};



#endif