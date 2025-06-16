#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

class clsScreen
{

public:
	static void NewMenu(string TopicOfMenu, int NumberOfTaps)
	{
		cout << setw(NumberOfTaps) << left << "" << "________________________________________\n";
		cout << setw(NumberOfTaps) << left << "" << TopicOfMenu << endl;
		cout << setw(NumberOfTaps) << left << "" << "________________________________________\n\n";

		time_t t = time(0);
		tm* now = localtime(&t);
		cout << setw(NumberOfTaps) << left << "" << "            Date: ";
		cout << now->tm_year + 1900 << "/" << now->tm_mon + 1 << "/" << now->tm_mday << endl << endl;

	}

};

