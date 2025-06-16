
#pragma once

#include "clsTransportLine.h"
#include "Database.h"
#include "Input.h"

using namespace std;

class TransportLineService {


public:
    static void printAllTransportLines() {
        OpenHash<int, clsTransportLine> transportLines = Database::loadTransportLines(Database::clsTransportLineFileName);

        if (transportLines.isEmpty()) {
            cout << "\nNo Transport Lines Found!\n";
            return;
        }
      
        cout << "\n===========================================\n";
        cout << "        All Transport Lines (" << transportLines.size() << ")";
        cout << "\n===========================================\n"; 

        for (int i = 0; i < transportLines.capacity; i++) {
            HashNode<clsTransportLine> *current = transportLines.getHead(i);
            while (current != nullptr) {
                current->data.item.display();
                current = current->next;
            }
        }
    }

    static void addNewTransportLine() {
        OpenHash<string, clsTransportLine> transportLines=Database::loadTransportLinesByName(Database::clsTransportLineFileName);
        OpenHash<int, clsStation> stations = Database::loadStations(Database::clsStationFileName);
      
        cout << "\n===========================================\n";
        cout << "        Add New Transport Line";
        cout << "\n===========================================\n";
        
        while(true){
        string name = Input::readString("Enter Transport Line Name: ");
        if(transportLines[name]!=nullptr)
                cout << "This name is already in use. You should use a unique name. \n";
        else
                break;
        }
        
        double price = Input::readDouble("Enter Ticket Price: ");
        
        cout << "\nVehicle Types:\n";
        cout << "1. BUS\n";
        cout << "2. TRAM\n";
        cout << "3. FERRY\n";
        cout << "4. METRO\n";
                
        int typeChoice = Input::ReadIntNumberBetween(1, 4, "Invalid choice. Enter 1-4: ");
        enVehicleType vehicleType = static_cast<enVehicleType>(typeChoice - 1);

        DoubleLinkedList<clsStation> lineStations;
        if (!stations.isEmpty()) {// طباعة كل المحطات من كلاس خدمات المحطة 
            cout << "\nAvailable Stations:\n";
            for (int i = 0; i < stations.capacity; i++) {
                DoubleNode<clsStation> *current = stations.getHead(i);
                while (current != nullptr) {
                    cout << current->data.item.getId() << " - " << current->data.item.getName() << endl;
                    current = current->next;
                }
            }

            bool addMore = Input::readBool("Are there any stations to add? (yes/no): ", "yes", "no");
            while (addMore) {
                int stationId = Input::readInt("Enter Station ID to add to line: ");
                clsStation* station = stations[stationId];
                if (station != nullptr) {
                    lineStations.addLast(*station);
                    cout << "Station added successfully.\n";
                } else {
                    cout << "Station not found!\n";
                }
                addMore = Input::readBool("Add another station? (yes/no): ", "yes", "no");
            }
        }

        clsTransportLine newLine(price, vehicleType, name, lineStations);
        transportLines.insert(newLine.getId(), newLine);

        cout << "\nTransport Line added successfully with ID: " << newLine.getId() << "\n";
        Database::saveTransportLines(Database::clsTransportLineFileName, transportLines);
    }

    static void deleteTransportLine() {
       
        cout << "\n===========================================\n";
        cout << "        Delete Transport Line";
        cout << "\n===========================================\n";

        cout << "\nSearch by:\n";
        cout << "1. ID\n";
        cout << "2. Name\n";
        cout << "3. Exit\n";
        
        int choice = Input::ReadIntNumberBetween(1, 3, "Invalid choice. Enter 1-2: ");

        switch(choice){
            case 1:{
        OpenHash<int, clsTransportLine> transportLines=Database::loadTransportLines(Database::clsTransportLineFileName);
        int id = Input::readInt("Enter Transport Line ID to delete (0 to cancel): ");
        if (id == 0) 
            return;

        clsTransportLine* line = remove(id);
        if (line == nullptr) {
            cout << "\nTransport Line not found!\n";
            return;
        }
        else if{
            cout << "\nTransport Line deleted successfully.\n";
            Database::saveTransportLines(Database::clsTransportLineFileName, transportLines);
            return;
        }
        break;
        }
            case 2:{
        OpenHash<string, clsTransportLine> transportLines=Database::loadTransportLinesByName(Database::clsTransportLineFileName);
        string name = Input::readString("Enter Transport Line Name to delete : ");

        clsTransportLine* line = remove(name);
        if (line == nullptr) {
            cout << "\nTransport Line not found!\n";
            return;
        }
        else if{
            cout << "\nTransport Line deleted successfully.\n";
             Database::saveTransportLines(Database::clsTransportLineFileName, transportLines);
            return;
        }  
        }  
      }
    }

