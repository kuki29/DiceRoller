#include <iostream>
#include <string>

#include "dice_roller.h"

int main()
{
	// TODO: !!!Test parser!!!
	// TODO: !!!Test roller!!!
	// (done)TODO: !!!check for empty string!!!
	// TODO: !!!check parsing!!!
	// TODO: !!!check generation!!!
	bool run = true;
	std::string user_input;
	DiceRoller diceRoller;
	while (run)
	{
		std::getline(std::cin, user_input);
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