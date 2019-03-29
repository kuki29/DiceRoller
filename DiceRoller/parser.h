#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>

#include "dice_roller_defines.h"

class Parser
{
private:
	// NOTE: vector of all dices in expression, (dice, number_of_dices)
	vec_p_uii Tokens;

public:
	Parser();
	~Parser();

	bool parse(const std::string& input);
	vec_p_uii getTokens();

private:
	// returns number from the string or -1 if it is imposible to parse
	int parseNumber(const std::string& string, const int startIndex);

	// returns amount of symbols in the number
	inline int numLength(const int num) const;
	inline bool isOperation(char c) const;
	inline bool isOperation(int i) const;
	// returns int value for representation of operation in vector
	inline int opSymbolToMacro(char c) const;

	friend class DiceRoller;
};

#endif