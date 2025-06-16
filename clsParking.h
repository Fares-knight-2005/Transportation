
#pragma once

#include "DataStructures.h"
#include "clsVehicle.h"
#include "clsPassengerTrip.h"
#include <sstream>

class clsParking{



private:

    Queue<clsVehicle> Vehicle;
    Queue<clsPassengerTrip> passengers;
    int id, stationId, idTransportLine;
    double distanceToNext;
    enVehicleType parkingType;
    static int numberOfAllParking;
     
    public:
   
    clsParking(int id, double distanceToNext,int stationId,enVehicleType parkingType,int idTransportLine, Queue<clsPassengerTrip> passengers) :id(id), distanceToNext(distanceToNext),stationId(stationId),
    idTransportLine(idTransportLine) {
        this->passengers = passengers;
        this->parkingType=parkingType;
    }
    clsParking(double distanceToNext, int stationId, enVehicleType parkingType, int idTransportLine) :id(++numberOfAllParking), distanceToNext(distanceToNext), stationId(stationId),
        parkingType(parkingType), idTransportLine(idTransportLine) {}
          
    double getDistanceToNext(){
        return distanceToNext;
    }

    bool operator==(int id){
        return this->id==id;
    }

    int getStationId(){
        return stationId;    
    }

    int getId(){
       return id;    
    }

    void addPassengerTrip(clsPassengerTrip trip) {
        passengers.enqueue(trip);
    }

   static int getNumberOfAllParking(){
          return numberOfAllParking;     
    }

    static void setNumberOfAllParking(int n){
          numberOfAllParking=n;
    }
         
    string toString() {
    ostringstream oss;
    oss<< id<< ",,,"<< stationId<< ",,," << distanceToNext << ",,,"  << static_cast<int>(parkingType)<< ",,," << idTransportLine;
    while (!passengers.isEmpty())
          oss << ",,," << passengers.dequeue()->toString();
    return oss.str();
    }

    static clsParking parse(string line) {
    DoubleLinkedList<string> tokens = Database::Split(line,",,,");
         
    if (tokens.size() < 5) {
        throw invalid_argument("Not enough tokens in line");
    }

    int id = stoi(*tokens[0]);
    int stationId = stoi(*tokens[1]);
    double distance = stoi(*tokens[2]);
    enVehicleType type = static_cast<enVehicleType>(stoi(*tokens[3]));
    int idTransportLine= stoi(*tokens[4]);
    Queue<clsPassengerTrip> passengers;
    for (int i = 5; i < tokens.size(); ) {
            
            int start = stoi(*tokens[i++]);
            int end = stoi(*tokens[i++]);
            int passengerId = stoi(*tokens[i++]);
            bool heading = (*tokens[i++] == "1");
            bool disabled = (*tokens[i++] == "1");
            bool items = (*tokens[i++] == "1");
            float price = stof(*tokens[i++]);
            
            clsPassengerTrip trip(start, end, passengerId, heading, disabled, items, price);
            passengers.enqueue(trip);
    }
         
    return clsParking(id, distance, stationId, type, idTransportLine, passengers);
    }
};
int clsParking::numberOfAllParking=0;

