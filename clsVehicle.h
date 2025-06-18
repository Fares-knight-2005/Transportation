#pragma once

#include <iostream>
#include "DataStructures.h"
#include "clsPassengerTrip.h"
#include "clsVehicleTrip.h"
#include <sstream>

using namespace std;

string clsVehicleFileName = "Vehicles.txt";

enum enVehicleType {BUS=1, TRAM, FERRY, METRO};

string getVehicleType(enVehicleType vehicleType) {
    switch(vehicleType) {
        case BUS:  return "BUS";
        case TRAM: return "TRAM";
        case FERRY: return "FERRY";
        default: return "METRO";
    }
}

enVehicleType setVehicleType(int vehicleNumber){
    switch(vehicleNumber){
        case 1: return BUS;
        case 2: return TRAM;
        case 3: return FERRY;
        default: return METRO;
    }
}

class clsVehicle {
private:

    int id, transportLineId, driverId;
    int capacity, currSeats;
    float speed;
    int seatsForPeopleWithDisabilities, currDisabilitySeats;
    int packageSize, currPackageSize;
    bool destination;
    SingleLinkedList<clsVehicleTrip> vehicleTrips;
    static int numberOfAllVehicle;
    enVehicleType vehicleType;

public:
    clsVehicle(int id, enVehicleType type, int lineId, int cap, float spd, int disabilitySeats, int pkgSize) {
        this->id = id;
        vehicleType = type;
        transportLineId = lineId;
        capacity = cap;
        speed = spd;
        seatsForPeopleWithDisabilities = disabilitySeats;
        packageSize = pkgSize;
        currSeats = 0;
        currDisabilitySeats = 0;
        currPackageSize = 0;
        destination = false;
    }

    clsVehicle(){}

    clsVehicle(enVehicleType type, int lineId, int cap, float spd, int disabilitySeats, int pkgSize) {
        id = ++numberOfAllVehicle;
        vehicleType = type;
        transportLineId = lineId;
        capacity = cap;
        speed = spd;
        seatsForPeopleWithDisabilities = disabilitySeats;
        packageSize = pkgSize;
        currSeats = 0;
        currDisabilitySeats = 0;
        currPackageSize = 0;
        destination = false;
    }

    enVehicleType getVehicleType() { return vehicleType; }
    int getTransportLineId() { return transportLineId; }
    int getCapacity() { return capacity; }
    float getSpeed() { return speed; }
    int getDisabilitySeats() { return seatsForPeopleWithDisabilities; }
    int getPackageSize() { return packageSize; }
    int getId() { return id; }
    int getDriverId() { return driverId; }

    void setVehicleType(enVehicleType type) { vehicleType = type; }
    void setTransportLineId(int lineId) { transportLineId = lineId; }
    void setCapacity(int cap) { capacity = cap; }
    void setSpeed(float spd) { speed = spd; }
    void setDisabilitySeats(int seats) { seatsForPeopleWithDisabilities = seats; }
    void setPackageSize(int size) { packageSize = size; }
    void setId(int id) { this->id = id; }
    void setDriverId(int id) { driverId = id; }

    bool hasDisabilityAccess() {
        return seatsForPeopleWithDisabilities > currDisabilitySeats;
    }

    bool hasCapacity() {
        return capacity > currSeats;
    }

    bool hasPackageSpace() {
        return packageSize > currPackageSize;
    }

    static clsVehicle getVehicleByID(int id)
    {
        OpenHash <int, clsVehicle> AllVehicles = loadVehicles();

        return *AllVehicles[id];
    }

    static OpenHash<int, clsVehicle> loadVehicles() {
        OpenHash<int, clsVehicle> vehicles;
        OpenHash<int, clsVehicleTrip> vehicleTrip = clsVehicleTrip::loadVehicleTrips();

        ifstream file(clsVehicleFileName);
        string line;

        while (getline(file, line)) {
            try {
                clsVehicle vehicle = clsVehicle::parse(line, vehicleTrip);
                vehicles.insert(vehicle.getId(), vehicle);

                if (clsVehicle::getNumberOfAllVehicle() < vehicle.getId()) {
                    clsVehicle::setNumberOfAllVehicle(vehicle.getId());
                }
            }
            catch (...) {
                continue;
            }
        }

        return vehicles;
    }


    void Add()
    {
        fstream MyFile;
        MyFile.open(clsVehicleFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << this->toString() << endl;
            MyFile.close();
        }
    }

    static void saveVehciles(DoubleLinkedList <clsVehicle> Vehicle)
    {
        fstream TripsFile;

        TripsFile.open(clsVehicleFileName, ios::out);

        if (TripsFile.is_open())
        {
            for (int i = 0; i < Vehicle.size(); i++)
            {
                if (Vehicle[i] != nullptr)
                {
                    clsVehicle p = *Vehicle[i];
                    string Line = p.toString();
                    TripsFile << Line << endl;
                }
            }

            TripsFile.close();
        }
    }


    template <typename Key>
    static void saveVehcilsFromOpenHash(OpenHash <Key, clsVehicle> Vehciles)
    {
        fstream ParhingsFile;

        ParhingsFile.open(clsVehicleFileName, ios::out);

        if (ParhingsFile.is_open())
        {
            for (int i = 0; i < Vehciles.getCapicty(); i++) {
                Node <HashNode<Key, clsVehicle>>* d = Vehciles.getHead(i);
                while (d != nullptr) {
                    ParhingsFile << d->item.item.toString() << endl;
                    d = d->next;
                }
            }

            ParhingsFile.close();
        }
    }


