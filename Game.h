#include "Board.h"
#include "Scores.h"

namespace Game
{
	using std::cout;
	using std::string;
	const string s11 = "\u250c", s12 = "\u252c", s13 = "\u2510";
	const string s21 = "\u251c", s22 = "\u253c", s23 = "\u2524";
	const string s31 = "\u2514", s32 = "\u2534", s33 = "\u2518";
	const string s1 = "\u2500", s2 = "\u2502";
	#define P_Size 3//odd

	void Print()
	{
		Public::Clear();
		puts("Press Esc to return, r/R to restart.");
		puts("Press WASD/wasd or the direction keys to play.");
		using namespace Board;
		printf("Step: %d\n", CStep);
		printf("Score: %lld\n", CScore);
		for(int i = 0; i <= n; ++i)
		{
			for(int j = 0; j <= n; ++j)
			{
				if(!j)
					if(!i)cout << s11;
					else if(i != n)cout << s21;
					else cout << s31;
				else if(j != n)
					if(!i)cout << s12;
					else if(i != n)cout << s22;
					else cout << s32;
				else
					if(!i)cout << s13;
					else if(i != n)cout << s23;
					else cout << s33;
				if(j == n)break;
				for(int k = P_Size * 2 + 1; k; --k)cout << s1;
			}
			putchar('\n');
			if(i == n)break;
			for(int j = 0; j < P_Size; ++j)
			{
				for(int k = 0; k <= n; ++k)
				{
					cout << s2;
					if(k == n)break;
					if((P_Size >> 1) != j)
						for(int l = P_Size * 2 + 1; l; --l)putchar(' ');
					else
					{
						putchar(' ');
						if(!a[i][k])
						{
							for(int l = P_Size * 2; l; --l)putchar(' ');
							continue;
						}
						int l = log10(1ll << a[i][k]) + 1;
						if(l <= P_Size * 2)
						{
							printf("%lld", 1ll << a[i][k]);
							for(l = P_Size * 2 - l; l; --l)putchar(' ');
						}
						else
						{
							l = 2 + log10(a[i][k]) + 1;
							printf("2^%d", a[i][k]);
							for(l = P_Size * 2 - l; l; --l)putchar(' ');
						}
					}
				}
				putchar('\n');
			}
		}
	}

	int Refresh()
	{
		using namespace Board;
		Print();
		if(Game_End())return 0;
		while(true)
		{
			int Valid = false;
			char c = Public::Get_Input();
			if(c == 'w' || c == 'W' || c == Up)
				Valid = Roll_Up();
			else if(c == 's' || c == 'S' || c == Down)
				Valid = Roll_Down();
			else if(c == 'a' || c == 'A' || c == Left)
				Valid = Roll_Left();
			else if(c == 'd' || c == 'D' || c == Right)
				Valid = Roll_Right();
			else if(c == Esc)return 1;
			else if(c == 'r' || c == 'R')return 2;
			if(Valid)return 3;
		}
	}

	void Main()
	{
		while(true)
		{
			Board::Init();
			while(true)
			{
				int x = Refresh();
				++Board::CStep;
				if(!x)
				{
					puts("Game Over!");
					printf("You got %lld points!", Board::CScore);
					if(Scores::Update(Board::CScore))printf(" Scoreboard updated!");
					char c;
					while(true)
					{
						c = getch();
						if(c == Esc)return;
						if(c == 'r' || c == 'R')break;
					}
					break;
				}
				else if(x == 1)return;
				else if(x == 2)break;
				else if(x == 3)Board::Random_Generate();
				Board::CScore += Board::CStep;
			}
		}
	}
}