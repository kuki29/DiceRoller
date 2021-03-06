#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <cstdlib>

#include "dice_roller.h"

int main()
{
	bool run = true;
	std::string user_input;
	DiceRoller diceRoller;
	while (run)
	{
		std::getline(std::cin, user_input);
		if (user_input == "exit")
		{
			break;
		}
		diceRoller = DiceRoller(user_input);
		int dice = diceRoller.roll();
		if (dice != ERR)
		{
			std::cout << "roll: " << dice << std::endl;
		}
		else
		{
			std::cout << "you typed an invalid expression!" << std::endl;
		}
		diceRoller.~DiceRoller();
	}
	system("pause");
	return 0;
}