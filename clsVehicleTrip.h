#pragma once

#include<iostream>
#include "clsPassengerTrip.h"
#include <sstream>
#include <string>
#include "DataStructures.h"
#include "Input.h"
#include<fstream>

using namespace std;
string clsVehicleTripFileName = "VehicleTrips.txt";

    struct strVehicleMovements {
        int idStation;
        int currDisabilitSeat, currPackageSize;
        SingleLinkedList<clsPassengerTrip> passengers;

        strVehicleMovements(int idStation) : idStation(idStation), currPackageSize(0), currDisabilitSeat(0) {}
        strVehicleMovements() : idStation(0), currPackageSize(0), currDisabilitSeat(0) {}

        string toString() {
            ostringstream oss;
            oss << idStation;

            Node<clsPassengerTrip>* current = passengers.getHead();
            while (current != nullptr) {
                oss << ",,," << current->item.toString();
                current = current->next;
            }

            return oss.str();
        }
    };

class clsVehicleTrip {

    int id, numberOfStations, idVehicle, idTransportLine;
    ClosedHash<int, strVehicleMovements> vehicleMovements;
    static int numberOfAllVehicleTrip;

public:

    clsVehicleTrip(int numberOfStations,int idVehicle,int idTransportLine)
    {
        this->id = ++numberOfAllVehicleTrip;
        this->idVehicle = idVehicle;
        this->idTransportLine = idTransportLine;
        this->numberOfStations = numberOfStations;
        vehicleMovements=ClosedHash<int, strVehicleMovements>(numberOfStations);
    }

    clsVehicleTrip() {

    }

    clsVehicleTrip(int id,int numberOfStations, int idVehicle, int idTransportLine)
    {
        this->id = id;
        this->idVehicle = idVehicle;
        this->idTransportLine = idTransportLine;
        this->numberOfStations = numberOfStations;
        vehicleMovements=ClosedHash<int, strVehicleMovements>(numberOfStations);
    }

    static int getNumberOfAllVehicleTrip(){
          return numberOfAllVehicleTrip;
    }


    strVehicleMovements *insertVehicleMovements(int idStation){

        strVehicleMovements *curr=this->vehicleMovements[idStation];

        if(curr!=nullptr)
            return curr;

        strVehicleMovements movement(idStation);
        vehicleMovements.insert(idStation,movement);
        return &movement;
    }



    static void setNumberOfAllVehicleTrip(int n){
          numberOfAllVehicleTrip=n;
    }

    int getId() { return id; }

    void setIdVehicle(int idVehicle) {
        this->idVehicle = idVehicle;
    }

    void setIdTransportLine(int idTransportLine) {
        this->idTransportLine = idTransportLine;
    }

    void setNumberOfStations(int numberOfStations) {
        this -> numberOfStations = numberOfStations;
    }

    strVehicleMovements *getVehicleMovements(int idStation){
        return vehicleMovements[idStation];
    }

    string toString() {
        ostringstream oss;
        oss << id << ",,," << numberOfStations << ",,," << idVehicle << ",,," << idTransportLine;

        for(int i = 0; i < vehicleMovements.size(); i++) {
            strVehicleMovements *curr = vehicleMovements.getNode(i);
            if (curr != nullptr) {
                oss << ",,," << curr->toString();
            }
        }
        return oss.str();
    }

    void displayInfo() {
        cout << "**************************************\n";
        cout << "       Vehicle Trip Information      \n";
        cout << "**************************************\n";
        cout << "Trip ID: " << id << "\n";
        cout << "TransportLine ID: "<< idTransportLine << "\n";
        cout << "Vehicle ID: "<< idVehicle << "\n";
        cout << "number of stations: " << numberOfStations << "\n\n";

        for (int i = 0; i < vehicleMovements.size(); i++) {
            strVehicleMovements *node = vehicleMovements.getNode(i);
            if (node != nullptr) {
                cout << "Current Station: " << node->idStation << "\n";
                cout << "Passengers List:\n";
                cout << "----------------\n";

                Node<clsPassengerTrip>* current = node->passengers.getHead();
                int passengerCount = 1;

                while (current != nullptr) {
                    cout << passengerCount++ << ". ";
                    current->item.displayInfo();
                    cout << "----------------\n";
                    current = current->next;
                }
                cout << "**************************************\n";
            }
        }
    }

