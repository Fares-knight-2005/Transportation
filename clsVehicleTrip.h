#pragma once

#include<iostream>
#include "clsPassengerTrip.h"
#include "DataStructures.h"
#include <sstream>
#include <string>


using namespace std;
string clsVehicleTripFileName = "VehicleTrips.txt";


class clsVehicleTrip {

 
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

    int id, numberOfStations, idVehicle, idTransportLine;
    ClosedHash<int, strVehicleMovements> vehicleMovements;
    static int numberOfAllVehicleTrip;

public:
    clsVehicleTrip(int numberOfStations) : 
        id(++numberOfAllVehicleTrip), 
        numberOfStations(numberOfStations),
        idVehicle(0),
        idTransportLine(0) {
        vehicleMovements = ClosedHash<int, strVehicleMovements>(numberOfStations);
    }

    clsVehicleTrip(int id, int numberOfStations) : 
        id(id), 
        numberOfStations(numberOfStations),
        idVehicle(0),
        idTransportLine(0) {
        vehicleMovements = ClosedHash<int, strVehicleMovements>(numberOfStations);          
    }

   static int getNumberOfAllVehicleTrip(){
          return numberOfAllVehicleTrip;     
    }

    static void setNumberOfAllVehicleTrip(int n){
          numberOfAllVehicleTrip=n;
    }

    int getId() { return id; }
 
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
        DoubleLinkedList<string> tokens = Split(line, ",,,");
        if (tokens.size() < 4) {
            throw invalid_argument("Not enough tokens in line");
        }
        
        int id = stoi(*tokens[0]);
        int numberOfStations = stoi(*tokens[1]);
        int idVehicle = stoi(*tokens[2]);
        int idTransportLine = stoi(*tokens[3]);
        
        clsVehicleTrip trip(id, numberOfStations);
        trip.idVehicle = idVehicle;
        trip.idTransportLine = idTransportLine;
        
        int tokenIndex = 4;
        while (tokenIndex < tokens.size()) {
            int stationId = stoi(*tokens[tokenIndex++]);
            strVehicleMovements movement(stationId);
           
            while (tokenIndex + 5 < tokens.size()) {
                try {
                    int start = stoi(*tokens[tokenIndex++]);
                    int end = stoi(*tokens[tokenIndex++]);
                    int pid = stoi(*tokens[tokenIndex++]);
                    bool heading = *tokens[tokenIndex++] == "1";
                    bool disabled = *tokens[tokenIndex++] == "1";
                    bool items = *tokens[tokenIndex++] == "1";
                    float price = stoi(*tokens[tokenIndex++]);
                    
                    clsPassengerTrip passenger(start, end, pid, heading, disabled, items ,price);
                    movement.passengers.addLast(passenger);
                } catch (...) {
                    break;
                }
            }
            
            trip.vehicleMovements.insert(stationId, movement);
        }
        
        return trip;
    }


    static OpenHash<int, clsVehicle> loadVehicles(string filename) {
        OpenHash<int, clsVehicle> vehicles;
        OpenHash<int, clsVehicleTrip> vehicleTrip = loadVehicleTrips(Database::clsVehicleTripFileName);

        ifstream file(filename);
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


    static void saveVehicleTrips(const string& filename, OpenHash<int, clsVehicleTrip>& trips) {
        ofstream outFile(filename);

        for (int i = 0; i < trips.capacity; i++) {
            Node<int, clsVehicleTrip>* current = trips.getHead(i);
            while (current != nullptr) {
                outFile << current->item.toString() << endl;
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