    static void updateTransportLine() {
        cout << "\n===========================================\n";
        cout << "        Update Transport Line";
        cout << "\n===========================================\n";

        cout << "\nSearch by:\n";
        cout << "1. ID\n";
        cout << "2. Name\n";
        cout << "3. Exit\n";
        
        int choice = Input::ReadIntNumberBetween(1, 3, "Invalid choice. Enter 1-3: ");
        if (choice == 3) 
            return;

        clsTransportLine* lineToUpdate = nullptr;
        OpenHash<int, clsTransportLine> transportLinesById;
        OpenHash<string, clsTransportLine> transportLinesByName;

        if (choice == 1) {
            transportLinesById = Database::loadTransportLines(Database::clsTransportLineFileName);
            int id = Input::readInt("Enter Transport Line ID to update: ");
            lineToUpdate = transportLinesById[id];
        }
        else {
            transportLinesByName = Database::loadTransportLinesByName(Database::clsTransportLineFileName);
            string name = Input::readString("Enter Transport Line Name to update: ");
            lineToUpdate = transportLinesByName[name];
        }

        if (lineToUpdate == nullptr) {
            cout << "\nTransport Line not found!\n";
            return;
        }

        lineToUpdate->display();
        cout << "\nWhat would you like to update?\n";
        cout << "1. Name\n";
        cout << "2. Price\n";
        cout << "3. Stations\n";
        cout << "0. Cancel\n";

        int updateChoice = Input::ReadIntNumberBetween(0, 4, "Invalid choice. Enter 0-4: ");
        if (updateChoice == 0) 
            return;

        switch (updateChoice) {
            case 1: {
                string newName = Input::readString("Enter new name: ");
                lineToUpdate->setName(newName);
                break;
            }
            case 2: {
                double newPrice = Input::readDouble("Enter new price: ");
                lineToUpdate->setPrice(newPrice);
                break;
            }
            case 3: {
                TransportLineService::updateStations(*lineToUpdate);
                break;
            }
        }

    
        if (choice == 1) {
            Database::saveTransportLines(Database::clsTransportLineFileName, transportLinesById);
        }
        else {
            Database::saveTransportLines(Database::clsTransportLineFileName,transportLinesByName);
        }

        cout << "\nTransport Line updated successfully.\n";
    }

private:
    static void updateStations(clsTransportLine& line) {
        OpenHash<int, clsStation> stations = Database::loadStations(Database::clsStationFileName);
        
        while (true) {
            cout << "\nCurrent Stations in this line:\n";
            DoubleNode<clsStation> *currentStation = line.getFirstStation();
            while (currentStation != nullptr) {
                cout << currentStation->item.getId() << " - " << currentStation->item.getName() << endl;
                currentStation = currentStation->next;
            }

            cout << "\nStation Operations:\n";
            cout << "1. Add Station\n";
            cout << "2. Remove Station\n";
            cout << "0. Back\n";

            int choice = Input::ReadIntNumberBetween(0, 2, "Invalid choice. Enter 0-2: ");
            if (choice == 0) 
                break;

            if (choice == 1) {
                cout << "\nAvailable Stations:\n";// طباعة كل المحطات بكلاس طلاعة تبع الخدمات
                for (int i = 0; i < stations.capacity; i++) {
                    HashNode<clsStation> *current = stations.getHead(i);
                    while (current != nullptr) {
                        cout << current->data.item.getId() << " - " << current->data.item.getName() << endl;
                        current = current->next;
                    }
                }

                int stationId = Input::readInt("Enter Station ID to add: ");
                clsStation* station = stations[stationId];
                if (station != nullptr) {
                    int position = Input::readInt("Enter position (1 for first): ");
                    line.addStation(*station, position);
                    cout << "Station added successfully.\n";
                } else {
                    cout << "Station not found!\n";
                }
            }
            else {
                int stationId = Input::readInt("Enter Station ID to remove: ");
                line.removeStation(stationId);
            }
        }
    }
};
