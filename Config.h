namespace Config
{
	int B_Size;
	int G_Mode;

	void Init()
	{
		std::ofstream Out("Config.txt");
		Out << (B_Size = 4) << '\n' << (G_Mode = 0) << '\n';
	}

	bool Load()
	{
		std::ifstream In("Config.txt");
		if(!In)
		{
			Init(), In.open("Config.txt");
			if(!In)return false;
		}
		B_Size = Public::Read_Pll(In);
		G_Mode = Public::Read_Pll(In);
		return Min_B_Size <= B_Size && B_Size <= Max_B_Size && !(G_Mode >> 1);
	}

	void Update()
	{
		std::ofstream Out("Config.txt");
		Out << B_Size << '\n' << G_Mode << '\n';
	}

	int Curp;
	void Show_Config()
	{
		puts("Config.");
		puts("Press up or down to choose the setting.");
		puts("Press left or right to change the setting.");
		puts("Press ESC to return.\n\n");
		printf("[%c] Board Size : %d\n", Curp ? ' ' : 'x', B_Size);
		printf("[%c] Game Mode  : %d\n", Curp ? 'x' : ' ', G_Mode);
	}

	void Main()
	{
		Public::Clear(), Curp = 0;
		if(!Load())puts("Error: Config Load Failed. Initialized."), Init();
		while(true)
		{
			Show_Config();
			char c = Public::Get_Input();
			if(c == Up || c == Down)Curp ^= 1;
			else if(c == Left)
				if(!Curp)B_Size = B_Size == Min_B_Size ? Max_B_Size : B_Size - 1;
				else G_Mode ^= 1;
			else if(c == Right)
				if(!Curp)B_Size = B_Size == Max_B_Size ? Min_B_Size : B_Size + 1;
				else G_Mode ^= 1;
			else if(c == Esc)return Update();
			Public::Clear();
		}
	}
}