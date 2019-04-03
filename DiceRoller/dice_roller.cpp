#include "dice_roller.h"

DiceRoller::DiceRoller()
{
	std::srand((uint) time(NULL));
	isTokensAlreadySet = false;
}

DiceRoller::DiceRoller(const std::string& i_str)
	: str(i_str)
{
	std::srand((uint) time(NULL));
	isTokensAlreadySet = false;
}

DiceRoller::DiceRoller(const vec_p_ii& tokens)
{
	std::srand((uint) time(NULL));
	parser.Tokens = tokens;
	isTokensAlreadySet = true;
}

DiceRoller::~DiceRoller()
{
}

// IMPORTANT: refactor this shitty piece of code
int DiceRoller::roll()
{
	if (!isTokensAlreadySet)
	{
		if (!parser.parse(str))
		{
			// TODO: log it
			return ERR;
		}
	}
	int result = 0;
	const vec_p_ii& tokens = parser.Tokens;
	for (int i = 0; i < tokens.size(); i++)
	{
		int token0 = tokens[i].first;
		int token1 = tokens[i].second;
		if (Parser::isOperation(token1))
		{
			int num = 0;
			if (i < tokens.size() - 1)
			{
				i++;
			}
			else
			{
				return ERR;
			}
			if (tokens[i].first == 1 && tokens[i].second >= 0)
			{
				num = tokens[i].second;
			}
			else
			{
				num = rollDices(tokens[i].first, tokens[i].second);
			}

			switch (token1)
			{
			case ADD:
				result += num;
				break;

			case SUB:
				result -= num;
				break;

			case MUL:
				// TODO: think about alert if it equals 0
				result *= num;
				break;

			case DIV:
				if (token1 == 0)
				{
					// TODO: log it
					return ERR;
				}
				result /= num;
				break;

			default:
				// TODO: log it
				return ERR;
			}
		}
		else
		{
			result += rollDices(token0, token1);
		}
	}
	return result;
}

void DiceRoller::setTokens(const vec_p_ii& tokens)
{
	parser.Tokens = tokens;
}

int DiceRoller::rollDices(int dice, int amount)
{
	int result = 0;
	int tmp = 0;
	for (int i = 0; i < amount; i++)
	{
		if (dice != 0)
		{
			// NOTE: maybe it is too complicated, but it gives pretty random numbers
			tmp = std::rand() + time(NULL) % (std::rand() + 1) + 1;
			tmp = (std::rand() % (tmp + 1)) * (time(NULL) % (std::rand() % 3 + 1) + 2);
			tmp = (std::rand() + tmp) / ((std::rand() >> 
				((std::rand() % 
				(std::rand() % (time(NULL) % (rand() % 31 + 2) + 3) + 2) + 4) % 31)) + 4);
			result += (tmp % dice) + 1;
		}
		else
		{
			// TODO: log it
			return ERR;
		}
	}
	return result;
}

void initDiceRollerRandom()
{
	std::srand((uint) time(NULL));
	std::srand((uint) time(NULL) + std::rand());
}