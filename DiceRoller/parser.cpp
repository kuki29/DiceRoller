#include "parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

bool Parser::parse(const std::string& input)
{
	if (!(isdigit(input[0]) || input[0] == 'd' || input[0] == 'D') ||
		(input.length() == 0))
	{
		// NOTE: this string is not a dice expression
		return false;
	}

	for (int i = 0; i < input.length(); i++)
	{
		Tokens.shrink_to_fit();
		// TODO: it's possible to optimize, there are too many code copies
		// NOTE: I'm checking here dice for only one and I'll check it later if there are more than one of this dices
		if ((i < (input.length() - 1)) &&
			(input[i] == 'd' || input[i] == 'D'))
		{
			if (isdigit(input[i + 1]))
			{
				int dice = parseNumber(input, i + 1);
				i += numLength(dice);
				Tokens.push_back(std::make_pair(dice, 1));
			}
			else
			{
				// NOTE: this string is not a dice expression
				return false;
			}
		}
		else if (isdigit(input[i]))
		{
			int num = parseNumber(input, i);
			i += numLength(num);
			// TODO: review it, cuz this part of code was used two times
			if ((i < input.length() - 1) &&
				(input[i + 1] == 'd' || input[i + 1] == 'D'))
			{
				if (isdigit(input[i + 1]))
				{
					int dice = parseNumber(input, i + 1);
					i += numLength(dice);
					Tokens.push_back(std::make_pair(dice, num));
				}
				else
				{
					// NOTE: this string is not a dice expression
					return false;
				}
			}
			else if ((Tokens.size() > 0) && isOperation(Tokens.back().second))
			{
				if (isOperation(num))
				{
					// TODO: log it
					// NOTE: this program does not support this numbers, cuz uses it like math operations tokens
					return false;
				}
				Tokens.push_back(std::make_pair(1, num));
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
			int op = opSymbolToMacro(input[i]);
			while (input[++i] == ' ');
			if (isdigit(input[i]))
			{
				int num = parseNumber(input, i);
				i += numLength(num);
				if ((i < input.length() - 1) &&
					(input[i] == 'd' || input[i] == 'D'))
				{
					// NOTE: this string is not a dice expression
					return false;
				}
				Tokens.push_back(std::make_pair(1, op));
			}
			else
			{
				// NOTE: this string is not a dice expression
				return false;
			}
		}
		else
		{
			// NOTE: this string is not a dice expression
			return false;
		}
	}

	return true;
}

vec_p_uii Parser::getTokens()
{
	return Tokens;
}

int Parser::parseNumber(const std::string& str, const int start_index)
{
	if (start_index > str.length() - 1)
	{
		// NOTE: start_index is biger or equals to the last index of the string
		// TODO: log this "error"
		return -1;
	}
	uint result = 0;
	for (int i = start_index; i < str.length(); i++)
	{
		if (isdigit(str[i]))
		{
			result += (uint) pow(10.0f, ((int) str[i] - 48));
			continue;
		}
		else
		{
			break;
		}
	}
	return result;
}

inline int Parser::numLength(const int num) const
{
	return std::to_string(num).length();
}

inline bool Parser::isOperation(const char c) const
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
	{
		return true;
	}
	return false;
}

inline bool Parser::isOperation(int i) const
{
	if (i == ADD || i == SUB || i == MUL || i == DIV)
	{
		return true;
	}
	return false;
}

inline int Parser::opSymbolToMacro(char c) const
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