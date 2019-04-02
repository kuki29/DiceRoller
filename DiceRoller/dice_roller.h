#ifndef _DICE_ROLLER_H_
#define _DICE_ROLLER_H_

#include <cstdlib>
#include <ctime>

#include "dice_roller_defines.h"
#include "parser.h"

class DiceRoller
{
private:
	std::string str;
	Parser parser;
	bool isTokensAlreadySet;

public:
	DiceRoller();
	DiceRoller(const std::string& str);
	DiceRoller(const vec_p_ii& tokens);
	~DiceRoller();

	// returns (ERR) if something went wrong
	int roll();
	void setTokens(const vec_p_ii& tokens);
	int rollDices(int dice, int amount = 1);
};

#endif