    static DoubleLinkedList <clsVehicle> GetAllVehicles()
    {
        DoubleLinkedList <clsVehicle> AllVehicle;
        OpenHash<int, clsVehicleTrip> vehicleTrip = clsVehicleTrip::loadVehicleTrips();

        fstream MyFile;
        MyFile.open(clsVehicleFileName, ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsVehicle Trip = parse(Line , vehicleTrip);
                AllVehicle.addLast(Trip);
            }

            MyFile.close();

        }

        return AllVehicle;

    }



    //void addNewVehicleTrip(clsTransportLine line,clsVehicleTrip &trip){


    //DoubleNode<clsStation> *station=line.getFirstStation();
    //destination=true;// Heading to the end of the line

    //while(station!=nullptr||destination){
    //  
    //  clsParking *parking= station->item.getParking(line.getId());
    //  Stack<clsPassengerTrip> s;
    //  parking->addVehicle(*this);

    //  if(parking->getnumberOfAllVehicle()==1){

    //  while(hasCapacity()&&parking->hasPassengers()){
    //  clsPassengerTrip *passenger= parking->getPassengerTrip();
    //  strVehicleMovements *movement=trip.insertVehicleMovements(passenger->getStartStation());

    //  if(passenger->getDestination()==destination&&(!passenger->getDisabilityStatus()||hasDisabilityAccess())&&(!passenger->getItemsStatus()||hasPackageSpace())){


    //  currSeats++;
    //  if(passenger->getDisabilityStatus())
    //  {
    //  movement->currDisabilitSeat++;
    //  currDisabilitySeats++;
    //  }
    //  if(passenger->getItemsStatus())
    //  {
    //  movement->currPackageSize++;
    //  currPackageSize++;
    //  }
    //  }
    //  else
    //      s.push(*passenger);
    //  }

    //  if(!s.isEmpty())
    //      s.toQueue(parking->GetAllParkings());

    //  strVehicleMovements *curr=trip.getVehicleMovements(station->item.getid());
    //  if(curr!=nullptr)
    //  {
    //  currSeats-=movement->passengers.size();
    //  currDisabilitySeats-=movement->CurrDisability;
    //  movement->CurrDisability=0;
    //  currPackageSize-=movement->CurrPackageSize;
    //  movement->CurrPackageSize=0;
    //  }
    //  if(station->next==nullptr)
    //      destination=false;
    //  if(destination)
    //      station=station->next;
    //  else
    //      station=station->previous;

    //  parking->vehicle.dequeue();
    //  }
    //}

    //vehicleTrips.addFirst(trip);
    //}



   static int getNumberOfAllVehicle(){
          return numberOfAllVehicle;
    }

    static void setNumberOfAllVehicle(int n){
          numberOfAllVehicle=n;
    }

    void displayVehicleInfo() {
        cout << "\nVehicle Information:";
        cout << "\nId: " << id;
        cout << "\nDriver Id: " << driverId;
        cout << "\nType: " << ::getVehicleType(vehicleType);
        cout << "\nTransport Line ID: " << transportLineId;
        cout << "\nCapacity: " << capacity;
        cout << "\nSpeed: " << speed << " km/h";
        cout << "\nDisability Seats: " << seatsForPeopleWithDisabilities;
        cout << "\nPackage Size: " << packageSize << endl;
    }

    string toString() {
        ostringstream oss;
        oss << static_cast<int>(vehicleType) << ",,," << transportLineId << ",,,"
            << capacity << ",,," << speed << ",,," << seatsForPeopleWithDisabilities
            << ",,," << packageSize << ",,," << id << ",,," << driverId;

        Node<clsVehicleTrip>* current = vehicleTrips.getHead();
        while (current != nullptr) {
            oss << ",,," << current->item.getId();
            current = current->next;
        }

        return oss.str();
    }

    static clsVehicle parse(string line, OpenHash<int, clsVehicleTrip> vehicleTripHash) {
        DoubleLinkedList<string> tokens = Input::Split(line, ",,,");
        if (tokens.size() < 8) {
            throw invalid_argument("Not enough tokens in line");
        }

        enVehicleType type = static_cast<enVehicleType>(stoi(*tokens[0]));
        int lineId = stoi(*tokens[1]);
        int cap = stoi(*tokens[2]);
        float spd = stof(*tokens[3]);
        int disabilitySeats = stoi(*tokens[4]);
        int pkgSize = stoi(*tokens[5]);
        int id = stoi(*tokens[6]);
        int driverId = stoi(*tokens[7]);

        clsVehicle vehicle(id, type, lineId, cap, spd, disabilitySeats, pkgSize);
        vehicle.setDriverId(driverId);

        for (int i = 8; i < tokens.size(); i++) {
            int tripId = stoi(*tokens[i]);
            clsVehicleTrip* trip = vehicleTripHash[tripId];
            if (trip != nullptr) {
                vehicle.vehicleTrips.addLast(*trip);
            }
        }

        return vehicle;
    }


};

int clsVehicle::numberOfAllVehicle = 0;

