#pragma once

#include "clsScreen.h"
#include "Input.h"
#include "clsMainMenu.h"
#include "clsAdminScreen.h"
#include "clsPassenger.h"

using namespace std;

class clsLogin
{

	enum enWhatToDo { enUser = 1, enAdmin = 2, enDriver = 3, Exit = 4 };

	static void User()
	{/*
		Input::Clear();
		clsScreen::NewMenu("\t     Login Password", 43);
		
		OpenHash <string , clsPassenger> oh = clsPassenger::loadPassengersByName();
		
		string name = Input::readString("Enter FullName : ");
		string pass = Input::readPassword();
		clsPassenger a = *oh[name];
		if (a == nullptr) {
			cout << "Wrong user name or Password :(\n\n";
			Input::pressAnyKeyToContinue();
			return;
		}

		
		if(a.getPassword() == pass)*/
     		clsMainMenu::MainMenu();
	}

	static void Admin()
	{
		clsAdminScreen::AdminMenu();
	}

	static void Driver()
	{
		cout << "Driver May Be Here May Be Not We Don't Have Time :(\n\n";
	}


	static void LogoutScreen()
	{

		//clsLoginScreen::LoginScreen();

		//cout << "Logout Screen Will Be Here Near :(\n\n";
		//system("pause");

	}


	static void $p(enWhatToDo WhatToDo)
	{
		switch (WhatToDo)
		{
		case enWhatToDo::enUser:
			Input::Clear();
			User();
			Login();
			break;

		case enWhatToDo::enAdmin:
			Input::Clear();
			Admin();
			Login();
			break;

		case enWhatToDo::enDriver:
			Input::Clear();
			Driver();
			Login();
			break;

			//case enWhatToDo::enLogout:
			//	system("cls");
			//	LogoutScreen();
			//	break;

		case enWhatToDo::Exit:
			Input::Clear();
			//Login();
			break;
		}
	}





public:

	static void Login()
	{
		Input::Clear();



		clsScreen::NewMenu("              How To Login ", 43);

		cout << setw(37) << left << "" << "=======================================================" << endl;
		cout << setw(37) << left << "" << "                      Loging IN\n";
		cout << setw(37) << left << "" << "=======================================================" << endl;
		cout << setw(37) << left << "" << " Login As Passenger   [1]\n";
		cout << setw(37) << left << "" << " Login As Admin       [2]\n";
		cout << setw(37) << left << "" << " Vehicle Driver       [3]\n";
		cout << setw(37) << left << "" << " Exit                 [4]\n";
		cout << setw(37) << left << "" << "=======================================================" << endl;

		int WhatChoos;
		cout << setw(37) << "" << "Enter What to do [1 -> 4] : ";
		WhatChoos = Input::ReadIntNumberBetween(1, 4, "                                     Number is Not With Range Enter [1 -> 4] : ");

		$p((enWhatToDo)WhatChoos);
		return;

	}

};

