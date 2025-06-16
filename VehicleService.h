
#pragma once

#include "clsVehicle.h"
#include "Database.h"
#include "Input.h"

using namespace std;

class VehicleService {
public:
    void printAllVehicles() {
        OpenHash<int, clsVehicle> vehicles = Database::loadVehicles(Database::clsVehicleFileName);

        if (vehicles.isEmpty()) {
            cout << "\nNo Vehicles Found!\n";
            return;
        }
      
        cout << "\n===========================================\n";
        cout << "        All Vehicles (" << vehicles.size() << ")";
        cout << "\n===========================================\n"; 

        for (int i = 0; i < vehicles.capacity; i++) {
            HashNode<int, clsVehicle>* current = vehicles.getHead(i);
            while (current != nullptr) {
                current->data.item.displayVehicleInfo();
                current = current->next;
            }
        }
    }

    void addNewVehicle() {
        OpenHash<int, clsVehicle> vehicles = Database::loadVehicles(Database::clsVehicleFileName);
        OpenHash<int, clsTransportLine> transportLines = Database::loadTransportLines(Database::clsTransportLineFileName);
        
        cout << "\n===========================================\n";
        cout << "        Add New Vehicle";
        cout << "\n===========================================\n";

        cout << "\nVehicle Types:\n";
        cout << "1. BUS\n";
        cout << "2. TRAM\n";
        cout << "3. FERRY\n";
        cout << "4. METRO\n";
                
        int typeChoice = Input::ReadIntNumberBetween(1, 4, "Invalid choice. Enter 1-4: ");
        enVehicleType vehicleType = static_cast<enVehicleType>(typeChoice - 1);
        while(true){
        int lineId = Input::readInt("Enter Transport Line ID: ");
        clsTransportLine  line=*transportLines[lineId];
        if(line==nullptr)
            cout<< "There is no line with this ID. \n";
        else if(vehicleType!=line.getVehicleType())
            cout<< "The Transport line type does not match the added vehicle. \n";
        else 
        {
            line.setNumberOfVehicles(getNumberOfVehicles()++);
            break;
        }    
        }
        int capacity = Input::readInt("Enter Vehicle Capacity: ");
        float speed = Input::readFloat("Enter Vehicle Speed (km/h): ");
        int disabilitySeats = Input::readInt("Enter Disability Seats Count: ");
        int packageSize = Input::readInt("Enter Package Size Capacity: ");
        int driverId = Input::readInt("Enter Driver ID (0 if none): ");

        clsVehicle newVehicle(vehicleType, lineId, capacity, speed, disabilitySeats, packageSize);
        if (driverId > 0) {
            newVehicle.setDriverId(driverId);
        }

        vehicles.insert(newVehicle.getId(), newVehicle);

        cout << "\nVehicle added successfully with ID: " << newVehicle.getId() << "\n";
        Database::saveVehicles(Database::clsVehicleFileName, vehicles);
        Database::saveTransportLines(Database::clsTransportLineFileName,transportLines);
    }

    void deleteVehicle() {
        cout << "\n===========================================\n";
        cout << "        Delete Vehicle";
        cout << "\n===========================================\n";

        int id = Input::readInt("Enter Vehicle ID to delete (0 to cancel): ");
        if (id == 0) 
            return;

        OpenHash<int, clsVehicle> vehicles = Database::loadVehicles(Database::clsVehicleFileName);
        OpenHash<int, clsTransportLine> transportLines = Database::loadTransportLines(Database::clsTransportLineFileName);
        
        bool success = vehicles.remove(id);

        if (success) {
            int lineId=vehicles[id]->getIdTransportLine();
            transportLines[lineId]->setNumberOfVehicles(getNumberOfVehicles()++);
            Database::saveVehicles(Database::clsVehicleFileName, vehicles);
            Database::saveTransportLines(Database::clsTransportLineFileName,transportLines);
            cout << "\nVehicle deleted successfully.\n";
        } else {
            cout << "\nVehicle not found!\n";
        }
    }

    void updateVehicle() {
        cout << "\n===========================================\n";
        cout << "        Update Vehicle";
        cout << "\n===========================================\n";

        int id = Input::readInt("Enter Vehicle ID to update (0 to cancel): ");
        if (id == 0) 
            return;

        OpenHash<int, clsVehicle> vehicles = Database::loadVehicles(Database::clsVehicleFileName);
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
           OpenHash<int, clsTransportLine> transportLines = Database::loadTransportLines(Database::clsTransportLineFileName);
           while(true){
             int lineId = Input::readInt("Enter Transport Line ID: ");
             clsTransportLine  line=*transportLines[lineId];
             if(line==nullptr)
                 cout<< "There is no line with this ID. \n";
            else if(vehicle.getVehicleType()!=line.getVehicleType())
                  cout<< "The Transport line type does not match the added vehicle. \n";
            else {
            line.setNumberOfVehicles(getNumberOfVehicles()++);
            break; }}
            }
            case 2: {
                int newCapacity = Input::readInt("Enter new Capacity: ");
                vehicle->setCapacity(newCapacity);
                break;
            }
            case 3: {
                float newSpeed = Input::readFloat("Enter new Speed: ");
                vehicle->setSpeed(newSpeed);
                break;
            }
            case 4: {
                int newDisabilitySeats = Input::readInt("Enter new Disability Seats count: ");
                vehicle->setDisabilitySeats(newDisabilitySeats);
                break;
            }
            case 5: {
                int newPackageSize = Input::readInt("Enter new Package Size: ");
                vehicle->setPackageSize(newPackageSize);
                break;
            }
            case 6: {
                int newDriverId = Input::readInt("Enter new Driver ID (0 to remove): ");
                vehicle->setDriverId(newDriverId);
                break;
            }
        }

        Database::saveVehicles(Database::clsVehicleFileName, vehicles);
        cout << "\nVehicle updated successfully.\n";
    }

};
