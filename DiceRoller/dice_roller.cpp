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

DiceRoller::DiceRoller(const vec_p_uii& tokens)
{
	std::srand((uint) time(NULL));
	parser.Tokens = tokens;
	isTokensAlreadySet = true;
}

DiceRoller::~DiceRoller()
{
}

int DiceRoller::roll()
{
	if (!isTokensAlreadySet)
	{
		if (!parser.parse(str))
		{
			// TODO: log it
			return INT_MAX + 1;
		}
	}
	int result = 0;
	const vec_p_uii& tokens = parser.Tokens;
	for (int i = 0; i < tokens.size(); i++)
	{
		int token0 = tokens[i].first;
		int token1 = tokens[i].second;
		if (parser.isOperation(token0))
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
						return INT_MAX + 1;
					}
					result /= tokens[i + 1].first;
					break;

				default:
					// TODO: log it
					return INT_MAX + 1;
				}
			}
			else 
			{
				// TODO: make method from this
				for (int j = 0; j < token1; j++)
				{
					result += (rand() % token0) + 1;
				}
			}
		}
		else
		{
			for (int j = 0; j < token1; j++)
			{
				result += (rand() % token0) + 1;
			}
		}
	}
	return result;
}

void DiceRoller::setTokens(const vec_p_uii& tokens)
{
	parser.Tokens = tokens;
}