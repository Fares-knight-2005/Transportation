#pragma once

#include <iostream>
#include "clsPerson.h"
#include "clsVehicle.h"
#include "Database.h"
#include <fstream>

using namespace std;


string txtFile = "VehcilDrivers.txt";

class clsVehicleDriver : clsPerson
{
	static string clsVehcilDriverFileName = "VehcilDrivers.txt";



public:

    enum enDriverMode {Working = 1 , TakingRest = 2 , OutOfWork = 3};


	string convertObjectToLine(clsBusDriver Driver)
	{
		string Arr[] = {
		   Driver.FirstName ,
		   Driver.LastName ,
		   to_string(Driver.Age) ,
		   Driver.Email ,
		   to_string(Driver.Id) ,
		   to_string((int)Driver.Mode),
		   to_string(Driver.Salary),
		   Driver.PhoneNumber ,
		   Driver.vehcilToDrive.getId() ,
		}
		return Database::join("#//#", Arr);
	}

	//I need func To Give Me The Vehcile From It's Id

private:

	clsVehicle vehcilToDrive;
	int Salary;
	enDriverMode Mode;

public:

 enDriverMode GetMode()
 {
	 return Mode;
 }

 void setMode(enDriverMode Mode)
 {
	 this->Mode = Mode;
 }

 int GetSalary()
 {
	 return Salary;
 }

 void SetSalary(int Salary)
 {
	 this->Salary = Salary;
 }

 void GetVehcilID()
 {
	 return vehcilToDrive.getId();
 }

 static void save(DoubleLinkedList <clsVehicleDriver> Driverss)
 {
	 fstream Drivers;

	 Drivers.open(clsVehcilDriverFileName, ios::out);

	 if (Drivers.is_open())
	 {
		 for (int i = 0 ; i < Driverss.size() ;i++)
		 {
			 if (Driverss[i] != nullptr)
			 {
				 clsVehicleDriver p = *Driverss[i];
				 string Line = p.toString();
				 TripsFile << Line << endl;
			 }
		 }

		 Drivers.close();
	 }
 }

 void Delete()
 {
	 this->Mode = enDriverMode::OutOfWork;
 }




};
