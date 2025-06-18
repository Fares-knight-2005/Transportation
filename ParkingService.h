
#pragma once


#include "clsParking.h"
#include "Input.h"
#include <iostream>
#include"DataStructures.h"

class ParkingService {
public:


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
