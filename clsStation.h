

#pragma once

#include <iostream>
#include <fstream>
#include "DataStructures.h"
#include "clsParking.h"
#include "clsPassengerTrip.h"
#include "clsVehicle.h"
#include "string"


using namespace std;

string StationsFile = "Stations.txt";


class clsStation
{

	int station_id;
	string station_Name;
	ClosedHash <int, clsParking> parkings;
	string city;
	string street;
	int maxParkingsCapicty;
	int maxVehcelNumberIn1Parking;
	enVehicleType stationType;
	bool markToDelete = false;

	static string convertObjectToLine(clsStation s)
	{
		string arr[] = {
			to_string(s.getid()) ,
			s.getStationName() ,
			s.getCity() ,
			s.getStreet() ,
			to_string(s.getMaxParkingsCapacity()) , 
			to_string(s.getMaxVehicleNumber()) ,
			to_string((int)s.getStationType()) ,
		};

		string* Array = arr;

		for (int i = 0; i < s.parkings.size(); i++)
		{
			clsParking* D = s.parkings.getNode(i);
			if (D != nullptr)
			{
				while (Array != nullptr)
					Array = Array + 1;

				*Array = D->getId();
			}
		}
		return JoinString(Array , s.parkings.size() + 7, "#//#");
	}

	//I Need Function in Parking Class return all station Parkings

	static clsStation convertLineToObject(string Line)
	{
		DoubleLinkedList <string> ObjectList = Split(Line, "#//#");
	    
		clsStation St;
		St.station_id = stoi(*ObjectList[0]);
		St.station_Name = *ObjectList[1];
		St.city = *ObjectList[2];
		St.street = *ObjectList[3];
		St.maxParkingsCapicty = stoi(*ObjectList[4]);
		St.maxVehcelNumberIn1Parking = stoi(*ObjectList[5]);
		St.stationType = (enVehicleType) stoi(*ObjectList[6]);

		if (ObjectList.size() > 7)
		{
			OpenHash <int, clsParking> AllParkings = clsParking::loadParkings();

			for (int i = 0; i < ObjectList.size() - 7; i++)
			{
				*St.parkings[i] = *AllParkings[stoi(*ObjectList[i + 7])];
			}
		}
		return St;
	}



public:

	bool operator==(int id) {
		return this->station_id == id;
	}
	

	int getid()
	{
		return station_id;
	}

	void setStationName(string name) { station_Name = name; }
	void setCity(string cityName) { city = cityName; }
	void setStreet(string streetName) { street = streetName; }
	void setMaxParkingsCapacity(int capacity) { maxParkingsCapicty = capacity; }
	void setMaxVehicleNumber(int maxVehicles) { maxVehcelNumberIn1Parking = maxVehicles; }
	void setStationType(enVehicleType type) { stationType = type; }
	string getStationName() { return station_Name; }
	string getCity() { return city; }
	string getStreet() { return street; }
	int getMaxParkingsCapacity() { return maxParkingsCapicty; }
	int getMaxVehicleNumber() { return maxVehcelNumberIn1Parking; }
	enVehicleType getStationType() { return stationType; }
	bool isMarkedToDelete() { return markToDelete; }



	void addPassengerTrip(int lineId, clsPassengerTrip p) {
		parkings[lineId]->addPassengerTrip(p);
	}

	ClosedHash <int, clsParking> getAllParkings()
	{
		return parkings;
	}

	bool AddParkingbyId(int id)
	{
		clsParking *P = clsParking::Find(id);
		if (P != nullptr) {
			this->parkings.insert(P->getLineId(), *P);
			return true;
		}
		return false;
	}


	void AddParking(clsParking P)
	{
		this->parkings.insert(P.getLineId(), P);
	}


	clsParking* getParking(int lineId) {
		return  parkings[lineId];
	}




	clsStation(){}



	static void save(DoubleLinkedList<clsStation> AllStations)
	{
		fstream station;

		station.open(StationsFile, ios::out);

		if (station.is_open())
		{
			for (int i = 0 ; i < AllStations.size() ; i++)
			{
				if (AllStations[i]->markToDelete == false) {
					string Line = convertObjectToLine(*AllStations[i]);
					station << Line << endl;
				}
			}

			station.close();
		}
	}

