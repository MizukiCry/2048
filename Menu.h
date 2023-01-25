#include "Game.h"

namespace Menu
{
	void Main()
	{
		Public::Clear();
		puts("Welcome to 2048.");
		puts("Created by Mizuki.");
		puts("\n");
		puts("Enter 1~4 to continue.");
		puts("");
		puts("1. Start Game.");
		puts("2. Config.");
		puts("3. Scoreboard.");
		puts("4. Exit.");
		while(true)
		{
			char c = Public::Get_Input();
			if(c == '1')Game::Main();
			else if(c == '2')Config::Main();
			else if (c == '3')Scores::Main();
			else if(c == '4')exit(0);
			if('1' <= c && c <= '3')break;
		}
	}
}