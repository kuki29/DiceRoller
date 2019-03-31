#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>

#include "dice_roller_defines.h"

class Parser
{
private:
	// NOTE: vector of all dices in expression, (dice, number_of_dices)
	vec_p_ii Tokens;

public:
	Parser();
	~Parser();

	bool parse(const std::string& input);
	vec_p_ii getTokens();

private:
	// returns number from the string or -1 if it is imposible to parse
	int parseNumber(const std::string& string, const int startIndex);

	// returns amount of symbols in the number
	static inline int numLength(int num);
	static inline bool isOperation(char c);
	static inline bool isOperation(int i);
	static inline bool isDiceChar(char c);
	static inline int opSymbolToMacros(char c);
	// returns int value for representation of operation in vector

	friend class DiceRoller;
};

inline int Parser::numLength(int num)
{
	return std::to_string(num).length();
}

inline bool Parser::isOperation(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
	{
		return true;
	}
	return false;
}

inline bool Parser::isOperation(int i)
{
	if (i == ADD || i == SUB || i == MUL || i == DIV)
	{
		return true;
	}
	return false;
}

inline bool Parser::isDiceChar(char c)
{
	if (c == 'd' || c == 'D')
	{
		return true;
	}
	return false;
}

inline int Parser::opSymbolToMacros(char c)
{
	switch (c)
	{
	case '+':
		return ADD;
	case '-':
		return SUB;
	case '*':
		return MUL;
	case '/':
		return DIV;
	default:
		return -1;
	}
}

#endif