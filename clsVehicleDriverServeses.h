#pragma once

#include <iostream>
#include "clsVehicleDriver.h"
#include "clsScreen.h"

using namespace std;


class clsVehicleDriverServeses
{
private:



	static void $printVehicleDriver(clsVehicleDriver driver)
	{
		cout << "       " << setw(17) << left << driver.GetFullName() << "|" << setw(11) 
			<< left << driver.getId() << "|" << setw(15) << left << driver.GetMode() << "|" << setw(8) << left << driver.GetAge()
			<< "|" << setw(17) << left << driver.GetEmail() << "|" << setw(20) << left << driver.GetPhoneNumber() << "|"
			<< setw(7) << left << driver.GetSalary() << "|" << setw(5) << left << driver.GetVehcilID() << "|" << endl;
	}


	static void PrintOneDriver(clsVehicleDriver driver)
	{
		cout << "\n\n----------------------------------" << endl;
		cout << "  Driver Full Name = " << driver.GetFullName << endl;
		cout << "----------------------------------" << endl;
		cout << "Id : " << driver.getId() << endl;
		cout << "Age : " << driver.GetAge() << endl;
		cout << "Email : " << driver.GetEmail() << endl;
		cout << "Status : " << driver.GetMode() << endl;
		cout << "Phone Number : " << driver.GetPhoneNumber() << endl;
		cout << "Salary : " << driver.GetSalary() << endl;
		cout << "Vehcil Id : " << driver.GetVehcilID() << endl;
		cout << "----------------------------------" << endl;

		cout << endl << endl;

	}

	static void PrintOneDriverToUpdate(clsVehicleDriver driver)
	{
		cout << "\n\n----------------------------------" << endl;
		cout << "  Driver Full Name = " << driver.GetFullName << endl;
		cout << "----------------------------------" << endl;
		cout << "[1] Age : " << driver.GetAge() << endl;
		cout << "[2] Email : " << driver.GetEmail() << endl;
		cout << "[3] Status : " << driver.GetMode() << endl;
		cout << "[4] Phone Number : " << driver.GetPhoneNumber() << endl;
		cout << "[5] Salary : " << driver.GetSalary() << endl;
		cout << "[6] Vehcil Id : " << driver.GetVehcilID() << endl;
		cout << "----------------------------------" << endl;

		cout << endl << endl;

	}


public:


	static void showDriversList()
	{
		clsScreen::NewMenu("\t      Show Drivers List ", 40);

		DoubleLinkedList <clsVehicleDriver> AllDriversData = clsVehicleDriver::GetAllDrivers();


		printf("       ______________________________________________Drivers Are Are [%.3d]__________________________________________\n\n", AllDriversData.size());
		cout << "       " << setw(17) << left << "Driver Full Name" << "|" << setw(11) << left << "Driver ID" << "|" << setw(15) << left << "Driver Status" << "|" << setw(8) << left << "Age"
			<< "|" << setw(17) << left << "Email" << "|" << setw(20) << left << "Phone Number" << "|" << setw(7) << left << "Salary" << "|" << setw(5) << left << "V ID" << "|" << endl;

		cout << "       __________________________________________________________________________________________________________\n";


		if (AllDriversData.size() == 0)
		{
			cout << "                              No Drivers Exist " << endl;
		}

		else
			for (int i = 0; i < AllDriversData.size(); i++)
			{
				$printVehicleDriver(*AllDriversData[i]);
			}
		cout << "       __________________________________________________________________________________________________________\n\n\n\n";


		Input::pressAnyKeyToContinue();
	}




