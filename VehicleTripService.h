
#pragma once

#include "clsVehicleTrip.h"
#include "DataStructures.h"
#include "clsVehicle.h"
#include "clsTransportLine.h"
#include "Input.h"

using namespace std;

class VehicleTripService {
public:
    static void printAllVehicleTrips() {
        DoubleLinkedList<clsVehicleTrip> trips = clsVehicleTrip::GetAllVehicleTrips();

        if (trips.isEmpty()) {
            cout << "\nNo Vehicle Trips Found!\n";
            return;
        }
      
        cout << "\n===========================================\n";
        cout << "        All Vehicle Trips (" << trips.size() << ")";
        cout << "\n===========================================\n"; 

            DoubleNode<clsVehicleTrip>* current = trips.getHead();
            while (current != nullptr) {
                current->item.displayInfo();
                cout << "-------------------------\n";
                current = current->next;
            }
    }

    static void addNewVehicleTrip() {
        OpenHash<int, clsVehicle> vehicles = clsVehicle::loadVehicles();
        OpenHash<int, clsTransportLine> transportLines = clsTransportLine::loadTransportLines();
        
        cout << "\n===========================================\n";
        cout << "        Add New Vehicle Trip";
        cout << "\n===========================================\n";
        if (vehicles.isEmpty()){
            cout << "There is no Vehicles. ";
            return;
        }
        if (transportLines.isEmpty()) {
            cout << "There is no Transport Line. ";
            return;
        }

        int idVehicle=0;
        while (true) {
            idVehicle = Input::readInt("Enter Vehicle ID: ");
            clsVehicle* vehicle = vehicles[idVehicle];
            if (vehicle == nullptr) {
                cout << "Error: No vehicle found with this ID!\n";
                continue;
            }
            break;
        }

        int idTransportLine=0;
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

        
        clsVehicleTrip newTrip(numberOfStations, idVehicle, idTransportLine);
      
 
// هون ضل تابع صغير مشان نحفظ تحركات المركبة
        newTrip.Add();

        cout << "\nVehicle Trip added successfully with ID: " << newTrip.getId() << "\n";
 
    }

};
