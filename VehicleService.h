
#pragma once

#include "clsVehicle.h"
#include "clsVehicleTrip.h"
#include "DataStructures.h"
#include "clsTransportLine.h"
#include "clsVehicleDriver.h"
#include "Input.h"
#include "TransportLineService.h"

using namespace std;

class VehicleService {
public:
    static void printAllVehicles() {
        DoubleLinkedList<clsVehicle> vehicles = clsVehicle::GetAllVehicles();

        if (vehicles.isEmpty()) {
            cout << "\nNo Vehicles Found!\n";
            return;
        }

        cout << "\n===========================================\n";
        cout << "        All Vehicles (" << vehicles.size() << ")";
        cout << "\n===========================================\n";
        DoubleNode<clsVehicle>* current = vehicles.getHead();
            while (current != nullptr) {
                current->item.displayVehicleInfo();
                current = current->next;
            }

    }

    static void addNewVehicle() {
        OpenHash<int, clsVehicle> vehicles = clsVehicle::loadVehicles();
        OpenHash<int, clsTransportLine> transportLines = clsTransportLine::loadTransportLines();
        OpenHash<int, clsVehicleDriver> vehicleDrivers = clsVehicleDriver::GetAllDriversOpen();

        if (transportLines.isEmpty())
        {
            cout << "There is no TransportLines. \n";
            return;
        }

        if(vehicleDrivers.isEmpty())
        {
            cout << "There is no vehicle Drivers. \n";
            return;
        }

        cout << "\n===========================================\n";
        cout << "        Add New Vehicle";
        cout << "\n===========================================\n";

        cout << "\nVehicle Types:\n";
        cout << "1. BUS\n";
        cout << "2. TRAM\n";
        cout << "3. FERRY\n";
        cout << "4. METRO\n";
        int lineId = 0;
        int typeChoice = Input::ReadIntNumberBetween(1, 4, "Invalid choice. Enter 1-4: ","Enter Vehicle Type: ");
        enVehicleType vehicleType = static_cast<enVehicleType>(typeChoice - 1);
        TransportLineService::printAllTransportLines();
        while(true){
        lineId = Input::readInt("Invalid input. Please enter a number : ","Enter Transport Line ID (0 to cancel):");
        if(lineId==0)
            return;

        clsTransportLine  *line=transportLines[lineId];
        if (line == nullptr)
        {
            cout << "There is no line with this ID. \n";
            continue;
        }
        else if(vehicleType==line->getVehicleType())
            cout<< "The Transport line type does not match the added vehicle. \n";
        else
        {
            line->setNumberOfVehicles(line->getNumberOfVehicles()+1);
            break;
        }
        }

        clsVehicleDriver  *driver;
        int driverId;
        while(true){
        driverId = Input::readInt("Invalid input. Please enter a number : ","Enter Driver ID (0 to cancel): ");
        if(driverId==0)
            return;
        driver=vehicleDrivers[driverId];
        if (driver == nullptr)
        {
            cout << "There is no driver with this ID. \n";
        }
        else
            break;
        }

        int capacity = Input::readInt("Invalid input. Please enter a number : ","Enter Vehicle Capacity: ");
        float speed = Input::readFloat("Enter Vehicle Speed (km/h): ");
        int disabilitySeats = Input::readInt("Invalid input. Please enter a number : ","Enter Disability Seats Count: ");
        int packageSize = Input::readInt("Invalid input. Please enter a number : ","Enter Package Size Capacity: ");


        clsVehicle newVehicle(vehicleType, lineId, capacity, speed, disabilitySeats, packageSize);
        newVehicle.setDriverId(driverId);
        driver->SetVehicleByID(newVehicle.getId());
//        driver->setMode(enDriverMode::Working);
        vehicles.insert(newVehicle.getId(), newVehicle);

        cout << "\nVehicle added successfully with ID: " << newVehicle.getId() << "\n";
        clsVehicle::saveVehcilsFromOpenHash(vehicles);
        clsTransportLine::saveTransportLinesFromOpenHash(transportLines);
        clsVehicleDriver::SaveAllFromOpenHash(vehicleDrivers);
    }

