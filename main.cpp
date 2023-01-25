#include <cmath>
#include <chrono>
#include <cstdio>
#include <random>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
//#include <windows.h>
#endif

typedef long long ll;
typedef std::pair<int, int> pii;
#include "Public.h"
#include "Menu.h"

int main()
{
	#ifdef _WIN32
		system("chcp 65001");
		system("cls");
	#endif
	while(true)Menu::Main();
	return 0;
}