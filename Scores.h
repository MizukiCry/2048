namespace Scores
{
	ll a[Rank_Size];
	void Init()
	{
		std::ofstream Out("Scores.txt");
		for(int i = 0; i < Rank_Size; ++i)Out << (a[i] = 0) << '\n';
	}

	bool Load()
	{
		std::ifstream In("Scores.txt");
		if(!In)
		{
			Init(), In.open("Scores.txt");
			if(!In)return false;
		}
		for(int i = 0; i < Rank_Size; ++i)
			if((a[i] = Public::Read_Pll(In)) == -1)
				return false;
		return true;
	}

	bool Update(ll x)
	{
		Load();
		if(x <= a[9])return false;
		for(int i = 9; i >= 0; --i)
		{
			if(i != 9)a[i + 1] = a[i];
			if(!i || x <= a[i - 1])a[i] = x, i = 0;
		}
		std::ofstream Out("Scores.txt");
		for(int i = 0; i < Rank_Size; ++i)Out << a[i] << '\n';
		return true;
	}

	void Main()
	{
		Public::Clear();
		if(Load())for(int i = 0; i < Rank_Size; ++i)
			if(a[i])printf("Rank #%d : %lld\n", i + 1, a[i]);
			else printf("Rank #%d : ?\n", i + 1);
		else puts("Error: Scores Load Failed."), Init();
		puts("Press enter to return.");
		while(getch() != Enter);
	}
}