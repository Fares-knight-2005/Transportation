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
		cout << "\n\n-------------------------------" << endl;
		cout << "  Station Name = " << St.getStationName() << endl;
		cout << "-------------------------------" << endl;
		cout << "Id : " << St.getid() << endl;
		cout << "City : " << St.getCity() << endl;
		cout << "Street : " << St.getStreet() << endl;
		cout << "Max Vehcils In 1 Parking : " << St.getMaxVehicleNumber();
		cout << "Max Parkings Num : " << St.getMaxParkingsCapacity();
		cout << endl << endl;

	}


	static void PrintOneStatioUpdate(clsStation St)
	{
		cout << "\n\n-------------------------------" << endl;
		cout << " [1] Station Name = " << St.getStationName() << endl;
		cout << "-------------------------------" << endl;
		cout << "[2] City : " << St.getCity() << endl;
		cout << "[3] Street : " << St.getStreet() << endl;
		cout << "[4] Max Vehcils In 1 Parking : " << St.getMaxVehicleNumber();
		cout << "[5] Max Parkings Num : " << St.getMaxParkingsCapacity();
		cout << "[6] to Add Parkings : " << endl;
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
			cout << "                                                  No Stations Exist " << endl;
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

		StToAdd.setStationName(Input::readString("Station Name (To Go Back Enter 0) : "));
		if (StToAdd.getStationName() == "0")
			return;
		OpenHash <string, clsStation> oh = clsStation::GetAllStationsOpenByName();
		while (oh[StToAdd.getStationName()] != nullptr)
		{
			cout << "\nSorry Name Is Already In Use \n";
			StToAdd.setStationName(Input::readString("Station Name (To Cancel Enter 0) : "));
			if (StToAdd.getStationName() == "0")
				return;
		}

		StToAdd.setCity(Input::readString("City Located in : "));
		StToAdd.setStreet(Input::readString("Street Name : "));
		StToAdd.setStationType( (enVehicleType) Input::readInt("Enter Number Not Text :(  ", "Enter Type Of Station Vehcils (Number) : BUS = 1 | TRAM = 2 | FERRY = 3 | METRO = 4 :"));
		StToAdd.setMaxVehicleNumber(Input::readInt("Enter Number Not Text :(  ", "Enter 1 Parking Capicty (Station is Devided To Many Parkings) : "));
		StToAdd.setMaxParkingsCapacity(Input::readInt("Enter Number Not Text :(  ", "Enter How Many Parkings Can Set In Station "));

		cout << endl << endl;


		if (Input::readBool("Do You Want To Add Parkings : ", "y", "n"))
		{
			cout << "Okay Then Press 0 to stop any time : ";

			while (true) {
				int id = (Input::readInt("Enter Number Not Text ", "Enter Id : "));
				if (id == 0)
					break;
				StToAdd.AddParkingbyId(id);
			}
		}

		
		PrintOneStatio(StToAdd);


		if (Input::readBool("Are You Sure To Add This Station : " , "y" , "n"))
		{
			StToAdd.Add();
			cout << "\n\n Station Added Succesfully :)";
		}
		
		else   { cout << "\n\n Didn't Save Station\n\n"; }
	}



	static void DeleteStation()
	{
		clsScreen::NewMenu("\t         Deleting A Station", 43);

		int id = Input::readInt("Coulsn't Enter text Enter Number : ", "Enter Id Of Station You Want To Delete : ");

		clsStation ToDelete = *clsStation::Find(id);

		PrintOneStatio(ToDelete);



		if (Input::readBool("Are You Sure To Delete This Station[Y/N] : ", "Y", "N"))
		{
			ToDelete.Delete();
			cout << "\n\n Station Deleted Succesfully :)";
		}

		else { cout << "\n\nan Error Ocured Didn't Delete Station\n\n"; }

	}


	static void FindStation()
	{
		clsScreen::NewMenu("\t         Finding A Station", 43);

		int Search;

        cout << "For Searching By Id Enter [1]" << endl;
		cout << "For Searching By Name Enter [2]" << endl;
		cout << "To Cancel Enter [0]" << endl;
		cout << "________________________________" << endl;
		cout << "Enter Number Of Search : ";
		Search = Input::ReadIntNumberBetween(0 ,2);

		cout << endl << endl << endl;
		if (Search == 0)
			return;

		clsStation *ToFind = nullptr;

		switch (Search)
		{
		case 1:
			ToFind = clsStation::Find(Input::readInt("U Can't Enter Text Enter Number : ", "Enter Id : "));
				break;

		case 2:
			ToFind = clsStation::Find(Input::readString("Enter Station Name : "));
		}

		if (ToFind != nullptr)
		{
			PrintOneStatio(*ToFind);
			cout << endl << "Parkings Of This Statin Are : ";

			for (int i = 0; i < ToFind->getAllParkings().size(); i++) {
				ToFind->getAllParkings()[i]->printParkingInfo();
			}
		}


		else { cout << "\n\n No Station was Found :( \n\n"; }
	}

	


	static void Update()
	{
		clsScreen::NewMenu("\t         Updating A Station", 43);

		clsStation *ToUpdate = clsStation::Find(Input::readInt("U Can't Enter Text Enter Number : ", "Enter the ID Of The Station : "));
		if (ToUpdate == nullptr)
		{
			cout << "\n\nStation Was Not Found :(\n";
			return;
		}

		PrintOneStatioUpdate(*ToUpdate);

		cout << "Choose What To Update : ";

		int up = Input::ReadIntNumberBetween(1 , 6);

		switch (up)
		{
		case 1:
			ToUpdate->setStationName(Input::readString("Enter The New Name Of Station : "));
			break;
		case 2:
			ToUpdate->setCity(Input::readString("Enter The New City : "));
			break;
		case 3:
			ToUpdate->setStreet(Input::readString("Enter The New Street : "));
			break;
		case 4:
			ToUpdate->setMaxVehicleNumber(Input::readInt("U Can't Enter Text Enter Number : ", "Enter Max Vehicles Number :"));
		case 5:
			ToUpdate->setMaxParkingsCapacity(Input::readInt("U Can't Enter Text Enter Number : ", "Enter Max Parkings Number :"));
			break;
		case 6:

			if (Input::readBool("Do You Want To Add Parkings : ", "y", "n"))
			{
				cout << "Okay Then Press 0 to stop any time : ";

				while (true) {
					int id = (Input::readInt("Enter Number Not Text ", "Enter Id : "));
					if (id == 0)
						break;
					ToUpdate->AddParkingbyId(id);
				}
			}
		}


		PrintOneStatio(*ToUpdate);

		if (Input::readBool("Are You Sure Update To This [Y/N] : ", "Y", "N"))
		{
			ToUpdate->Update();
			cout << "\n\n Station Updated Succesfully :)";
		}

		else { cout << "\n\nan Error Ocured Didn't Update Station\n\n"; }


	}

};

