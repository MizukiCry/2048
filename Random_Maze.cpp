#include <queue>
#include <chrono>
#include <cstdio>
#include <random>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

namespace Random_Maze
{
    const int N = 305;
    const int R_Seed = chrono::system_clock::now().time_since_epoch().count();
    const char Yes = ' ', No = '#', Vis = '.';
    mt19937 Rs(R_Seed);

    inline int Rand(int l, int r)
    {
        return Rs() % (r - l + 1) + l;
    }

    const int Dirx[] = {-1, 1, 0, 0}, Diry[] = {0, 0, -1, 1};
    int NDir[24][4] = {0, 1, 2, 3};

    struct Maze
    {
        int n, m;
        char Map[N][N];

        void Generate(int ns, int ms)
        {
            n = ns, m = ms;
            vector<pair<int, int>> v, vs;
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= m; ++j)
                {
                    Map[i][j] = No;
                    if(i != 1 && i != n && j != 1 && j != m)
                        vs.emplace_back(i, j);
                }
            Map[Rand(2, n - 1)][Rand(2, m - 1)] = Yes;
            bool Flag = true;
            while(Flag)
            {
                v = vs, vs.clear();
                shuffle(v.begin(), v.end(), Rs), Flag = false;
                for(auto i:v)
                {
                    int s = 0, x = i.first, y = i.second;
                    for(int j = 0; j < 4; ++j)
                        if(Map[x + Dirx[j]][y + Diry[j]] == Yes)
                            ++s;
                    if(s == 1)Map[x][y] = Yes, Flag = true;
                    else vs.emplace_back(x, y);
                }
            }
        }

        void Generate_Ver2(int ns, int ms)
        {
            n = ns, m = ms;
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= m; ++j)
                    Map[i][j] = No;
            vector<pair<int, int>> v;
            //queue 生成对称图形
            int Sx = Rand(2, n - 1), Sy = Rand(2, m - 1);
            Map[Sx][Sy] = Yes, v.emplace_back(Sx, Sy);
            while(!v.empty())
            {
                int Np = Rand(0, (int)v.size() - 1),Nd = Rand(0, 23);
                int Nx = v[Np].first, Ny = v[Np].second;
                v.erase(v.begin() + Np);
                for(int i = 0; i < 4; ++i)
                {
                    int Wx = Nx + Dirx[NDir[Nd][i]], Wy = Ny + Diry[NDir[Nd][i]], s = 0;
                    if(Wx == 1 || Wx == n || Wy == 1 || Wy == m)continue;
                    //printf("-- %d %d\n", Wx, Wy);
                    for(int j = 0; j < 4; ++j)
                        if(Map[Wx + Dirx[j]][Wy + Diry[j]] == Yes)
                            ++s;
                    if(Map[Wx][Wy] == No)
                    {
                        if(s == 1)Map[Wx][Wy] = Yes;
                        else Map[Wx][Wy] = Vis;
                        v.emplace_back(Wx, Wy);
                    }
                }
            }
        }

        void Generate_Ver3(int ns, int ms)
        {
            n = ns, m = ms;
            struct AI
            {
                int x, y, ID, Rs;
                AI(int xs, int ys, int IDs, int Rss):
                    x(xs), y(ys), ID(IDs), Rs(Rss){}
            };
            static int Vid[N][N];
            vector<AI> v;
            int AI_Cnt = max(n * m * Rand(1, 20) / 100, 1);
            int Max_Step = n * m, Min_Step = sqrt(n * m);
            //int Max_Step = sqrt(min(n, m)), Min_Step = 1;
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= m; ++j)
                    Map[i][j] = No, Vid[i][j] = 0;
            for(int i = 1; i <= AI_Cnt; ++i)
            {
                int x, y;
                do
                {
                    x = Rand(2, n - 1);
                    y = Rand(2, m - 1);
                }while(Map[x][y] != No);
                Map[x][y] = Yes;
                v.emplace_back(x, y, i, Rand(Min_Step, Max_Step));
                Vid[x][y] = i;
            }
            while(!v.empty())
            {
                int p = Rand(0, (int)v.size() - 1), d = Rand(0, 3);
                int wx = v[p].x + Dirx[d], wy = v[p].y + Diry[d];
                if(wx == 1 || wx == n || wy == 1 || wy == m)continue;
                if(Vid[wx][wy] && Vid[wx][wy] != v[p].ID)
                {
                    v.erase(v.begin() + p);
                    continue;
                }
                if(!Vid[wx][wy])
                {
                    Vid[wx][wy] = v[p].ID;
                    Map[wx][wy] = Yes;
                }
                v[p].x = wx, v[p].y = wy;
                if(!--v[p].Rs)v.erase(v.begin() + p);
            }
        }

        void Generate_Ver3_1(int ns, int ms)
        {
            n = ns, m = ms;
            struct AI
            {
                int x, y, ID;
                AI(int xs, int ys, int IDs):
                    x(xs), y(ys), ID(IDs){}
            };
            static int Vid[N][N];
            vector<AI> v;
            int AI_Cnt = max(n * m * Rand(9, 11) / 100, 1);
            int Max_Step = sqrt(min(n, m)), Min_Step = 1;
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= m; ++j)
                    Map[i][j] = No, Vid[i][j] = 0;
            for(int i = 1; i <= AI_Cnt; ++i)
            {
                int x, y;
                do
                {
                    x = Rand(2, n - 1);
                    y = Rand(2, m - 1);
                }while(Map[x][y] != No);
                Map[x][y] = Yes;
                v.emplace_back(x, y, i);
                Vid[x][y] = i;
            }
            puts("T");
            while(!v.empty())
            {
                int p = Rand(0, (int)v.size() - 1), d = Rand(0, 3);
                bool Flag = false;
                for(int Steps = Rand(Min_Step, Max_Step); Steps--; )
                {
                    int wx = v[p].x + Dirx[d], wy = v[p].y + Diry[d];
                    if(wx == 1 || wx == n || wy == 1 || wy == m)continue;
                    if(Vid[wx][wy] && Vid[wx][wy] != v[p].ID)
                    {
                        Flag = true;
                        break;
                    }
                    if(!Vid[wx][wy])
                    {
                        Vid[wx][wy] = v[p].ID;
                        Map[wx][wy] = Yes;
                    }
                    v[p].x = wx, v[p].y = wy;
                }
                if(Flag)v.erase(v.begin() + p);
            }
        }

        void Output(const string &s)
        {
            const int Pixie = 15;
            fstream os;
            os.open(s + ".ppm", ios::out | ios::binary);
            os << "P6\n" << m * Pixie << ' ' << n * Pixie << "\n255\n";
            for(int i = 1; i <= n; ++i)
                for(int x = 1; x <= Pixie; ++x)
                    for(int j = 1; j <= m; ++j)
                        for(int y = 1; y <= Pixie; ++y)
                            if(Map[i][j] == Yes)
                                os << char(0xff) << char(0xff) << char(0xff);
                            else
                                os << char(0x00) << char(0x00) << char(0x00);
            for(int i = 1; i <= n; ++i, putchar('\n'))
                for(int j = 1; j <= m; putchar(Map[i][j++]));
        }
    };

    void Init()
    {
        for(int i = 1; i < 24; ++i)
        {
            memcpy(NDir[i], NDir[i - 1],sizeof NDir[i]);
            next_permutation(NDir[i], NDir[i] + 4);
        }
    }
}

int main()
{
    Random_Maze::Init();
    Random_Maze::Maze m;
    m.Generate_Ver3_1(50, 50);
    m.Output("Random_Maze");
    return 0;
}