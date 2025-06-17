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
		cout << setw(7) << "" << setw(20) << left << station.getStationName() << "|" << setw(13) << left << station.getid() << "|" << setw(15)
			<< left << station.getStationType() << "|" << setw(15) << left << station.getCity() << "|" << setw(17) << left << station.getStreet() << "|" <<
			setw(20) << left << station.getMaxParkingsCapacity() << "|" << endl;
	}


	static void PrintOneStatio(clsStation St)
	{
		cout << "-------------------------------" << endl;
		cout << "  Station Name = " << St.getStationName() << endl;
		cout << "-------------------------------" << endl;
		cout << "Id : " << St.getid() << endl;
		cout << "Station Type : " << St.getStationType() <<endl;
		cout << "City : " << St.getCity() << endl;
		cout << "Street : " << St.getStreet() << endl;
		cout << "Max Vehcils In 1 Parking : " << St.getMaxVehicleNumber();
		cout << "Max Parkings Num : " << St.getMaxParkingsCapacity();
		cout << endl << endl;

	}


public:



	static void showStationsList()
	{
		clsScreen::NewMenu("\t    Show Stations List ", 40);

		DoubleLinkedList <clsStation> AllStationData = clsStation::GetAllStationsList();


		printf("       ______________________________________________Stations Are [%.3d]__________________________________________\n\n", AllStationData.size());
		cout << "       " << setw(20) << left << "Station Name" << "|" << setw(13) << left << "Station ID" << "|" << setw(15) << left << "Station Type" << "|" << setw(15) << left << "City"
			<< "|" << setw(17) << left << "Street" << "|" << setw(20) << left << "Parking Capecty" << "|" << endl;

		cout << "       __________________________________________________________________________________________________________\n";


		if (AllStationData.size() == 0)
		{
			cout << "  No Stations Exist " << endl;
		}

		else
			for (int i = 0 ; i < AllStationData.size() ; i++)
			{
				$printStation(*AllStationData[i]);
			}
		cout << "       __________________________________________________________________________________________________________\n\n\n\n";


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
		StToAdd.setStationType( (enVehicleType) Input::readInt("Enter Number Not Text :(  ", "Enter Type Of Station Vehcils (Number) : BUS = 1 | TRAM = 2 | FERRY = 3 | METRO = 4 :"));
		StToAdd.setMaxVehicleNumber(Input::readInt("Enter Number Not Text :(  ", "Enter 1 Parking Capicty (Station is Devided To Many Parkings) : "));
		StToAdd.setMaxParkingsCapacity(Input::readInt("Enter Number Not Text :(  ", "Enter How Many Parkings Can Set In Station "));

		cout << endl << endl;

		PrintOneStatio(StToAdd);

	

		

		if (Input::readBool("Are You Sure To Add This Station : " , "y" , "n"))
		{
			StToAdd.Add();
			cout << "\n\n Station Added Succesfully :)";
		}
		
		else   { cout << "\n\n Didn't Save Station\n\n"; }
	}




};

