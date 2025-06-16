
#pragma once

#include <iostream>
#include <fstream>
#include "DataStructures.h"
#include "clsVehicle.h"
#include "clsParking.h"
#include "clsTransportLine.h"
#include "clsVehicleTrip.h"
#include "clsPassenger.h"
#include "clsStation.h"


using namespace std;

class Database
{
public:
//
//static string clsVehicleFileName,clsParkingFileName;
//static string clsTransportLineFileName,clsVehicleTripFileName;
//static string clsPassengerFileName , clsStationFileName , clsVehcilDriverFileName;


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



template<class Item>
static void saveTransportLines(string filename, OpenHash<Item, clsTransportLine>& transportLines) {
    ofstream outFile(filename);
    
    for (int i = 0; i < transportLines.getCapicty(); i++) {
         Node<clsTransportLine>* current = transportLines.getHead(i);
         while (current != nullptr) {
                outFile << current->item.toString() << endl;
                current = current->next;
          }
          }
        outFile.close();
 }

static OpenHash<int, clsTransportLine> loadTransportLines(string filename) {
    OpenHash<int, clsTransportLine> transportLines;
    OpenHash<int, clsStation> stations= clsStation::GetAllStationsOpen();
    
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        try {
            clsTransportLine tl =clsTransportLine::parse(line, stations);
            transportLines.insert(tl.getId(), tl);
            
            if (clsTransportLine::getNumberOfAllTransportLine() < tl.getId()) {
                clsTransportLine::setNumberOfAllTransportLine(tl.getId());
            }
        } catch (...) {
            continue;
        }
    }
    
    return transportLines;
}

static OpenHash<string, clsTransportLine> loadTransportLinesByName(string filename) {
    OpenHash<string, clsTransportLine> transportLines;
    OpenHash<int, clsStation> stations = clsStation::GetAllStationsOpen();

    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        try {
            clsTransportLine tl = clsTransportLine::parse(line, stations);
            string nameKey = tl.getName(); 
            transportLines.insert(nameKey, tl);
            
            if (clsTransportLine::getNumberOfAllTransportLine() < tl.getId()) {
                clsTransportLine::setNumberOfAllTransportLine(tl.getId());
            }
        } catch (...) {
            continue;
        }
    }
    
    return transportLines;
}

static void saveParkings(string& filename, OpenHash<int, clsParking>& parkings) {
    ofstream outFile(filename);
    
    for (int i = 0; i < parkings.getCapicty(); i++) {
        Node<clsParking> *current = parkings.getHead(i);
        while (current != nullptr) {
            outFile << current->item.toString() << endl;
            current = current->next;
        }
    }
    
    outFile.close();
}


static OpenHash<int, clsParking> loadParkings(string filename) {
    OpenHash<int, clsParking> parkings;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        try {
            clsParking parking =clsParking::parse(line);
            parkings.insert(parking.getId(), parking);
            
            if (clsParking::getNumberOfAllParking() < parking.getId()) {
                clsParking::setNumberOfAllParking(parking.getId());
            }
        } catch (...) {
            continue;
        }
    }

    return parkings;
}



static void saveVehicles(string& filename, OpenHash<int, clsVehicle>& vehicles) {
    ofstream outFile(filename);
    
    for (int i = 0; i < vehicles.getCapicty(); i++) {
        Node <int, clsVehicle> *current = vehicles.getHead(i);
        while (current != nullptr) {
            outFile << current->item.toString() << endl;
            current = current->next;
        }
    }
    
    outFile.close();
}

static OpenHash<int, clsVehicle> loadVehicles(string filename) {
    OpenHash<int, clsVehicle> vehicles;
    OpenHash<int, clsVehicleTrip> vehicleTrip=loadVehicleTrips(Database::clsVehicleTripFileName);
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        try {
            clsVehicle vehicle =clsVehicle::parse(line,vehicleTrip);
            vehicles.insert(vehicle.getId(), vehicle);
            
            if (clsVehicle::getNumberOfAllVehicle() < vehicle.getId()) {
                clsVehicle::setNumberOfAllVehicle(vehicle.getId());
            }
        } catch (...) {
            continue;
        }
    }

    return vehicles;
}

template<class Item>
static void savePassengers(string& filename, OpenHash<Item, clsPassenger>& passengers) {
     ofstream outFile(filename);
        
     for (int i = 0; i < passengers.capacity; i++) {
            HashNode<<Item, clsPassenger> *current = passengers.array[i].getHead();
            while (current != nullptr) {
                outFile << current->data.item.toString() << endl;
                current = current->next;
            }
        }
        
        outFile.close();
}

static OpenHash<int, clsPassenger> loadPassengers(string filename) {
    OpenHash<int, clsPassenger> passengers;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        try {
            clsPassenger passenger =clsPassenger::parse(line);
            passengers.insert(passenger.getId(), passenger);
            
            if (clsPassenger::getNumberOfAllPassenger() < passenger.getId()) {
                clsPassenger::setNumberOfAllPassenger(passenger.getId());
            }
        } catch (...) {
            continue;
        }
    }

    return passengers;
}

static OpenHash<string, clsPassenger> loadPassengersByName(string filename) {
    OpenHash<string, clsPassenger> passengers;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        try {
            clsPassenger passenger = clsPassenger::parse(line);
            string fullNameKey = passenger.GetFullName();
            passengers.insert(fullNameKey, passenger);
            
            if (clsPassenger::getNumberOfAllPassenger() < passenger.getId()) {
                clsPassenger::setNumberOfAllPassenger(passenger.getId());
            }
        } catch (...) {
            continue;
        }
    }

    return passengers;
}

static void saveVehicleTrips(const string& filename, OpenHash<int, clsVehicleTrip>& trips) {
    ofstream outFile(filename);
    
    for (int i = 0; i < trips.capacity; i++) {
        HashNode<int, clsVehicleTrip> *current = trips.getHead(i);
        while (current != nullptr) {
            outFile << current->data.item.toString() << endl;
            current = current->next;
        }
    }
    
    outFile.close();
}

static OpenHash<int, clsVehicleTrip> loadVehicleTrips(const string& filename) {
    OpenHash<int, clsVehicleTrip> trips;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        try {
            clsVehicleTrip trip =clsVehicleTrip::parse(line);
            trips.insert(trip.getId(), trip);
            
            if (clsVehicleTrip::getNumberOfAllVehicleTrip() < trip.getId()) {
                clsVehicleTrip::setNumberOfAllVehicleTrip(trip.getId());
            }
        } catch (...) {
            continue;
        }
    }

    return trips;
    }

};
string clsVehicleFileName="Vehicles.txt";
string clsParkingFileName="Parkings.txt";
string clsTransportLineFileName="TransportLines.txt";
string clsVehicleTripFileName="VehicleTrips.txt";
string clsPassengerFileName="Passengers.txt";
string clsStationFileName = "Stations.txt";
string clsVehcilDriverFileName = "VehcilDrivers.txt";
