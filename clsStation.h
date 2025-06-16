#pragma once

#include <iostream>
#include <fstream>
#include "DataStructures.h"
#include "clsParking.h"
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
			to_string((int)s.getStationType())
		};
		return JoinString(arr ,"#//#");
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
		St.stationType = (enVehicleType) stoi(*ObjectList[7]);
		return St;
	}



public:

	

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
		markToDelete = true;
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

	

	static string JoinString(string* ArrString, string Delim)
	{
		string Results = "";

		if (ArrString != nullptr)
			for (int i = 0; ArrString != nullptr; i++)
			{
				Results += Delim + ArrString[i];
			}

		return Results.substr(Delim.length(), Results.length() - Delim.length());
	}
};

