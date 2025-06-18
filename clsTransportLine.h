
#pragma once

#include <iostream>
#include "DataStructures.h"
#include "clsStation.h"
#include "clsVehicle.h"
#include <sstream>
#include "Input.h"

using namespace std;

string clsTransportLineFileName = "TransportLines.txt";

class clsTransportLine
{
private:


    DoubleLinkedList<clsStation> stations;
    string name;
    int id, numberOfVehicles;
    double price;
    enVehicleType vehicleType;
    static int numberOfAllTransportLines;

public:
    clsTransportLine(double price, enVehicleType vehicleType, string name, DoubleLinkedList<clsStation> stations) :
        stations(stations), price(price), id(++numberOfAllTransportLines), vehicleType(vehicleType),
        numberOfVehicles(0), name(name) {}

    clsTransportLine(int id, int numberOfVehicles, double price, enVehicleType vehicleType, string name, DoubleLinkedList<clsStation> stations) :
        id(id),numberOfVehicles(numberOfVehicles), price(price), vehicleType(vehicleType),name(name),stations(stations) {}

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

    DoubleNode<clsStation>* getFirstStation() {
        return  stations.getHead();
    }

    bool operator==(int id) {
        return this->id == id;
    }

    bool operator==(string name) {
        return this->name == name;
    }

    enVehicleType getVehicleType() {
        return vehicleType;
    }

    int getId() {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    double getPirce() {
        return price;
    }

    DoubleLinkedList<clsStation> getStations() {
        return stations;
    }

    void setNumberOfVehicles(int n) {
        numberOfVehicles = n;
    }

    int getNumberOfVehicles() {
        return numberOfVehicles;
    }

    void display() {
        cout << "\nTransport Line Information\n";
        cout << "--------------------------\n";
        cout << "Line ID: " << id << "\n";
        cout << "Line Name: " << name << "\n";
        cout << "Number of Vehicles: " << numberOfVehicles << "\n";
        cout << "Price : " << price << " $\n";
        cout << "vehicle Type : " <<::getVehicleType(vehicleType) << "\n";
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

    static int getNumberOfAllTransportLine() {
        return numberOfAllTransportLines;
    }

    static void setNumberOfAllTransportLine(int n) {
        numberOfAllTransportLines = n;
    }

    void setName(string name) {
        this->name = name;
    }

    void setPrice(int p) {
        price = p;
    }

    string getName() {
        return name;
    }


    string toString() {
        ostringstream oss;
        oss << id << ",,," << numberOfVehicles << ",,," << price << ",,," << (int)vehicleType << ",,," << name;
        for (int i = 0; i < stations.size(); i++)
            oss << ",,," << stations[i]->getid();
        return oss.str();
    }

    static clsTransportLine parse(string line, OpenHash<int, clsStation>& stations) {
        DoubleLinkedList<string> tokens = Input::Split(line, ",,,");
        if (tokens.size() < 5) {
            throw invalid_argument("Not enough tokens in line");
        }

        int id = stoi(*tokens[0]);
        int vehicles = stoi(*tokens[1]);
        double price = stod(*tokens[2]);
        enVehicleType type = static_cast<enVehicleType>(stoi(*tokens[3]));
        string name = *tokens[4];

        DoubleLinkedList<clsStation> stationList;
        for (int i = 5; i < tokens.size(); i++) {
            int stationId = stoi(*tokens[i]);
            clsStation* station = stations[stationId];
            if (station != nullptr) {
                stationList.addLast(*station);
            }
        }
        clsTransportLine t(id,vehicles,price, type, name, stationList);

        return t;
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


    template <typename Key>
    static void saveTransportLinesFromOpenHash(OpenHash <Key, clsTransportLine> Transports)
    {
        fstream PassengerFile;


        PassengerFile.open(clsTransportLineFileName, ios::out);

        if (PassengerFile.is_open())
        {
            for (int i = 0; i < Transports.getCapicty(); i++) {
                Node <HashNode<Key, clsTransportLine>>* d = Transports.getHead(i);
                while (d != nullptr) {
                    PassengerFile << d->item.item.toString() << endl;
                    d = d->next;
                }
            }

            PassengerFile.close();
        }
    }



    static DoubleLinkedList <clsTransportLine> GetTransportLines()
    {
        DoubleLinkedList <clsTransportLine> AllLines;

        fstream MyFile;
        MyFile.open(clsTransportLineFileName, ios::in);

        if (MyFile.is_open())
        {
            string Line;
            OpenHash<int, clsStation> s = clsStation::GetAllStationsOpen();

            while (getline(MyFile, Line))
            {
                clsTransportLine Trip = parse(Line, s);
                AllLines.addLast(Trip);
            }

            MyFile.close();

        }

        return AllLines;

    }

    void Add()
    {
        fstream MyFile;
        MyFile.open(clsTransportLineFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << this->toString() << endl;
            MyFile.close();
        }
    }


    static OpenHash<int, clsTransportLine> loadTransportLines() {

        OpenHash<int, clsTransportLine> transportLines;
        OpenHash<int, clsStation> stations = clsStation::GetAllStationsOpen();

        fstream file;
        file.open(clsTransportLineFileName, ios::in);
        string line;


        while (getline(file, line)) {
            try {

                clsTransportLine t1=clsTransportLine::parse(line,stations);

                transportLines.insert(t1.getId(),t1);


                if (clsTransportLine::getNumberOfAllTransportLine() < t1.getId()) {
                    clsTransportLine::setNumberOfAllTransportLine(t1.getId());
               }
            }
            catch (...) {
                continue;
            }
        }

        return transportLines;
    }

    static OpenHash<string, clsTransportLine> loadTransportLinesByName() {
        OpenHash<string, clsTransportLine> transportLines;
        OpenHash<int, clsStation> stations = clsStation::GetAllStationsOpen();

        ifstream file(clsTransportLineFileName);
        string line;

        while (getline(file, line)) {
            try {
                clsTransportLine tl = clsTransportLine::parse(line, stations);
                string nameKey = tl.getName();
                transportLines.insert(nameKey, tl);

                if (clsTransportLine::getNumberOfAllTransportLine() < tl.getId()) {
                    clsTransportLine::setNumberOfAllTransportLine(tl.getId());
                }
            }
            catch (...) {
                continue;
            }
        }

        return transportLines;
    }

};
int clsTransportLine::numberOfAllTransportLines = 0;
