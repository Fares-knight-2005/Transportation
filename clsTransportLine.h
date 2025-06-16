
#pragma once

#include "DataStructures.h"
#include "clsStation.h"
#include "clsVehicle.h"
#include <sstream>
#include "Input.h"

class clsTransportLine
{
private:
    static string clsTransportLineFileName = "TransportLines.txt";

    DoubleLinkedList<clsStation> stations;
    string name;
    int id, numberOfVehicles;
    double price;
    enVehicleType vehicleType;
    static int numberOfAllTransportLines;

public:
    clsTransportLine(double price, enVehicleType vehicleType, string name, DoubleLinkedList<clsStation> stations) :
        stations(stations), price(price), id(++numberOfAllTransportLines), vehicleType(vehicleType),
        numberOfVehicles(numberOfVehicles), name(name) {
    }

    clsTransportLine(int id, int numberOfVehicles, double price, enVehicleType vehicleType, string name, DoubleLinkedList<clsStation> stations) :
         id(id), stations(stations), price(price), vehicleType(vehicleType),
         numberOfVehicles(numberOfVehicles), name(name) {
    }

    clsTransportLine() : id(0), numberOfVehicles(0), price(0) {}

    void addStation(clsStation station, int stationNumber) {
        stations.add(stationNumber - 1, station);
    }

    void removeStation(int stationId) {
        if (stations.remove(stationId))
            cout << "The deletion process was completed successfully.\n";
        else
            cout << "The station ID number you entered is not available.\n";
    }

    DoubleNode<clsStation>* getFirstStation(){
            return  stations.getHead();
    }

    bool operator==(int id) {
        return this->id == id;
    }

    bool operator==(string name){
       return this->name==name;      
    }

    enVehicleType getVehicleType() {
        return vehicleType;
    }

    int getId(){
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    DoubleNode<clsStation> *getStations(){
         return stations.getHead();
    }

    void setNumberOfVehicles(int n){
         numberOfVehicles=n;     
    }

    int getNumberOfVehicles(){
        return numberOfVehicles;      
    }

    void display() {
        cout << "\nTransport Line Information\n";
        cout << "--------------------------\n";
        cout << "Line ID: " << id << "\n";
        cout << "Line Name: " << name << "\n";
        cout << "Number of Vehicles: " << numberOfVehicles << "\n";
        cout << "Price : " << price << " $\n";
        cout << ::getVehicleType(vehicleType) << "\n";
        if (stations.size() > 0) {
            cout << "Stations IDs: ";
            for (int i = 0; i < stations.size(); i++) {
                cout << stations[i]->getid();
                if (i < stations.size() - 1)
                    cout << ", ";
            }
            cout << "\n";
        }
        cout << "--------------------------\n";
    }

    static int getNumberOfAllTransportLine(){
          return numberOfAllTransportLines;     
    }

    static void setNumberOfAllTransportLine(int n){
          numberOfAllTransportLines=n;
    }

    string getName() {
        return name;
    }

    string toString() {
        ostringstream oss;
        oss << id << ",,," << numberOfVehicles << ",,," << price << ",,," << static_cast<int>(vehicleType) << ",,," << name;
        for (int i = 0; i < stations.size(); i++)
            oss << ",,," << stations[i]->getid();
        return oss.str();
    }

    static clsTransportLine parse(string line, OpenHash<int, clsStation>& stations) {
        DoubleLinkedList<string> tokens = Input::Split(line,",,,");
        if (tokens.size() < 5) {
            throw invalid_argument("Not enough tokens in line");
        }

        int id = stoi(*tokens[0]);
        int vehicles = stoi(*tokens[1]);
        double price = stod(*tokens[2]);
        enVehicleType type = static_cast<enVehicleType>(stoi(*tokens[3]));
        string name= *tokens[4];
        
        DoubleLinkedList<clsStation> stationList;
        for (int i = 5; i < tokens.size(); i++) {
            int stationId = stoi(*tokens[i]);
            clsStation* station = stations[stationId];
            if (station != nullptr) {
                stationList.addLast(*station);
            }
        }

        clsTransportLine tl(id, vehicles, price, type, name, stationList);
        return tl;
    }



    static void saveTransportLines(DoubleLinkedList <clsTransportLine> Lines)
    {
        fstream TripsFile;

        TripsFile.open(clsTransportLineFileName, ios::out);

        if (TripsFile.is_open())
        {
            for (int i = 0; i < Lines.size(); i++)
            {
                if (Lines[i] != nullptr)
                {
                    clsTransportLine p = *Lines[i];
                    string Line = p.toString();
                    TripsFile << Line << endl;
                }
            }

            TripsFile.close();
        }
    }


    static DoubleLinkedList <clsVehicle> GetTransportLines()
    {
        DoubleLinkedList <clsVehicle> AllLines;

        fstream MyFile;
        MyFile.open(clsTransportLineFileName, ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsTransportLine Trip = parse(Line);
                AllLines.addLast(Trip);
            }

            MyFile.close();

        }

        return AllLines;

    }



    //template<class Item>
    //static void saveTransportLines(string filename, OpenHash<Item, clsTransportLine>& transportLines) {
    //    ofstream outFile(filename);

    //    for (int i = 0; i < transportLines.getCapicty(); i++) {
    //        Node<clsTransportLine>* current = transportLines.getHead(i);
    //        while (current != nullptr) {
    //            outFile << current->item, toString() << endl;
    //            current = current->next;
    //        }
    //    }
    //    outFile.close();
    //}

    //static OpenHash<int, clsTransportLine> loadTransportLines(string filename) {
    //    OpenHash<int, clsTransportLine> transportLines;
    //    OpenHash<int, clsStation> stations = clsStation::GetAllStationsOpen();

    //    ifstream file(filename);
    //    string line;

    //    while (getline(file, line)) {
    //        try {
    //            clsTransportLine tl = clsTransportLine::parse(line, stations);
    //            transportLines.insert(tl.getId(), tl);

    //            if (clsTransportLine::getNumberOfAllTransportLine() < tl.getId()) {
    //                clsTransportLine::setNumberOfAllTransportLine(tl.getId());
    //            }
    //        }
    //        catch (...) {
    //            continue;
    //        }
    //    }

    //    return transportLines;
    //}

    //static OpenHash<string, clsTransportLine> loadTransportLinesByName(string filename) {
    //    OpenHash<string, clsTransportLine> transportLines;
    //    OpenHash<int, clsStation> stations = clsStation::GetAllStationsOpen();

    //    ifstream file(filename);
    //    string line;

    //    while (getline(file, line)) {
    //        try {
    //            clsTransportLine tl = clsTransportLine::parse(line, stations);
    //            string nameKey = tl.getName();
    //            transportLines.insert(nameKey, tl);

    //            if (clsTransportLine::getNumberOfAllTransportLine() < tl.getId()) {
    //                clsTransportLine::setNumberOfAllTransportLine(tl.getId());
    //            }
    //        }
    //        catch (...) {
    //            continue;
    //        }
    //    }

    //    return transportLines;
    //}

};

int clsTransportLine::numberOfAllTransportLines = 0;
