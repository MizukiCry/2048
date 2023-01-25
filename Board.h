#include "Config.h"

namespace Board
{
	int n = 0, a[Max_B_Size][Max_B_Size], NMax;
	int CStep;
	ll CScore;
	const ll MaxS = 1e18;

	pii Rand_Space()
	{
		std::vector<pii> v;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(!a[i][j])v.emplace_back(i, j);
		if(v.empty())return pii(-1, -1);
		return v[Public::Random(0, (int)v.size() - 1)];
	}

	int New_Nubmer()
	{
		int x = 1;
		while(x < NMax && Public::Random(0, 1))++x;
		return x;
	}

	void Spawn_New_Number()
	{
		pii p = Rand_Space();
		if(p.first != -1)a[p.first][p.second] = New_Nubmer();
	}

	void Random_Generate()
	{
		for(int i = Public::Random(std::max(1, n / 2 - 1), std::min(n, n / 2 + 1)); i; --i)
			Spawn_New_Number();
	}

	void Init()
	{
		Config::Load();
		n = Config::B_Size;
		NMax = 2;
		CStep = 0;
		CScore = 1;
		memset(a, 0, sizeof a);
		Random_Generate();
	}

	bool Game_End()
	{
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				if(!a[i][j])return false;
				if(i && a[i - 1][j] == a[i][j])return false;
				if(j && a[i][j - 1] == a[i][j])return false;
			}
		return true;
	}

	bool Roll_Up()
	{
		bool Res = false;
		for(int i = 0; i < n; ++i)
			for(int j = 0, l = 0; j < n; ++j)
				for(int k = j; a[k][i] && k; --k)
				{
					if(!a[k - 1][i])a[k - 1][i] = a[k][i], a[k][i] = 0, Res = true;
					else if(a[k - 1][i] == a[k][i] && k > l)
					{
						++a[k - 1][i], a[k][i] = 0, Res = true;
						CScore += 1ll << std::min(50, a[k - 1][i]);
						if(CScore > MaxS)CScore = MaxS;
						if(!Config::G_Mode)l = k;
					}
					else break;
				}
		return Res;
	}

	bool Roll_Down()
	{
		bool Res = false;
		for(int i = 0; i < n; ++i)
			for(int j = n - 1, l = n - 1; j >= 0; --j)
				for(int k = j; a[k][i] && k != n - 1; ++k)
				{
					if(!a[k + 1][i])a[k + 1][i] = a[k][i], a[k][i] = 0, Res = true;
					else if(a[k + 1][i] == a[k][i] && k < l)
					{
						++a[k + 1][i], a[k][i] = 0, Res = true;
						CScore += 1ll << std::min(50, a[k + 1][i]);
						if(CScore > MaxS)CScore = MaxS;
						if(!Config::G_Mode)l = k;
					}
					else break;
				}
		return Res;
	}

	bool Roll_Left()
	{
		bool Res = false;
		for(int i = 0; i < n; ++i)
			for(int j = 0, l = 0; j < n; ++j)
				for(int k = j; a[i][k] && k; --k)
				{
					if(!a[i][k - 1])a[i][k - 1] = a[i][k], a[i][k] = 0, Res = true;
					else if(a[i][k - 1] == a[i][k] && k > l)
					{
						++a[i][k - 1], a[i][k] = 0, Res = true;
						CScore += 1ll << std::min(50, a[i][k - 1]);
						if(CScore > MaxS)CScore = MaxS;
						if(!Config::G_Mode)l = k;
					}
					else break;
				}
		return Res;
	}

	bool Roll_Right()
	{
		bool Res = false;
		for(int i = 0; i < n; ++i)
			for(int j = n - 1, l = n - 1; j >= 0; --j)
				for(int k = j; a[i][k] && k != n - 1; ++k)
				{
					if(!a[i][k + 1])a[i][k + 1] = a[i][k], a[i][k] = 0, Res = true;
					else if(a[i][k + 1] == a[i][k] && k < l)
					{
						++a[i][k + 1], a[i][k] = 0, Res = true;
						CScore += 1ll << std::min(50, a[i][k + 1]);
						if(CScore > MaxS)CScore = MaxS;
						if(!Config::G_Mode)l = k;
					}
					else break;
				}
		return Res;
	}
}