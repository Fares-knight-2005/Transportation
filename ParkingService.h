
#pragma once


#include "clsParking.h"
#include "Input.h"
#include "clsStation.h"
#include <iostream>
#include"DataStructures.h"

class ParkingService {
public:

    static void addNewParking(int lineId,clsStation &s) {

        OpenHash<int,clsParking> parkings=clsParking::loadParkings();

        cout << "\n===========================================\n";
        cout << "           Add New Parking";
        cout << "\n===========================================\n";

        double distance = Input::readDouble("Enter Distance To Next Parking: ");
        cout<<"Enter Parking Type (1: BUS, 2: TRAM, 3: FERRY, 4: METRO): \n";
        int typeChoice = Input::ReadIntNumberBetween(1, 3);
        enVehicleType parkingType = static_cast<enVehicleType>(typeChoice);

        clsParking newParking(distance,s.getid(),parkingType,lineId);
        s.addParking(lineId,newParking);
        parkings.insert(newParking.getId(),newParking);
        clsParking::saveParkingsFromOpenHash(parkings);
        cout << "\nParking added successfully with ID: " << newParking.getId() << "\n";
    }

    static void deleteParking(int lineId,clsStation &s) {
        s.removeParking(lineId);
    }

    static void printAllParkings() {
        DoubleLinkedList<clsParking> parkings = clsParking::GetAllParkings();
        if (parkings.isEmpty()) {
            cout << "\nNo Parkings Found!\n";
            return;
        }

        cout << "\n===========================================\n";
        cout << "           All Parkings (" << parkings.size() << ")";
        cout << "\n===========================================\n";

            DoubleNode<clsParking>* current = parkings.getHead();
            while (current != nullptr) {
                current->item.printParkingInfo();
                current = current->next;
            }

    }

};