	void addNewParking(int lineId, enVehicleType type) {

		OpenHash<int, clsParking> parkings = clsParking::loadParkings();

		cout << "\n===========================================\n";
		cout << "              Add New Parking";
		cout << "\n===========================================\n";

		double distance = Input::readDouble("Enter Distance To Next Parking: ");

		clsParking newParking(distance, station_id, type, lineId);
		parkings.insert(lineId, newParking);
		clsParking::saveParkingsFromOpenHash(parkings);
		cout << "\nParking added successfully with ID: " << newParking.getId() << "\n";
	}

	void removeParking(int lineId) {

		OpenHash<int, clsParking> p = clsParking::loadParkings();
		clsParking* p2 = p[lineId];
		int id = p2->getId();
		parkings.remove(lineId);
		p.remove(id);
		clsParking::saveParkingsFromOpenHash(p);
	}

	static ClosedHash <int , clsStation> GetAllStations()
	{

		ClosedHash <int, clsStation> AllStations;

		fstream MyFile;
		MyFile.open(StationsFile, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsStation station = convertLineToObject(Line);
				AllStations.insert(station.getid(), station);
			}

			MyFile.close();

		}

		return AllStations;

	}

	//ClosedHash <int, clsStation> GetAllParkings()
	//{
	//	return parkings;
	//}


	template <typename T>
	static void SaveAllFromOpenHash(OpenHash <T , clsStation> AllStatitons)
	{
		fstream File;

		File.open(StationsFile, ios::out);

		if (File.is_open())
		{
			for (int i = 0; i < AllStatitons.getCapicty(); i++) {
				Node <HashNode<T, clsStation>>* d = AllStatitons.getHead(i);
				
				while (d != nullptr) {
                    if(!d->item.item.markToDelete)
					File << convertObjectToLine(d->item.item) << endl;
					d = d->next;
				}
			}

			File.close();
		}
	}

	static OpenHash <int, clsStation> GetAllStationsOpen()
	{

		OpenHash <int, clsStation> AllStations;

		fstream MyFile;
		MyFile.open(StationsFile, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsStation station = convertLineToObject(Line);
				AllStations.insert(station.getid(), station);
			}

			MyFile.close();

		}
		return AllStations;

	}



	static OpenHash <string, clsStation> GetAllStationsOpenByName()
	{

		OpenHash <string, clsStation> AllStations;

		fstream MyFile;
		MyFile.open(StationsFile, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsStation station = convertLineToObject(Line);
				AllStations.insert(station.getStationName() , station);
			}

			MyFile.close();

		}
		return AllStations;

	}

	static clsStation* Find(int id)
	{
		OpenHash <int, clsStation> AllStations = GetAllStationsOpen();

		return AllStations[id];
	}


	static clsStation* Find(string Station_Name)
	{
		OpenHash <string, clsStation> AllStations = GetAllStationsOpenByName();

		return AllStations[Station_Name];
	}

	static DoubleLinkedList <clsStation> GetAllStationsList()
	{
		DoubleLinkedList <clsStation> AllStations;

		fstream MyFile;
		MyFile.open(StationsFile, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsStation station = convertLineToObject(Line);
				AllStations.addLast(station);
			}

			MyFile.close();

		}

		return AllStations;

	}


	void Add()
	{
		fstream MyFile;
		MyFile.open(StationsFile , ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << convertObjectToLine(*this) << endl;
			MyFile.close();
		}
	}

	void Delete()
	{
		OpenHash <int, clsStation> AllStations = clsStation::GetAllStationsOpen();

		AllStations[this->getid()]->markToDelete = true;

		SaveAllFromOpenHash(AllStations);
	}


	void Update()
	{
		OpenHash <int, clsStation> AllStations = clsStation::GetAllStationsOpen();

		*AllStations[this->getid()] = *this;

		SaveAllFromOpenHash(AllStations);
	}


	static DoubleLinkedList <string> Split(string s, string delim)
	{
		string Word = "";

		DoubleLinkedList <string> Words;

		short pos = s.find(delim);

		while (pos != string::npos)
		{
			Word = s.substr(0, pos);
			s.erase(0, pos + delim.length());

			if (Word != "")
				Words.addLast(Word);

			pos = s.find(delim);
		}

		if (s != "")
			Words.addLast(s);

		return Words;
	}

	

	static string JoinString(string* ArrString, int ArraySize , string Delim)
	{
		string Results = "";

	      	if (ArrString != nullptr)
			for (int i = 0; i < ArraySize ; i++)
			{
				Results += Delim + ArrString[i];
			}

		return Results.substr(Delim.length(), Results.length() - Delim.length());
	}
};

