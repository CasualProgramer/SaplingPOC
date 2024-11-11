#ifndef compiler_h
#define compiler_h

#include <iostream>
#include<vector>

#include "AST.h"

int compile(std::vector<node> SyntaxTree);
extern std::string compileType;

#endif
