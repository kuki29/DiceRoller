#include <iostream>
#include <string>

#include "dice_roller.h"

int main()
{
	// TODO: !!!Test parser!!!
	// TODO: !!!Test roller!!!
	// TODO: !!!check for empty string!!!
	// TODO: !!!check parsing!!!
	// TODO: !!!check generation!!!
	bool run = true;
	std::string user_input;
	DiceRoller diceRoller;
	while (run)
	{
		std::getline(std::cin, user_input);
		diceRoller = DiceRoller(user_input);
		std::cout << "roll: " << diceRoller.roll() << std::endl;
		diceRoller.~DiceRoller();
	}
	system("pause");
	return 0;
}