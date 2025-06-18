
#pragma once

#include "clsVehicleTrip.h"
#include "DataStructures.h"
#include "clsVehicle.h"
#include "clsTransportLine.h"
#include "VehicleService.h"
#include "TransportLineService.h"
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

    static void search(){

        cout << "\n===========================================\n";
        cout << "        Search Vehicle Trip";
        cout << "\n===========================================\n";

        OpenHash<int, clsVehicleTrip> trips= clsVehicleTrip::loadVehicleTrips();

        int id = Input::readInt("Invalid input. Please enter a number : ","Enter Vehicle Trip ID to delete (0 to cancel): ");
        if (id == 0)
            return;

        clsVehicleTrip *s = trips[id];
        if (s==nullptr) {
            cout << "\nVehicle Trip not found!\n";
            return;
        }
        else{
            s->displayInfo();
            return;
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
        VehicleService::printAllVehicles();
        while (true) {
            idVehicle = Input::readInt("Invalid input. Please enter a number : ","Enter Vehicle ID (0 to cancel): ");
            if(idVehicle==0)
                return;
            clsVehicle* vehicle = vehicles[idVehicle];
            if (vehicle == nullptr) {
                cout << "Error: No vehicle found with this ID!\n";
                continue;
            }
            break;
        }

        int idTransportLine=0;
        int numberOfStations = 0;
        TransportLineService::printAllTransportLines();
        while (true) {
            idTransportLine = Input::readInt("Invalid input. Please enter a number : ","Enter Transport Line ID (0 to cancel):");
            clsTransportLine* line = transportLines[idTransportLine];

            if(idTransportLine==0)
                return;

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