    static void deleteVehicle() {
        cout << "\n===========================================\n";
        cout << "        Delete Vehicle";
        cout << "\n===========================================\n";

        int id = Input::readInt("Invalid input. Please enter a number : ","Enter Vehicle ID to delete (0 to cancel): ");
        if (id == 0)
            return;

        OpenHash<int, clsVehicle> vehicles = clsVehicle::loadVehicles();
        OpenHash<int, clsTransportLine> transportLines = clsTransportLine::loadTransportLines();

        bool success = vehicles.remove(id);

        if (success) {
            cout << "\nVehicle deleted successfully.\n";
            clsVehicle::saveVehcilsFromOpenHash(vehicles);
            int lineId = vehicles[id]->getTransportLineId();
            clsTransportLine *line=transportLines[lineId];
            line->setNumberOfVehicles(line->getNumberOfVehicles()+1);
            clsTransportLine::saveTransportLinesFromOpenHash(transportLines);
        } else {
            cout << "\nVehicle not found!\n";
        }

    }

        static void search(){

        cout << "\n===========================================\n";
        cout << "        Search Vehicle";
        cout << "\n===========================================\n";

        OpenHash<int, clsVehicle> vehicles= clsVehicle::loadVehicles();

        int id = Input::readInt("Invalid input. Please enter a number : ","Enter Vehicle ID to delete (0 to cancel): ");
        if (id == 0)
            return;

        clsVehicle *s = vehicles[id];
        if (s==nullptr) {
            cout << "\nVehicle not found!\n";
            return;
        }
        else{
            s->displayVehicleInfo();
            return;
        }


        }



    static void updateVehicle() {
        cout << "\n===========================================\n";
        cout << "        Update Vehicle";
        cout << "\n===========================================\n";

        int id = Input::readInt("Invalid input. Please enter a number : ","Enter Vehicle ID to update (0 to cancel): ");
        if (id == 0)
            return;

        OpenHash<int, clsVehicle> vehicles = clsVehicle::loadVehicles();
        OpenHash<int, clsVehicleDriver> vehicleDrivers = clsVehicleDriver::GetAllDriversOpen();
        clsVehicle* vehicle = vehicles[id];

        if (vehicle == nullptr) {
            cout << "\nVehicle not found!\n";
            return;
        }

        vehicle->displayVehicleInfo();
        cout << "\nWhat would you like to update?\n";
        cout << "1. Transport Line ID\n";
        cout << "2. Capacity\n";
        cout << "3. Speed\n";
        cout << "4. Disability Seats\n";
        cout << "5. Package Size\n";
        cout << "6. Driver ID\n";
        cout << "0. Cancel\n";

        int choice = Input::ReadIntNumberBetween(0, 6, "Invalid choice. Enter 0-6: ");
        if (choice == 0) return;

        switch (choice) {
            case 1: {
           OpenHash<int, clsTransportLine> transportLines = clsTransportLine::loadTransportLines();
           TransportLineService::printAllTransportLines();
           while(true){
             int lineId = Input::readInt("Invalid input. Please enter a number : ","Enter Transport Line ID ((0 to cancel)): ");
             if(lineId==0)
                return;
             clsTransportLine  *line=transportLines[lineId];
            if(line==nullptr){
             cout<< "There is no line with this ID. \n";
             continue;
             }
            else if(vehicle->getVehicleType()!=line->getVehicleType())
                  cout<< "The Transport line type does not match the added vehicle. \n";
            else {
            line->setNumberOfVehicles(line->getNumberOfVehicles()+1);
            break; }}
            break;
            }
            case 2: {
                int newCapacity = Input::readInt("Invalid input. Please enter a number : ","Enter new Capacity: ");
                vehicle->setCapacity(newCapacity);
                break;
            }
            case 3: {
                float newSpeed = Input::readFloat("Enter new Speed: ");
                vehicle->setSpeed(newSpeed);
                break;
            }
            case 4: {
                int newDisabilitySeats = Input::readInt("Invalid input. Please enter a number : ","Enter new Disability Seats count: ");
                vehicle->setDisabilitySeats(newDisabilitySeats);
                break;
            }
            case 5: {
                int newPackageSize = Input::readInt("Invalid input. Please enter a number : ","Enter new Package Size: ");
                vehicle->setPackageSize(newPackageSize);
                break;
            }
            case 6: {

           clsVehicleDriver  *driver;
           while(true){
           int driverId = Input::readInt("Invalid input. Please enter a number : ","Enter new Driver ID (0 to cancel): ");
           if(driverId==0)
                 return;
           driver=vehicleDrivers[driverId];
           if (driver == nullptr)
            {
            cout << "There is no driver with this ID. \n";
            }
            else
                 break;
            }
            driver->SetVehicleByID(vehicle->getId());
                break;
            }
            }

        clsVehicle::saveVehcilsFromOpenHash(vehicles);
        clsVehicleDriver::SaveAllFromOpenHash(vehicleDrivers);
        cout << "\nVehicle updated successfully.\n";
    }




};
