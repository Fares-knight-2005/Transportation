
#pragma once

#include "clsVehicleTrip.h"
#include "clsVehicle.h"
#include "clsTransportLine.h"
#include "Database.h"
#include "Input.h"

using namespace std;

class VehicleTripService {
public:
    void printAllVehicleTrips() {
        OpenHash<int, clsVehicleTrip> trips = Database::loadVehicleTrips(Database::clsVehicleTripFileName);

        if (trips.isEmpty()) {
            cout << "\nNo Vehicle Trips Found!\n";
            return;
        }
      
        cout << "\n===========================================\n";
        cout << "        All Vehicle Trips (" << trips.size() << ")";
        cout << "\n===========================================\n"; 

        for (int i = 0; i < trips.capacity; i++) {
            HashNode<int, clsVehicleTrip>* current = trips.getHead(i);
            while (current != nullptr) {
                current->data.item.displayInfo();
                cout << "-------------------------\n";
                current = current->next;
            }
        }
    }

    void addNewVehicleTrip() {
        OpenHash<int, clsVehicleTrip> trips = Database::loadVehicleTrips(Database::clsVehicleTripFileName);
        OpenHash<int, clsVehicle> vehicles = Database::loadVehicles(Database::clsVehicleFileName);
        OpenHash<int, clsTransportLine> transportLines = Database::loadTransportLines(Database::clsTransportLineFileName);
        
        cout << "\n===========================================\n";
        cout << "        Add New Vehicle Trip";
        cout << "\n===========================================\n";

        int idVehicle;
        while (true) {
            idVehicle = Input::readInt("Enter Vehicle ID: ");
            clsVehicle* vehicle = vehicles[idVehicle];
            if (vehicle == nullptr) {
                cout << "Error: No vehicle found with this ID!\n";
                continue;
            }
            break;
        }

        int idTransportLine;
        int numberOfStations = 0;
        while (true) {
            idTransportLine = Input::readInt("Enter Transport Line ID: ");
            clsTransportLine* line = transportLines[idTransportLine];
            if (line == nullptr) {
                cout << "Error: No transport line found with this ID!\n";
                continue;
            }
            
            numberOfStations = line->getStations().size();
            if (numberOfStations == 0) {
                cout << "Error: This transport line has no stations!\n";
                continue;
            }
            
            clsVehicle* vehicle = vehicles[idVehicle];
            if (vehicle->getVehicleType() != line->getVehicleType()) {
                cout << "Error: Vehicle type doesn't match transport line type!\n";
                continue;
            }
            
            break;
        }

        clsVehicleTrip newTrip(numberOfStations);
        newTrip.idVehicle = idVehicle;
        newTrip.idTransportLine = idTransportLine;
// هون ضل تابع صغير مشان نحفظ تحركات المركبة
        trips.insert(newTrip.getId(), newTrip);

        cout << "\nVehicle Trip added successfully with ID: " << newTrip.getId() << "\n";
        Database::saveVehicleTrips(Database::clsVehicleTripFileName, trips);
    }

};
