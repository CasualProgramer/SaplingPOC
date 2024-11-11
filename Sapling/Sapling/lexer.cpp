#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

#include"tokens.h"
#include"parser.h"

bool inString = false;

std::vector<Token> tokenize(const std::string& str) {
	std::string buf;
	std::vector<Token> tokens;
    std::string matsInString;
	for (size_t i = 0; i < str.length(); i++) {
		char c = str.at(i);

		if (isalpha(c)) {
			buf.clear();

			buf.push_back(c);
			i++;
			while (i < str.length() && (isalnum(str.at(i) ) ) ) {
				if (!isspace(str.at(i))) {
					buf.push_back(str.at(i));
				}
				i++;
			}
			i--;
            if (!inString) {
                if (buf == "return") {
                    Token t;
                    t.type = TokenType::_return;
                    t.value = "return";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "true" || buf == "false") {
                    Token t;
                    t.type = TokenType::_bool;
                    t.value = buf;
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "if") {
                    Token t;
                    t.type = TokenType::_if;
                    t.value = "if";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "else") {
                    Token t;
                    t.type = TokenType::_else;
                    t.value = "else";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "print") {
                    Token t;
                    t.type = TokenType::_print;
                    t.value = "print";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "string" || buf == "str") {
                    Token t;
                    t.type = TokenType::str;
                    t.value = "std::string";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "int") {
                    Token t;
                    t.type = TokenType::_int;
                    t.value = "int";
                    std::cout << "int text" << std::endl;
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "float") {
                    Token t;
                    t.type = TokenType::_float;
                    t.value = "float";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "bool") {
                    Token t;
                    t.type = TokenType::boolText;
                    t.value = "bool";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "input") {
                    Token t;
                    std::cout << "input" << std::endl;
                    t.type = TokenType::input;
                    t.value = "input";
                    tokens.push_back(t);
                    buf.clear();
                }
                else if (buf == "while") {
                    Token t;
                    t.type = TokenType::_while;
                    t.value = "while";
                    tokens.push_back(t);
                    buf.clear();
                }
                else {
                    Token t;
                    t.type = TokenType::identifier;
                    t.value = buf;
                    tokens.push_back(t);
                }
            }
            else if (inString) {
                matsInString = matsInString + buf;
            }
		}
		else if (isdigit(c)){
			buf.clear();

			buf.push_back(c);
			i++;
			while (i < str.length() && (isdigit(str.at(i)))) {
				if (!isspace(str.at(i))) {
					buf.push_back(str.at(i));
				}
				i++;
			}
			i--;
            if (!inString) {
			    Token t;
			    t.type = TokenType::int_lit;
			    t.value = buf;
			    tokens.push_back(t);
			    buf.clear();
                std::cout << t.value << std::endl;
            }
            else {
                matsInString = matsInString + buf;
            }
		}
        else if ((c == ';' || c == '\n') && !inString) {
            Token t;
            t.type = TokenType::semi;
            t.value = "semi";
            tokens.push_back(t);
        }
        else if (c == '(' && !inString) {
            Token t;
            t.type = TokenType::leftBrack;
            t.value = "(";

            tokens.push_back(t);
        }
        else if (c == ')' && !inString) {
            Token t;
            t.type = TokenType::rightBrack;
            t.value = ")";

            tokens.push_back(t);
        }
        else if (c == '{' && !inString) {
            Token t;
            t.type = TokenType::leftCurly;
            t.value = "{";
            tokens.push_back(t);
        }
        else if (c == '}' && !inString) {
            Token t;
            t.type = TokenType::rightCurly;
            t.value = "}";
            tokens.push_back(t);
        }
        else if (c == '=' && !inString) {
            Token t;
            t.type = TokenType::equalSign;
            t.value = "=";
            tokens.push_back(t);
        }
        else if (c == '~' && !inString) {
            Token t;
            t.type = TokenType::curlDash;
            t.value = "~";
            tokens.push_back(t);
        }
        else if (c == '+' && !inString) {
            Token t;
            t.type = TokenType::add;
            t.value = "+";
            tokens.push_back(t);
        }
        else if (c == '*' && !inString) {
            Token t;
            t.type = TokenType::mul;
            t.value = "*";
            tokens.push_back(t);
        }
        else if (c == '/' && !inString) {
            Token t;
            t.type = TokenType::div;
            t.value = "/";
            tokens.push_back(t);
        }
        else if (c == '-' && !inString) {
            Token t;
            t.type = TokenType::sub;
            t.value = "-";
            tokens.push_back(t);
        }
        else if (c == '"') {
            inString = !inString;
            Token t;
            t.type = TokenType::doubleQoutation;
            t.value = '"';

            if (!inString && matsInString != "\0") {
                Token p;
                p.type = TokenType::matsInString;
                p.value = matsInString;
                tokens.push_back(p);
               // std::cout << matsInString << std::endl;
                matsInString = "\0";
            }

            tokens.push_back(t);
        }
        else if (c == '.' && !inString) {
            Token t;
            t.type = TokenType::dot;
            t.value = ".";
            tokens.push_back(t);
        }
        else if (c == '<' && !inString) {
            Token t;
            t.type = TokenType::lessThan;
            t.value = "<";
            tokens.push_back(t);
        }
        else if (c == '<' && !inString) {
            Token t;
            t.type = TokenType::lessThan;
            t.value = "<";
            tokens.push_back(t);
        }
        else if (c == '>' && !inString) {
            Token t;
            t.type = TokenType::greaterThan;
            t.value = ">";
            tokens.push_back(t);
        }
        else if (c == '&' && !inString) {
            Token t;
            t.type = TokenType::andpersent;
            t.value = "&";
            tokens.push_back(t);
        }
        else if (c == '^' && !inString) {
            Token t;
            t.type = TokenType::superlink;
            t.value = "^";
            tokens.push_back(t);
        }
        else if (c == '$' && !inString) {
            Token t;
            t.type = TokenType::dolar;
            t.value = "$";
            tokens.push_back(t);
        }
        else if (c == '|' && !inString) {
            Token t;
            t.type = TokenType::lbutStright;
            t.value = "|";
            tokens.push_back(t);
        }
        else if (c == '%' && !inString) {
            Token t;
            t.type = TokenType::persent;
            t.value = "%";
            tokens.push_back(t);
        }
        else if (c == '#' && !inString) {
            Token t;
            t.type = TokenType::hastag;
            t.value = "#";
            tokens.push_back(t);
        }
        else if (c == '!' && !inString) {
            Token t;
            t.type = TokenType::exclimation;
            t.value = "!";
            tokens.push_back(t);
        }
        else if (c == '`' && !inString) {
            Token t;
            t.type = TokenType::badqoutes;
            t.value = "`";
            tokens.push_back(t);
        }
        else if (c == '[' && !inString) {
            Token t;
            t.type = TokenType::leftSquareBracket;
            t.value = "[";
            tokens.push_back(t);
        }
        else if (c == ']') {
            Token t;
            t.type = TokenType::rightSquareBracket;
            t.value = "]";
            tokens.push_back(t);
        }
        else if (c == '_' && !inString) {
            Token t;
            t.type = TokenType::underscore;
            t.value = "_";
            tokens.push_back(t);
        }
        else if (!isspace(c) && !inString) {
            buf.clear();
        }
        else {
            if (inString && c != '\n') {
                if (c != '"') {
                    matsInString += c;
                    if (!isspace) {
                        buf.clear();
                    }
                   // std::cout << matsInString << std::endl;
                }
            }
        }
	}
	return tokens;
}

void openFile(std::string filePath) {
    std::cout << "tokenising......" << std::endl;
	std::ifstream file (filePath);
	if (!file.is_open()) {
		std::cerr << "ERROR, FILE NOT FOUND: " << filePath << std::endl;
	}
	std::stringstream contents;
	contents << file.rdbuf();

	eat(tokenize(contents.str()));
}