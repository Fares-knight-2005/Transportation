
#pragma once

#include "clsPassengerTrip.h"
#include "Database.h"
#include "clsTransportLine.h"
#include "Input.h"

using namespace std;

class PassengerTripService {
public:
        void addNewPassengerTrip() {
        OpenHash<int, clsTransportLine>  transportLines= Database::loadTransportLines(Database::clsTransportLineFileName);
        OpenHash<int , clsPassenger> passengers = Database::loadPassengersByName(Database::clsPassengerFileName);

        cout << "\n===========================================\n";
        cout << "        Add New Passenger Trip";
        cout << "\n===========================================\n";
        clsTransportLine *transportLine;
        clsPassenger *passenger;

        while(true){
        int lineId= Input::readInt("Enter Line ID: ");
        transportLine=transportLines[lineId];
        if(transportLine==nullptr)
             cout << "\nTransport Line not found!\n";
        else
            break;
        }

        while(true){
        int startStation = Input::readInt("Enter Start Station ID: ");
        int endStation = Input::readInt("Enter End Station ID: ");
        int passengerId = Input::readInt("Enter Passenger ID: ");
        passenger=passengers[passengerId]
        if(transportLine.getStations[startStation]==nullptr||transportLine.setStations[endStation]==nullptr||passenger==nullptr)
             cout<< "The information provided is inaccurate. \n";   
        else
             break;
        }

        
        bool isHeading = Input::readBool();
        bool isDisabled = Input::readBool();
        bool hasItems = Input::readBool();
        bool transportingItems = Input::readBool();

        clsPassengerTrip newTrip(startStation, endStation, passengerId, isHeading, isDisabled, hasItems, 0);
        bool r=setPrice(transportLine.getPirce(),&passenger.getCard(),transportingItems);
        if(r)
        {
        trips.insert(newTrip.getPassengerId(), newTrip);
        cout << "\nPassenger Trip added successfully for Passenger ID: " << newTrip.getPassengerId() << "\n";
        }
        else
        cout<< "You do not have enough credit. \n";
    }

};
