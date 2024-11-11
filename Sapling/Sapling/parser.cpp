#include<iostream>
#include<vector>
#include<sstream>

#include"tokens.h"
#include"compiler.h"
#include"AST.h"
#include"parser.h"

using std::vector;
using std::cout;
using std::endl;

bool inFunc = false;

int reservedCords = -1;

vector<varIdentifire> vars;
vector<varIdentifire> arrays;

std::string location = "\0";

varIdentifire isDeclaredVar(std::string var_name, std::string lication) {
	//bool alreadyVar = false;
	varIdentifire varData;

	varData.alreadyVar = false;

	for (int i = 0; i < vars.size(); i++) {
		if (vars[i].name == var_name && (vars[i].location == lication || vars[i].location == "\0")) {
			varData.alreadyVar = true;
			varData.name = var_name;
			varData.location = lication;
			varData.type = vars[i].type;
			break;
		}
	}

	return varData;
}

int eat(vector<Token> tokens) {
	std::cout << "parsering......" << std::endl;

	vector<node> SyntaxTree;
	vector<std::string> toBeClosed;

	int tbc = toBeClosed.size();

	int n = SyntaxTree.size();
	//cout << "NodeCount: " << n << endl;

	node reservedFunc;

	for (size_t i = 0; i < tokens.size(); i++) {
		if ((tokens[i].type == TokenType::_return && (i + 2 < tokens.size() && tokens[i + 1].type == TokenType::int_lit) && tokens[i + 2].type == TokenType::semi)) {
			node t;
			t.type = nodeType::_return;
			t.v++;
			t.values.push_back(tokens[i + 1].value);
			t.i++;
			if (location != "\0") {
				//cout << reservedCords << endl;
				if (reservedCords >= 0 && SyntaxTree[reservedCords].type == nodeType::reservedFunc) {
					SyntaxTree[reservedCords].type = nodeType::function;
					SyntaxTree[reservedCords].innerNodes[1].values[0] = "int";
					reservedCords = -1;
					//cout << "func_name: " << SyntaxTree[reservedCords].values[0] << " type: " << SyntaxTree[reservedCords].innerNodes[1].values[0] << endl;
				}
				else if (reservedCords >= 0 && SyntaxTree[reservedCords].type != nodeType::reservedFunc){
					std::cerr << "CAN'T FIND THE DEFINED FUNCTION, ERROR 404, AT CORDS: " << reservedCords;
				}
				SyntaxTree.push_back(t);
			}
			else {
				std::cerr << "USE RETURN IN A FUNCTION OR A STATEMENT, ERROR 404";
			}
		}

		else if (tokens[i].type == TokenType::_print) {
			node print;
			print.type = nodeType::print;

			i ++;
			std::stringstream contents;
			while (tokens[i].type != TokenType::semi && i < tokens.size()) {
				contents << tokens[i].value;
				i++;
			}
			print.values.push_back(contents.str());

			SyntaxTree.push_back(print);
		}

		else if ((tokens[i].type == TokenType::_if || tokens[i].type == TokenType::_while)) {
			//cout << tokens[i].value << endl;

			node sate;
			if (tokens[i].type == TokenType::_if) {
				sate.type = nodeType::_if;
			}
			else {
				sate.type = nodeType::_while;
			}
			i++;
			node in;
			sate.innerNodes.push_back(in);
			sate.innerNodes[0].type = nodeType::condition;

			if (tokens[i].type == TokenType::_bool) {
				sate.innerNodes[0].values.push_back(tokens[i].value);
			}
			else if (tokens[i].type == TokenType::curlDash) {
				std::stringstream condition;
				i++;
				while ((tokens[i].type != TokenType::leftCurly && tokens[i].type != TokenType::semi) && i < tokens.size()) {
					condition << tokens[i].value;

					i++;
				}

				sate.innerNodes[0].values.push_back(condition.str());
			}

			/*
			if (location != "\0") {
				sate.innerNodes[1].type = nodeType::location;
				sate.i++;
				sate.innerNodes[1].values[0] = location;
			}*/

			location = "statement";
			toBeClosed.push_back(location);
			tbc++;
			SyntaxTree.push_back(sate);
		}

		else if (tokens[i].type == TokenType::_else) {
			node _else;
			_else.type = nodeType::_else;

			location = "else";
			toBeClosed.push_back(location);
			tbc++;

			SyntaxTree.push_back(_else);
		}
		//func or var or newFile stuff
		else if (tokens[i].type == TokenType::identifier) {
			node fvn;

			if (tokens[i].value != "\0") {
				fvn.values.push_back(tokens[i].value);

				//cout << fvn.values[0] << endl;
			}
			i++;
			bool func = false;

			//vars or input or array or maps
			if (tokens[i].type == TokenType::equalSign) {
				func = false;

				varIdentifire var = isDeclaredVar(fvn.values[0], location);
				
				if (var.alreadyVar){
					fvn.type = nodeType::alreadyVar;
				}
				//cout << tokens[i + 1].value << " " << fvn.values[0] << ";\n" << "cin >> " << fvn.values[0] << endl;

				if ((tokens[i + 1].type == TokenType::_int || tokens[i + 1].type == TokenType::_bool || tokens[i + 1].type == TokenType::_float || tokens[i + 1].type == TokenType::str)) {
					fvn.type = nodeType::input;
					i++;
					if ((tokens[i + 1].type == TokenType::input)) {
						fvn.values.push_back(tokens[i].value);
					}
				}
				else if (tokens[i + 1].type == TokenType::leftCurly) {
					node arrayContents;
					arrayContents.v = 0;
					fvn.type = nodeType::_array;
					i++;
					if (tokens[i + 1].type == TokenType::int_lit) {
						fvn.values.push_back("int");

					}
					else if (tokens[i + 1].type == TokenType::_bool || tokens[i + 1].type == TokenType::curlDash) {
						fvn.values.push_back("bool");

					}
					else if (tokens[i + 1].type == TokenType::doubleQoutation) {
						fvn.values.push_back("std::string");
					}
					i++;
					while (tokens[i].type != TokenType::rightCurly) {
						std::stringstream contentsValue;
						while (tokens[i].type != TokenType::comma && tokens[i].type != TokenType::rightCurly) {
							if (tokens[i].value != "\0" && tokens[i].type != TokenType::rightCurly) {
								if (tokens[i + 1].type == TokenType::rightCurly) {
									contentsValue << tokens[i].value;
								}
								else {
									contentsValue << tokens[i].value << ", ";
								}
								i++;
							}
						}
						arrayContents.values.push_back(contentsValue.str());
						arrayContents.v++;
					}
					arrayContents.type = nodeType::array_contents;
					fvn.innerNodes.push_back(arrayContents);
				}
				else {
					if (fvn.type != nodeType::alreadyVar) {
						fvn.type = nodeType::variable;
					}

					varIdentifire varTest = isDeclaredVar(tokens[i+1].value, location);

					if (tokens[i + 1].type == TokenType::int_lit) {
						fvn.values.push_back("int");
						cout << "int" << endl;
					
					}
					else if (tokens[i + 1].type == TokenType::_bool || tokens[i + 1].type == TokenType::curlDash) {
						fvn.values.push_back("bool");
					
					}
					else if (tokens[i + 1].type == TokenType::doubleQoutation) {
						fvn.values.push_back("std::string");
					}
					else if (varTest.alreadyVar) {
						fvn.values.push_back(varTest.type);
					}
					i++;
					std::stringstream varValue;
					while ((tokens[i].type != TokenType::semi && i < tokens.size())) {
						if (tokens[i].type != TokenType::curlDash) {
							varValue << tokens[i].value;
						}
						i++;
					}
					fvn.values.push_back(varValue.str());
					if (!var.alreadyVar) {
						varIdentifire varData;
						varData.name = fvn.values[0];
						varData.type = fvn.values[1];
						varData.location = location;
						vars.push_back(varData);
					}
				}
				
			}

			//function
			if (tokens[i].type == TokenType::leftBrack) {
				fvn.type = nodeType::function;

				location = "func";
				toBeClosed.push_back(location);
				tbc++;
				cout << tbc << std::endl;
				func = true;
				i++;

				node in;
				while (tokens[i].type != TokenType::rightBrack) {
					in.type = nodeType::condition;
					in.v = 0;
					in.values[in.v] = tokens[i].value;

					in.v++;
					i++;
				}
				fvn.innerNodes.push_back(in);

				reservedFunc = fvn;
				reservedFunc.type = nodeType::reservedFunc;
				node rin;
				rin.values.push_back("void");
				reservedFunc.innerNodes.push_back(rin);
				SyntaxTree.push_back(reservedFunc);
				reservedCords = SyntaxTree.size() - 1;
				//cout << reservedCords << "<---- func cords" << endl;
			}

			//newFile node thing
			if (tokens[i].type == TokenType::leftCurly) {
				location = "newFile";
				fvn.type = nodeType::newFile;
				func = false;

				toBeClosed.push_back(location);
				tbc++;
				cout << tbc << std::endl;
			}

			if (!func) {
				SyntaxTree.push_back(fvn);
			}
		}

		else if (tokens[i].type == TokenType::rightCurly){
			if (tbc > 0) {
				toBeClosed.pop_back();
				tbc--;
			}

			if (reservedCords >= 0 && location == "func" && SyntaxTree[reservedCords].type == nodeType::reservedFunc) {
				if (SyntaxTree[reservedCords].innerNodes[1].values[0] != "\0") {
					SyntaxTree[reservedCords].type = nodeType::function;
					SyntaxTree[reservedCords].innerNodes[1].values[0] = "void";
					//cout << "func_name: " << SyntaxTree[reservedCords].values[0] << "type: " << SyntaxTree[reservedCords].innerNodes[1].values[0] << endl;
					reservedCords = -1;
				}
			}
			node t;
			t.type = nodeType::close;
			SyntaxTree.push_back(t);
		}

	}
	compile(SyntaxTree);
	return 0;
}

