#pragma once
#include "Input.h"
#include "clsScreen.h"
#include "TransportLineService.h"
using namespace std;



class clsMainMenu
{

		enum enWhatToDo { enShowLines = 1, enBookPlace = 2, enFindShorterPath = 3, Exit = 4};

		static void ShowLines()
		{
			TransportLineService::printAllTransportLines();
			system("pause");
		}

		static void BookPlace()
		{
			cout << "Book Place Will Be Here :(\n\n";
			system("pause");
		}

		static void FindShorterPath()
		{
			cout << "Find Path Will Be Here\n\n";
			system("pause");
		}



		static void $p(enWhatToDo WhatToDo)
		{
			switch (WhatToDo)
			{
			case enWhatToDo::enShowLines:
				Input::Clear();
				ShowLines();
				MainMenu();
				break;

			case enWhatToDo::enBookPlace:
				Input::Clear();
				BookPlace();
				MainMenu();
				break;

			case enWhatToDo::enFindShorterPath:
				Input::Clear();
				FindShorterPath();
				MainMenu();
				break;

			//case enWhatToDo::enLogout:
			//	system("cls");
			//	LogoutScreen();
			//	break;

			case enWhatToDo::Exit:
				Input::Clear();
				//MainMenu();
				break;
			}
		}





public:

	static void MainMenu()
	{
		Input::Clear();



		clsScreen::NewMenu("             The Main Menu ", 43);

		cout << setw(37) << left << "" << "=======================================================" << endl;
		cout << setw(37) << left << "" << "                      Main Menu\n";
		cout << setw(37) << left << "" << "=======================================================" << endl;
		cout << setw(37) << left << "" << "Show Lines We Support [1]\n";
		cout << setw(37) << left << "" << "Book From The App     [2]\n";
		cout << setw(37) << left << "" << "Find Shortest Path    [3]\n";
		cout << setw(37) << left << "" << "Logout                [4]\n";
		cout << setw(37) << left << "" << "=======================================================" << endl;

		int WhatChoos;
		cout << setw(37) << "" << "Enter What to do [1 -> 4] : ";
		WhatChoos = Input::ReadIntNumberBetween(1, 4, "                                     Number is Not With Range Enter [1 -> 4] : ");

		$p((enWhatToDo)WhatChoos);
		return;
	
	}

};

