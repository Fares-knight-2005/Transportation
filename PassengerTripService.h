
#pragma once

#include <iostream>
#include "clsPassengerTrip.h"
#include "DataStructures.h"
#include "clsPassenger.h"
#include "clsTransportLine.h"
#include "clsStation.h"
#include "Input.h"

using namespace std;

class PassengerTripService {
public:
        static void addNewPassengerTrip() {

        OpenHash<int,clsTransportLine>  transportLines = clsTransportLine::loadTransportLines();
        OpenHash<int, clsPassenger> passengers = clsPassenger::loadPassengers();

        cout << "\n===========================================\n";
        cout << "        Add New Passenger Trip";
        cout << "\n===========================================\n";

        clsTransportLine *transportLine;
        clsPassenger *passenger;

        int lineId;
        while(true){
        lineId= Input::readInt("Invalid input. Please enter a number : ","Enter Line ID (0 to cancel): ");
        if(lineId==0)
            return;
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
        startStation = Input::readInt("Invalid input. Please enter a number : ","Enter Start Station ID (0 to cancel): ");
        endStation = Input::readInt("Invalid input. Please enter a number : ","Enter End Station ID (0 to cancel): ");
        passengerId = Input::readInt("Invalid input. Please enter a number : ","Enter Passenger ID (0 to cancel): ");
        if(startStation==0||endStation==0||passengerId==0)
            return;
        passenger = passengers[passengerId];
        if(stations.find(startStation)==nullptr||stations.find(endStation)==nullptr||passenger==nullptr)
             cout<< "The information provided is inaccurate. \n";
        else
             break;
        }


        bool isHeading = stations.isBigger(endStation,startStation);
        bool isDisabled = passenger->getDisabled();
        bool hasItems = Input::readBool("Does he own things? ");
        bool transportingItems = Input::readBool("Do you want to move things for $5 ? ");

        clsPassengerTrip newTrip(startStation, endStation, passengerId, isHeading, isDisabled, hasItems, 0.0);
        clsCard *c = passenger->getCard();
        bool r= newTrip.setPrice(transportLine->getPirce(),c, transportingItems);
        if(r)
        {
            DoubleLinkedList<clsStation> s = transportLine->getStations();
            clsStation* d = s.find(startStation);
            d->addPassengerTrip(lineId,newTrip);

        cout << "\nPassenger Trip added successfully for Passenger ID: " << newTrip.getPassengerId() << "\n";
        }
        else
        cout<< "You do not have enough credit. \n";

    }

};
