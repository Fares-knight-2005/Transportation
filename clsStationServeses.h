#pragma once


#include <iostream>
#include "clsScreen.h"
#include "clsStation.h"
#include "DataStructures.h"
#include "Input.h"
#include "cctype"


using namespace std;

class clsStationServeses
{

private:



	static void $printStation(clsStation station)
	{
		cout << setw(7) << "" << setw(15) << left << station.getStationName() << "|" << setw(25) << left << station.getid() << "|" << setw(15)
			<< left << station.getStationType() << "|" << setw(10) << left << station.getCity() << "|" << setw(25) << left << station.getStreet() << "|" <<
			setw(10) << left << station.getMaxParkingsCapacity() << "|" << endl;
	}


	static void PrintOneStatio(clsStation St)
	{
		cout << "-------------------------------";
		cout << "  Station Name = " << St.getStationName() << endl;
		cout << "-------------------------------";
		cout << "Id : " << St.getid() << endl;
		cout << "Station Type : " << St.getStationType() <<endl;
		cout << "City : " << St.getCity() << endl;
		cout << "Street : " << St.getStreet() << endl;
		cout << "Max Vehcils In 1 Parking : " << St.getMaxVehicleNumber();
		cout << "Max Parkings Num : " << St.getMaxParkingsCapacity();

	}


public:



	static void showStationsList()
	{
		clsScreen::NewMenu("\t    Show Stations List ", 40);

		DoubleLinkedList <clsStation> AllStationData = clsStation::GetAllStationsList();


		printf("       ______________________________________________Stations Are [%.3d]____________________________________________\n\n", AllStationData.size());
		cout << "       " << setw(15) << left << "Station Name" << "|" << setw(25) << left << "Station ID" << "|" << setw(15) << left << "Station Type" << "|" << setw(10) << left << "City"
			<< "|" << setw(25) << left << "Street" << "|" << setw(10) << left << "Parking Capecty" << "|" << endl;

		cout << "       __________________________________________________________________________________________________________\n";


		if (AllStationData.size() == 0)
		{
			cout << "  No Stations Exist " << endl;
		}

		else
			for (int i = 0 ; i < AllStationData.size() ; i++)
			{
				$printStation(AllStationData[i]);
			}
		cout << "       __________________________________________________________________________________________________________\n";

		Input::pressAnyKeyToContinue();
	}


	static void AddStation()
	{

		clsScreen::NewMenu("\t            Adding Station", 43);

		clsStation StToAdd;

		cout << "Enter Info For Station You Want To Add : \n";

		StToAdd.setStationName(Input::readString("Station Name : "));
		StToAdd.setCity(Input::readString("City Located in : "));
		StToAdd.setStreet(Input::readString("Street Name : "));
		StToAdd.setStationType( (enVehicleType) Input::readInt("Enter Type Of Station Vehcils (Number) : BUS = 1 | TRAM = 2 | FERRY = 3 | METRO = 4 :"));
		StToAdd.setMaxVehicleNumber(Input::readInt("Enter 1 Parking Capicty (Station is Devided To Many Parkings) : "));
		StToAdd.setMaxParkingsCapacity(Input::readInt("Enter How Many Parkings Can Set In Station "));


		char Okay = Input::readString("Are You Sure To Save This Station [Y/N] : ")[0];

		if (Okay == 'y' || Okay == 'Y');
		{
			StToAdd.Add();
			cout << "\n\n Station Added Succesfully :)";
		}
		if(Okay != 'y' && Okay != 'Y')
		{ 
		    { cout << "\n\n Didn't Save Station"; }
		}
	}




};

