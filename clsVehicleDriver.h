#pragma once

#include <iostream>
#include "clsPerson.h"
#include "clsVehicle.h"
#include <fstream>
#include "clsStation.h"
#include "Input.h"

using namespace std;


string txtFile = "VehcilDrivers.txt";

class clsVehicleDriver : public clsPerson
{
	

public:

    enum enDriverMode {Working = 1 , TakingRest = 2 , OutOfWork = 3};



private:

	clsVehicle vehcilToDrive;
	int Salary;
	enDriverMode Mode;

public:

	clsVehicleDriver(int Age, string FirstName, string LastName, string PhomeNum, string Email , 
		clsVehicle vehcil , int Salary , enDriverMode mode)
		: clsPerson(Age, FirstName, LastName, PhomeNum, Email)
	{
		this->vehcilToDrive = vehcil;
		this->Salary = Salary;
		this->Mode = mode;
	}

	clsVehicleDriver(){}

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


    static string convertObjectToLine(clsVehicleDriver Driver)
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
	    	to_string(Driver.vehcilToDrive.getId())
	     };
	     return clsStation::JoinString(Arr, 9, "#//#");
    }

 //I need func To Give Me The Vehcile From It's Id

    static clsVehicleDriver convertLineToObject(string Line)
    {
	     DoubleLinkedList <string> ObjectList = clsStation::Split(Line, "#//#");
	    
	     clsVehicleDriver St;
	     St.FirstName = (*ObjectList[0]);
	     St.LastName = *ObjectList[1];
	     St.Age = stoi(*ObjectList[2]);
	     St.Email = *ObjectList[3];
	     St.Id = stoi(*ObjectList[4]);
	     St.Mode = (enDriverMode) stoi(*ObjectList[5]);
	     St.Salary = stoi(*ObjectList[6]);
		 St.PhoneNumber = (*ObjectList[7]);
		 St.vehcilToDrive = clsVehicle::getVehicleByID(stoi(*ObjectList[8]));

		 return St;
    }

    void SetSalary(int Salary)
    {
     	this->Salary = Salary;
    }

    int GetVehcilID()
    {
	    return this->vehcilToDrive.getId();
    }

	void SetVehicleByID(int id)
	{
		vehcilToDrive = clsVehicle::getVehicleByID(id);
	}

	static void save(DoubleLinkedList <clsVehicleDriver> Driverss)
	{

		fstream Drivers;

		Drivers.open(txtFile, ios::out);

		if (Drivers.is_open())
		{
			for (int i = 0; i < Driverss.size();i++)
			{
				if (Driverss[i] != nullptr)
				{
					clsVehicleDriver p = *Driverss[i];
					string Line = convertObjectToLine(p);
					Drivers << Line << endl;
				}
			}

			Drivers.close();
		}
	}

	void Delete()
	{
		this->Mode = enDriverMode::OutOfWork;
	}


	void Add()
	{
		fstream MyFile;
		MyFile.open(txtFile, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << convertObjectToLine(*this) << endl;
			MyFile.close();
		}
	}



	static DoubleLinkedList <clsVehicleDriver> GetAllDrivers()
	{
		DoubleLinkedList <clsVehicleDriver> AllDrivers;

		fstream MyFile;
		MyFile.open(txtFile, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsVehicleDriver vDriver = convertLineToObject(Line);
				AllDrivers.addLast(vDriver);
			}

			MyFile.close();

		}

		return AllDrivers;

	}


	static OpenHash <int, clsVehicleDriver> GetAllDriversOpen()
	{

		OpenHash <int, clsVehicleDriver> AllDrivers;

		fstream MyFile;
		MyFile.open(txtFile, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsVehicleDriver driver = convertLineToObject(Line);
				AllDrivers.insert(driver.getId(), driver);
			}

			MyFile.close();

		}
		return AllDrivers;

	}



	void Update()
	{
		OpenHash <int, clsVehicleDriver> AllDrivers = GetAllDriversOpen();

		*AllDrivers[this->getId()] = *this;

		SaveAllFromOpenHash(AllDrivers);
	}


	static OpenHash <string, clsVehicleDriver> GetAllDriversOpenByName()
	{

		OpenHash <string, clsVehicleDriver> AllDrivers;

		fstream MyFile;
		MyFile.open(txtFile, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsVehicleDriver driver = convertLineToObject(Line);
				AllDrivers.insert(driver.GetFullName(), driver);
			}

			MyFile.close();

		}
		return AllDrivers;

	}
	

	template <typename T>
	static void SaveAllFromOpenHash(OpenHash <T, clsVehicleDriver> AllDrivers)
	{
		fstream File;

		File.open(txtFile, ios::out);

		if (File.is_open())
		{
			for (int i = 0; i < AllDrivers.getCapicty(); i++) {
				Node <HashNode<T, clsVehicleDriver>>* d = AllDrivers.getHead(i);
				while (d != nullptr) {
					File << convertObjectToLine(d->item.item) << endl;
					d = d->next;
				}
			}

			File.close();
		}
	}

	void Delete()
	{
		OpenHash <int, clsVehicleDriver> AllDrivers = GetAllDriversOpen();

		AllDrivers[this->getId()]->Mode = enDriverMode::OutOfWork;

		SaveAllFromOpenHash(AllDrivers);
	}


	static clsVehicleDriver* Find(int id)
	{
		OpenHash <int, clsVehicleDriver> AllDrivers = GetAllDriversOpen();

		return AllDrivers[id];
	}


	static clsVehicleDriver* Find(string FullName)
	{
		OpenHash <string, clsVehicleDriver> AllDrivers = GetAllDriversOpenByName();

		return AllDrivers[Name];
	}

};