    static clsVehicleTrip parse(string line) {
        DoubleLinkedList<string> tokens = Input::Split(line, ",,,");
        if (tokens.size() < 4) {
            throw invalid_argument("Not enough tokens in line");
        }

        int id = stoi(*tokens[0]);
        int numberOfStations = stoi(*tokens[1]);
        int idVehicle = stoi(*tokens[2]);
        int idTransportLine = stoi(*tokens[3]);

        clsVehicleTrip trip(id, numberOfStations, idVehicle, idTransportLine);

        int tokenIndex = 4;
        while (tokenIndex < tokens.size()) {
            int stationId = stoi(*tokens[tokenIndex++]);
            strVehicleMovements movement(stationId);

            while (tokenIndex + 5 < tokens.size()) {
                try {
                    int start = stoi(*tokens[tokenIndex++]);
                    int end = stoi(*tokens[tokenIndex++]);
                    int pid = stoi(*tokens[tokenIndex++]);
                    bool disabled = *tokens[tokenIndex++] == "1";
                    bool items = *tokens[tokenIndex++] == "1";
                    bool destenation = *tokens[tokenIndex++] == "1";
                    float price = stoi(*tokens[tokenIndex++]);

                    clsPassengerTrip passenger(start, end, pid , disabled, items, destenation ,price);
                    movement.passengers.addLast(passenger);
                } catch (...) {
                    break;
                }
            }

            trip.vehicleMovements.insert(stationId, movement);
        }

        return trip;
    }


    void Add()
    {
        fstream MyFile;
        MyFile.open(clsVehicleTripFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << this->toString() << endl;
            MyFile.close();
        }
    }

    static void saveVehcileTrips(DoubleLinkedList <clsVehicleTrip> VehicleTrips)
    {
        fstream TripsFile;

        TripsFile.open(clsVehicleTripFileName, ios::out);

        if (TripsFile.is_open())
        {
            for (int i = 0; i < VehicleTrips.size(); i++)
            {
                if (VehicleTrips[i] != nullptr)
                {
                    clsVehicleTrip p = *VehicleTrips[i];
                    string Line = p.toString();
                    TripsFile << Line << endl;
                }
            }

            TripsFile.close();
        }
    }


    template <typename Key>
    static void saveVehcilsFromOpenHash(OpenHash <Key, clsVehicleTrip> Vehciles)
    {
        fstream ParhingsFile;

        ParhingsFile.open(clsVehicleTripFileName, ios::out);

        if (ParhingsFile.is_open())
        {
            for (int i = 0; i < Vehciles.getCapicty(); i++) {
                Node <HashNode<Key, clsVehicleTrip>>* d = Vehciles.getHead(i);
                while (d != nullptr) {
                    ParhingsFile << d->item.item.toString() << endl;
                    d = d->next;
                }
            }

            ParhingsFile.close();
        }
    }


    static DoubleLinkedList <clsVehicleTrip> GetAllVehicleTrips()
    {
        DoubleLinkedList <clsVehicleTrip> AllVehicleTrips;

        fstream MyFile;
        MyFile.open(clsVehicleTripFileName, ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsVehicleTrip Trip = parse(Line);
                AllVehicleTrips.addLast(Trip);
            }

            MyFile.close();

        }

        return AllVehicleTrips;

    }



    static OpenHash<int, clsVehicleTrip> loadVehicleTrips() {
        OpenHash<int, clsVehicleTrip> trips;
        ifstream file(clsVehicleTripFileName);
        string line;

        while (getline(file, line)) {
            try {
                clsVehicleTrip trip = clsVehicleTrip::parse(line);
                trips.insert(trip.getId(), trip);

                if (clsVehicleTrip::getNumberOfAllVehicleTrip() < trip.getId()) {
                    clsVehicleTrip::setNumberOfAllVehicleTrip(trip.getId());
                }
            }
            catch (...) {
                continue;
            }
        }

        return trips;
    }

};

int clsVehicleTrip::numberOfAllVehicleTrip = 0;