	static void AddDriver()
	{

		clsScreen::NewMenu("\t            Adding Driver", 43);

		clsVehicleDriver ToAdd;

		cout << "Enter Info For Driver You Want To Add : \n";

		ToAdd.SetFirstName(Input::readString("First Name : "));
		ToAdd.SetLastName(Input::readString("Last Name : "));
		ToAdd.SetPhoneNumber(Input::readString("Phone Number : "));
		cout << "Age : ";
		ToAdd.SetAge(Input::ReadIntNumberBetween(20 , 50 , "Age Should Be Over 20 And Under 50"));
		ToAdd.SetEmail(Input::readString("Email : "));
		ToAdd.SetSalary(Input::readInt("Enter Number Not Text :(  ", "Enter The Salary : "));
		ToAdd.setMode(clsVehicleDriver::enDriverMode::Working);
		cout << "Enter Vehicle Id (If No Vehcile Now Enter 0) :";
		ToAdd.SetVehicleByID(Input::ReadIntNumberBetween(0, 10000000));

		cout << endl << endl;

		PrintOneDriver(ToAdd);


		if (Input::readBool("Are You Sure To Add This driver : ", "y", "n"))
		{
			ToAdd.Add();
			cout << "\n\n Driver Added Succesfully :)";
		}

		else { cout << "\n\n Didn't Save Driver\n\n"; }
	}



	static void DeleteDriver()
	{
		clsScreen::NewMenu("\t         Deleting A Driver", 43);

		int id = Input::readInt("Coulsn't Enter text Enter Number : ", "Enter Id Of Driver You Want To Delete : ");

		clsVehicleDriver *ToDelete = clsVehicleDriver::Find(id);


		if (ToDelete == nullptr)
		{
			cout << "Couldn't Find Driver :(";
			return;
		}

		PrintOneDriver(*ToDelete);



		if (Input::readBool("Are You Sure To Delete This Station[Y/N] : ", "Y", "N"))
		{
			ToDelete->Delete();
			cout << "\n\n Driver Deleted Succesfully :)";
		}

		else { cout << "\n\nan Error Ocured Didn't Delete Driver\n\n"; }

	}


	static void FindDriver()
	{
		clsScreen::NewMenu("\t         Finding A Driver", 43);

		int Search;

		cout << "For Searching By Id Enter [1]" << endl;
		cout << "For Searching By Full Name Enter [2]" << endl;
		cout << "________________________________";
		cout << "Enter Number Of Search : ";
		Search = Input::ReadIntNumberBetween(1, 2);

		cout << endl << endl << endl;

		clsVehicleDriver* ToFind = nullptr;

		switch (Search)
		{
		case 1:
			ToFind = clsVehicleDriver::Find(Input::readInt("U Can't Enter Text Enter Number : ", "Enter Id : "));
			break;

		case 2:
			ToFind = clsVehicleDriver::Find(Input::readString("Enter Driver Full Name : "));
		}

		if (ToFind != nullptr)
		{
			PrintOneDriver(*ToFind);
		}


		else { cout << "\n\n No Station was Found :( \n\n"; }
	}



	static void Update()
	{
		clsScreen::NewMenu("\t         Updating A Driver", 43);

		clsVehicleDriver ToUpdate = *clsVehicleDriver::Find(Input::readInt("U Can't Enter Text Enter Number : ", "Enter the ID Of The Driver : "));

		PrintOneDriverToUpdate(ToUpdate);

		cout << "Choose What To Update : ";

		int up = Input::ReadIntNumberBetween(1, 6);

		switch (up)
		{
		case 1:
			cout << "Enter The New Name Of Station : ";
			ToUpdate.SetAge(Input::ReadIntNumberBetween(20, 50, "Age Should Be Over 20 And Under 50"));
			break;
		case 2:
			ToUpdate.SetEmail(Input::readString("Enter The New Email : "));
			break;
		case 3:
			cout << "Enter [1] Working , [2] Tacking Rest , [3] Out Of Work : ";
			ToUpdate.setMode(Input::ReadIntNumberBetween(1 , 3));
			break;
		case 4:
			ToUpdate.SetPhoneNumber(Input::readString("Enter The New Phone Number : "));
			break;
		case 5:
			ToUpdate.SetSalary(Input::readInt("U Can't Enter Text Enter Number : ", "Enter The New Salary :"));
		case 6:
			ToUpdate.SetVehicleByID(Input::readInt("U Can't Enter Text Enter Number : ", "Enter Vehcile Id :"));
		}


		PrintOneDriver(ToUpdate);

		if (Input::readBool("Are You Sure to Update This [Y/N] : ", "Y", "N"))
		{
			ToUpdate.Update();
			cout << "\n\n Driver Updated Succesfully :)";
		}

		else { cout << "\n\nan Error Ocured Didn't Update Driver\n\n"; }


	}

};
