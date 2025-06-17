
#pragma once

#include "clsPassengerTrip.h"
#include "clsPassenger.h"
#include "clsTransportLine.h"
#include "clsStation.h"
#include "Input.h"

using namespace std;

class PassengerTripService {
public:
        void addNewPassengerTrip() {
            OpenHash<int, clsTransportLine>  transportLines = clsTransportLine::loadTransportLines();
            OpenHash<int, clsPassenger> passengers = clsPassenger::loadPassengers();


        cout << "\n===========================================\n";
        cout << "        Add New Passenger Trip";
        cout << "\n===========================================\n";
        clsTransportLine *transportLine;
        clsPassenger *passenger;
        
        int lineId;
        while(true){
        lineId= Input::readInt("Invalid input. Please enter a number : ","Enter Line ID: ");
        transportLine=transportLines[lineId];
        if(transportLine==nullptr)
             cout << "\nTransport Line not found!\n";
        else
            break;
        }

        DoubleLinkedList<clsStation> stations= transportLine->getStations();
        int startStation;
        int endStation,passengerId;

        while(true){
        startStation = Input::readInt("Invalid input. Please enter a number : ","Enter Start Station ID: ");
        endStation = Input::readInt("Invalid input. Please enter a number : ","Enter End Station ID: ");
        passengerId = Input::readInt("Invalid input. Please enter a number : ","Enter Passenger ID: ");
        passenger = passengers[passengerId];
        if(stations[startStation]==nullptr||stations[endStation]==nullptr||passenger==nullptr)
             cout<< "The information provided is inaccurate. \n";   
        else
             break;
        }

        
        bool isHeading = Input::readBool();
        bool isDisabled = Input::readBool();
        bool hasItems = Input::readBool();
        bool transportingItems = Input::readBool();

        clsPassengerTrip newTrip(startStation, endStation, passengerId, isHeading, isDisabled, hasItems, 0.0);
        clsCard c = passenger->getCard();
        bool r= newTrip.setPrice(transportLine->getPirce(), &c, transportingItems);
        if(r)
        {
            DoubleLinkedList<clsStation> s = transportLine->getStations();
            clsStation* d = s[startStation];
            d->addPassengerTrip(lineId,newTrip);
            
        cout << "\nPassenger Trip added successfully for Passenger ID: " << newTrip.getPassengerId() << "\n";
        }
        else
        cout<< "You do not have enough credit. \n";
    }

};
