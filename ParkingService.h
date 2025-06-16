
#pragma once

#include "clsParking.h"
#include "Database.h"
#include "Input.h"
#include <iostream>

class ParkingService {
public:

    void addNewParking() {
        OpenHash<int, clsParking> parkings = Database::loadParkings(Database::clsParkingFileName);

        cout << "\n===========================================\n";
        cout << "           Add New Parking";
        cout << "\n===========================================\n";

        double distance = Input::readDouble("Enter Distance To Next Parking: ");
        int stationId = Input::readInt("Enter Station ID: ");
        int typeChoice = Input::ReadIntNumberBetween(1, 3, "Enter Parking Type (1: Bus, 2: Train, 3: Tram): ");
        enVehicleType parkingType = static_cast<enVehicleType>(typeChoice);
        int transportLineId = Input::readInt("Enter Transport Line ID: ");

        clsParking newParking(distance, stationId, parkingType, transportLineId);
        parkings.insert(newParking.getId(), newParking);

        Database::saveParkings(Database::clsParkingFileName, parkings);

        cout << "\nParking added successfully with ID: " << newParking.getId() << "\n";
    }

    void deleteParking() {
        OpenHash<int, clsParking> parkings = Database::loadParkings(Database::clsParkingFileName);

        cout << "\n===========================================\n";
        cout << "           Delete Parking";
        cout << "\n===========================================\n";

        int id = Input::readInt("Enter Parking ID to delete: ");

        if (parkings.remove(id)) {
            Database::saveParkings(Database::clsParkingFileName, parkings);
            cout << "\nParking deleted successfully.\n";
        }
        else {
            cout << "\nParking with ID " << id << " not found.\n";
        }
    }

    void printAllParkings() {
        OpenHash<int, clsParking> parkings = Database::loadParkings(Database::clsParkingFileName);

        if (parkings.isEmpty()) {
            cout << "\nNo Parkings Found!\n";
            return;
        }

        cout << "\n===========================================\n";
        cout << "           All Parkings (" << parkings.size() << ")";
        cout << "\n===========================================\n";

        for (int i = 0; i < parkings.capacity; i++) {
            HashNode<int, clsParking>* current = parkings.getHead(i);
            while (current != nullptr) {
                printParkingInfo(current->data.item);
                current = current->next;
            }
        }
    }

private:
    void printParkingInfo(const clsParking& parking) {
        cout << "\nID: " << parking.getId();
        cout << "\nStation ID: " << parking.getStationId();
        cout << "\nDistance To Next: " << parking.getDistanceToNext();
        cout << "\n-------------------------------------------\n";
    }
};
