namespace Public
{
	#if defined(__linux__)
		#define Enter '\n'
	#else
		#define Enter '\r'
	#endif

	#define Min_B_Size 2
	#define Max_B_Size 10
	#define Rank_Size 10
	#define Esc 27
	#define Up 72
	#define Down 80
	#define Left 75
	#define Right 77

	void Clear()
	{
		//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
		#ifdef _WIN32
			system("cls");
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		    COORD coordScreen = {0, 0};
		    DWORD cCharsWritten;
		    CONSOLE_SCREEN_BUFFER_INFO csbi;
		    DWORD dwConSize;
		    GetConsoleScreenBufferInfo(hConsole, &csbi);
		    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
		    GetConsoleScreenBufferInfo(hConsole, &csbi);
		    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
		    SetConsoleCursorPosition(hConsole, coordScreen);*/
		#else
			system("clear");
		#endif
	}

	void Set_Window_Size(int Col, int Line)
	{
		char s[50];
		sprintf(s, "mode con: cols=%d lines=%d", Col, Line);
		system(s);
	}

	ll Read_Pll(std::ifstream& f)
	{
		ll x = 0;
		std::string s;
		getline(f, s);
		if(s.empty())return -1;
		for(auto j:s)
			if(!isdigit(j))return -1;
			else x = x * 10 + j - 48;
		return x;
	}

	char Get_Input()
	{
		char c = getch();
		if(c != -32)return c;
		return getch();
	}

	const int R_Seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::mt19937 Rs(R_Seed);
	int Random(int l, int r)
	{
		return Rs() % (r - l + 1) + l;
	}
}