#include <iostream>
#include <vector>
#include<string>
#include <sstream>
#include<fstream>

#include"AST.h"
#include "main.h"
#include"lexer.h"


using std::vector;
using std::cout;
using std::endl;

std::string compileType = "app";

std::stringstream output;

bool thereMain = false;

void appCompile(vector<node> SyntaxTree) {
	output << "#include<iostream>\n#include<vector>\n#include<string>\n#include<fstream>\n";
	for (size_t i = 0; i < SyntaxTree.size(); i++) {
		if ((SyntaxTree[i].type == nodeType::variable || SyntaxTree[i].type == nodeType::alreadyVar) && SyntaxTree[i].innerNodes.size() == 0) {
			if (SyntaxTree[i].type != nodeType::alreadyVar) {
				output << SyntaxTree[i].values[1] << " ";
			}
			output << SyntaxTree[i].values[0] << " = " << SyntaxTree[i].values[2] << ";\n";
			
		}
		else if (SyntaxTree[i].type == nodeType::_array) {
			output << "std::vector<" << SyntaxTree[i].values[1] << "> " << SyntaxTree[i].values[0] << " {\n";
			output << SyntaxTree[i].innerNodes[0].values[0] << "\n};\n";
		}
		else if (SyntaxTree[i].type == nodeType::_return) {
			output << "return " << SyntaxTree[i].values[SyntaxTree[i].v - 1] << ";\n";
		}
		else if (SyntaxTree[i].type == nodeType::function) {
			if (SyntaxTree[i].values[0] == "main") {
				thereMain = true;
			}

			output << SyntaxTree[i].innerNodes[1].values[0] << " " << SyntaxTree[i].values[0] << "(";
			for (size_t v = 0; v < SyntaxTree[i].innerNodes[0].v; v++) {
				output << "auto " << SyntaxTree[i].innerNodes[0].values[v];
				if (v + 1 < SyntaxTree[i].innerNodes[0].v) {
					output << ",";
				}
			}
			output << ") " << "{\n";
		}
		else if ((SyntaxTree[i].type == nodeType::_if || SyntaxTree[i].type == nodeType::_while)/*  && (SyntaxTree[i].innerNodes.size() > 0)*/) {
			if (SyntaxTree[i].type == nodeType::_if) {
				output << "if ";
			}
			else if (SyntaxTree[i].type == nodeType::_while) {
				output << "while ";
			}
			else {
				std::cerr << "WRONG STATEMENT TYPE, ERROR";
			}

			if ((SyntaxTree[i].type == nodeType::_if || SyntaxTree[i].type == nodeType::_while)) {
				output << "(" << SyntaxTree[i].innerNodes[0].values[0] << ") {\n";
			}
		}
		else if (SyntaxTree[i].type == nodeType::print) {
			output << "std::cout << " << SyntaxTree[i].values[0] << " << std::endl;\n";
		}
		else if (SyntaxTree[i].type == nodeType::input && SyntaxTree[i].values.size() == 2) {
			output << SyntaxTree[i].values[1] << " " << SyntaxTree[i].values[0] << ";\n";
			output << "std::cin >> " << SyntaxTree[i].values[0] << ";\n";
		}
		else if (SyntaxTree[i].type == nodeType::_else) {
			output << "else {\n";
		}
		else if (SyntaxTree[i].type == nodeType::close) {
			output << "}\n";
		}
	}
}

int compile(vector<node> SyntaxTree) {
	std::cout << "compiling......" << std::endl;
	if (compileType == "app") {
		appCompile(SyntaxTree);
		std::cout << "making the required files....." << std::endl;
		std::string outputPath = filePath + ".cpp";
		cout << outputPath << endl;

		if (!thereMain) {
			output << "int main() {return 0;}\n";
		}

		std::ofstream outputFile(outputPath);
		outputFile << output.str();
		outputFile.close();
		cout << output.str();

		std::string comandToBin("g++ ");
		comandToBin += outputPath + " -o " + filePath + ".exe";
		system(comandToBin.c_str());
		
		std::string removeCppFile("del /f ");
		removeCppFile += '"' + outputPath + '"';
		system(removeCppFile.c_str());
	}

	return 0;
}
