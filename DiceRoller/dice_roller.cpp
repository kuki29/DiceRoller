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
		if (Parser::isOperation(token0))
		{
			if (tokens[i + 1].first == 1)
			{
				switch (token1)
				{
				case ADD:
					result += tokens[i + 1].first;
					break;

				case SUB:
					result -= tokens[i + 1].first;
					break;

				case MUL:
					// TODO: think about alert if it equals 0
					result *= tokens[i + 1].first;
					break;

				case DIV:
					if (token1 == 0)
					{
						// TODO: log it
						return ERR;
					}
					result /= tokens[i + 1].first;
					break;

				default:
					// TODO: log it
					return ERR;
				}
			}
			else 
			{
				// TODO: make method from this
				for (int j = 0; j < token1; j++)
				{
					if (token0 != 0)
					{
						result += (rand() % token0) + 1;
					}
					else
					{
						// TODO: log it
						return ERR;
					}
				}
			}
		}
		else
		{
			for (int j = 0; j < token1; j++)
			{
				if (token0 != 0)
				{
					result += (rand() % token0) + 1;
				}
				else
				{
					// TODO: log it
					return ERR;
				}
			}
		}
	}
	return result;
}

void DiceRoller::setTokens(const vec_p_ii& tokens)
{
	parser.Tokens = tokens;
}