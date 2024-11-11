#ifndef parser_h
#define parser_h

#include<iostream>
#include <vector>

#include "tokens.h"
class varIdentifire {
public:
	std::string type;
	std::string name;
	std::string location;
	bool alreadyVar;
};

int eat(std::vector<Token> tokens);

#endif