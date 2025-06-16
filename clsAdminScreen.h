#pragma once

#include "Input.h"
#include "clsScreen.h"
#include "clsGame.h"
//#include "clsStationServeses.h"

using namespace std;


class clsAdminScreen
{
	enum enWhatToDo {
		enShow_Line = 1, enAdd_Line = 2, enDelete_Line = 3, enUpdat_Line = 4, enFind_Line,
		enShow_Passenger, enAdd_Passenger, enDelete_Passenger, enUpdate_Passenger, enFind_Passenger,
		enShow_Vehcils, enAdd_Vehcile, enDelete_Vehcile, enUpdate_Vehcile, enFind_Vehcile,
		enShow_Stations, enAdd_Station, enDelete_Station, enUpdate_Station, enFind_Station,
		enShow_Employyes, enAdd_Employee, enDelete_Employye, enUpdate_Employye, enFind_Employye,
		enShow_Trips, enSearch_Trip, enPlayGame, enExit
	};


	static void $p(enWhatToDo WhatToDo)
	{
		switch (WhatToDo)
		{

			//Employees

		case enWhatToDo::enAdd_Employee:
		    	Input::Clear();
		    	//Here Your Function Don't Touch Other Things
		    	Input::pressAnyKeyToContinue();
		    	AdminMenu();
		    	break;
			
		case enWhatToDo::enShow_Employyes:
		    	Input::Clear();
		    	//Here Your Function Don't Touch Other Things
		    	Input::pressAnyKeyToContinue();
		    	AdminMenu();
		    	break;

		case enWhatToDo::enDelete_Employye:
				Input::Clear();
				//Here Your Function Don't Touch Other Things
				Input::pressAnyKeyToContinue();
				AdminMenu();
				break;

		case enWhatToDo::enUpdate_Employye:
				Input::Clear();
				//Here Your Function Don't Touch Other Things
				Input::pressAnyKeyToContinue();
				AdminMenu();
				break;

		case enWhatToDo::enFind_Employye:
				Input::Clear();
				//Here Your Function Don't Touch Other Things
				Input::pressAnyKeyToContinue();
				AdminMenu();
				break;


					//Lines

		case enWhatToDo::enAdd_Line:
			    Input::Clear();
			    //Here Your Function Don't Touch Other Things
			    Input::pressAnyKeyToContinue();
			    AdminMenu();
			    break;


		case enWhatToDo::enDelete_Line:
				Input::Clear();
				//Here Your Function Don't Touch Other Things
				Input::pressAnyKeyToContinue();
				AdminMenu();
				break;

		case enWhatToDo::enUpdat_Line:
				Input::Clear();
				//Here Your Function Don't Touch Other Things
				Input::pressAnyKeyToContinue();
				AdminMenu();
				break;

		case enWhatToDo::enFind_Line:
				Input::Clear();
				//Here Your Function Don't Touch Other Things
				Input::pressAnyKeyToContinue();
				AdminMenu();
				break;

		case enWhatToDo::enShow_Line:
				Input::Clear();
				//Here Your Function Don't Touch Other Things
				Input::pressAnyKeyToContinue();
				AdminMenu();
				break;


                         //Passengers


		case enWhatToDo::enAdd_Passenger:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;

		case enWhatToDo::enUpdate_Passenger:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;


		case enWhatToDo::enDelete_Passenger:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;

		case enWhatToDo::enShow_Passenger:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;

		case enWhatToDo::enFind_Passenger:
			  Input::Clear();
			  //Here Your Function Don't Touch Other Things
			  Input::pressAnyKeyToContinue();
			  AdminMenu();
			  break;


									//Vehcils

		case  enWhatToDo::enAdd_Vehcile:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			  break;

		case enWhatToDo::enDelete_Vehcile:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;


		case enWhatToDo::enUpdate_Vehcile:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;

		case enWhatToDo::enFind_Vehcile:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;


		case enWhatToDo::enShow_Vehcils:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;




                                     //Stations

		case enWhatToDo::enAdd_Station:
			   Input::Clear();
			   //clsStationServeses::AddStation(); //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;


		case enWhatToDo::enDelete_Station:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;



		case enWhatToDo::enUpdate_Station:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;

		case enWhatToDo::enFind_Station:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;


		case enWhatToDo::enShow_Stations:
			   Input::Clear();
			   //clsStationServeses::showStationsList(); //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;



			   //Finsh Stations

		case enWhatToDo::enShow_Trips:
			   Input::Clear();
			   //Here Your Function Don't Touch Other Things
			   Input::pressAnyKeyToContinue();
			   AdminMenu();
			   break;


		case enWhatToDo::enSearch_Trip:
		       Input::Clear();
		       //Here Your Function Don't Touch Other Things
		       Input::pressAnyKeyToContinue();
		       AdminMenu();
		       break;


		case enWhatToDo::enPlayGame:
			   Input::Clear();
			   clsGame::Game();
			   AdminMenu();
			   break;

			//case enWhatToDo::enLogout:
			//	system("cls");
			//	LogoutScreen();
			//	break;

		case enWhatToDo::enExit:
			Input::Clear();
			//AdminMenu();
			break;
		}
	}





public:

	static void AdminMenu()
	{
		Input::Clear();

		

		clsScreen::NewMenu("             The Admin Menu ", 43);

		cout << setw(37) << left << "" << "=======================================================" << endl;
		cout << setw(37) << left << "" << "                      Admin Menu\n";
		cout << setw(37) << left << "" << "=======================================================" << endl;
		cout << setw(37) << left << "" << " Show Transp Lines    [1]  | Show Passengers Info [6]\n";
		cout << setw(37) << left << "" << " Add New Transp Line  [2]  | Add New Passenger    [7]\n";
		cout << setw(37) << left << "" << " Delete Transp Line   [3]  | Delete Passenger     [8]\n";
		cout << setw(37) << left << "" << " Update Transp Line   [4]  | Update Passenger     [9]\n";
		cout << setw(37) << left << "" << " Find Transp Line     [5]  | Find Passenger      [10]\n";
		cout << setw(37) << left << "" << "       ------------------------------------------\n";    
		cout << setw(37) << left << "" << " Show Vehcils Info   [11]  | Show Stations Info  [16]\n";
		cout << setw(37) << left << "" << " Add New Vehcil      [12]  | Add New Station     [17]\n";
		cout << setw(37) << left << "" << " Delete Vehcil       [13]  | Delete Station      [18]\n";
		cout << setw(37) << left << "" << " Update Vehcil       [14]  | Update Station      [19]\n";
		cout << setw(37) << left << "" << " Find Vehcil         [15]  | Find Station        [20]\n";
		cout << setw(37) << left << "" << "       ------------------------------------------\n";
		cout << setw(37) << left << "" << " Show Employees Info [21]  | Other Serveses  :)      \n";
		cout << setw(37) << left << "" << " Add New Employee    [22]  | Show All Trips Data [26]\n";
		cout << setw(37) << left << "" << " Delete Employee     [23]  | Search For Trip     [27]\n";
		cout << setw(37) << left << "" << " Update Employee     [24]  | Enter To Play Gmae  [28]\n";
		cout << setw(37) << left << "" << " Find Employee       [25]  | Logout              [29]\n";
		cout << setw(37) << left << "" << "=======================================================" << endl;

		int WhatChoos;
		cout << setw(37) << "" << "Enter What to do [1 -> 29] : ";
		WhatChoos = Input::ReadIntNumberBetween(1, 29, "                                     Number is Not With Range Enter [1 -> 29] : ");

		$p((enWhatToDo)WhatChoos);
		return;

	}
};

