#include "parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

bool Parser::parse(const std::string& input)
{
	if (input.length() == 0 || !(isdigit(input[0]) || isDiceChar(input[0])))
	{
		// NOTE: invalid input
		return false;
	}

	bool isOp = false;
	bool isDice = false;
	bool isDiceNumber = false;

	int op = 0;
	int diceNumber = 0;

	for (int i = 0; i < input.length(); i++)
	{
		Tokens.shrink_to_fit();
		if (i < (input.length() - 1) && isDiceChar(input[i]))
		{
			if (isDice)
			{
				// NOTE: invalid string
				return false;
			}
			isDice = true;
		}
		else if (isdigit(input[i]))
		{
			int num = parseNumber(input, i);
			i += numLength(num) - 1;
			if (i < input.length() - 1 && isDiceChar(input[i + 1]))
			{
				isDiceNumber = true;
				diceNumber = num;
			}
			else if (isDiceNumber)
			{
				if (isDice && diceNumber > 0)
				{
					Tokens.push_back(std::make_pair(num, diceNumber));
					isDice = false;
					isDiceNumber = false;
					diceNumber = 0;
				}
				else
				{
					// NOTE: invalid string
					return false;
				}
			}
			else if (isOp)
			{
				Tokens.push_back(std::make_pair(1, num));
				isOp = false;
				op = 0;
			}
			else
			{
				// NOTE: invalid string
				return false;
			}
		}
		else if (input[i] == ' ')
		{
			while (input[i + 1] == ' ')
			{
				i++;
			}
			continue;
		}
		else if (isOperation(input[i]))
		{
			op = opSymbolToMacros(input[i]);
			Tokens.push_back(std::make_pair(1, op));
			isOp = true;
		}
		else
		{
			// NOTE: invalid string
			return false;
		}
	}
	return true;
}

vec_p_ii Parser::getTokens()
{
	return Tokens;
}

int Parser::parseNumber(const std::string& str, const int startIndex)
{
	if (startIndex > str.length() - 1)
	{
		// NOTE: startIndex is biger or equals to the last index of the string
		// TODO: log this "error"
		return -1;
	}
	uint result = 0;
	for (int i = startIndex; i < str.length(); i++)
	{
		if (isdigit(str[i]))
		{
			result *= 10;
			result += (uint) (str[i] - 48);
			continue;
		}
		else
		{
			break;
		}
	}
	return result;
}