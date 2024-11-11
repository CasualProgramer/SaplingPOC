#ifndef tokens_h
#define tokens_h

#include<iostream>
#include <string>

enum class TokenType {
	_return,
	makeType,
	int_lit,
	double_lit,
	_bool,
	semi,
	_if,
	_else,
	leftCurly,
	rightCurly,
	identifier,
	equalSign,
	curlDash,
	add,
	sub,
	mul,
	power,
	div,
	doubleQoutation,
	dot,
	leftBrack,
	rightBrack,
	_print,
	input,
	str,
	_int,
	_float,
	_while,
	lessThan,
	greaterThan,
	andpersent,
	superlink,
	dolar,
	hastag,
	exclimation,
	lbutStright,
	at,
	badqoutes,
	question,
	comma,
	boolText,
	leftSquareBracket,
	rightSquareBracket,
	persent,
	underscore,
	matsInString
};
class Token {
public:
	TokenType type;
	std::string value;
};

#endif