#include<iostream>
#include<fstream>

#include"lexer.h"


using std::cout;
using std::endl;

std::string filePath;

int main(int i, char** c) {
	if (i > 1) {
		for (long l = 1; l <= i; l++) {
			if (l == 2) {
				std::string comandType = c[l - 1];
				if (comandType == "compile") {
					filePath = c[l];
					openFile(filePath + ".sap");
				}
			}
		}
	}
	else if (i == 1) {
		cout << "/////////Sapling Compiler////////////" << endl;
		cout << "(path)/(fileName).sap " << endl;
		std::cin >> filePath;
		openFile(filePath + ".sap");
	}
}