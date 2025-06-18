
#pragma once

#include "DataStructures.h"
#include "clsVehicle.h"
#include "clsPassengerTrip.h"
#include <sstream>


 string clsParkingFileName = "Parkings.txt";



class clsParking{



private:

    Queue<clsVehicle> Vehicle;
    Queue<clsPassengerTrip> passengers;
    int id, stationId, idTransportLine;
    double distanceToNext;
    enVehicleType parkingType;
    static int numberOfAllParking;

    public:

        clsParking()
        {
            id = 0;
        }


    clsParking(int id, double distanceToNext,int stationId,enVehicleType parkingType,int idTransportLine, Queue<clsPassengerTrip> passengers) :id(id), distanceToNext(distanceToNext),stationId(stationId),
    idTransportLine(idTransportLine) {
        this->passengers = passengers;
        this->parkingType=parkingType;
    }
    clsParking(double distanceToNext, int stationId, enVehicleType parkingType, int idTransportLine) :id(++numberOfAllParking), distanceToNext(distanceToNext), stationId(stationId),
        parkingType(parkingType), idTransportLine(idTransportLine) {}

    double getDistanceToNext(){
        return distanceToNext;
    }

    bool operator==(int id){
        return this->id==id;
    }

    int getStationId(){
        return stationId;
    }

    int getId(){
       return id;
    }

    void addPassengerTrip(clsPassengerTrip trip) {
        passengers.enqueue(trip);
    }

    clsPassengerTrip* getPassengerTrip(){
        return passengers.dequeue();
    }

    void addVehicle(clsVehicle v){
        Vehicle.enqueue(v);
    }

    int getnumberOfAllVehicle(){
        return this->Vehicle.size();
    }

    int getLineId()
    {
        return this->idTransportLine;
    }

    static clsParking *Find(int id)
    {
        OpenHash <int ,clsParking> oh = clsParking::loadParkings();

        return oh[id];
    }

    bool hasPassengers(){
        return !passengers.isEmpty();
    }

    Queue <clsPassengerTrip>* GetPassengerQueue()
    {
        return &passengers;
    }

   static int getNumberOfAllParking(){
          return numberOfAllParking;
    }

    static void setNumberOfAllParking(int n){
          numberOfAllParking=n;
    }

    void printParkingInfo(){
        cout << "\nID: " << getId();
        cout << "\nStation ID: " << getStationId();
        cout << "\nDistance To Next: " << getDistanceToNext();
        cout << "\n-------------------------------------------\n";
    }

    string toString() {
    ostringstream oss;
    oss<< id<< ",,,"<< stationId<< ",,," << distanceToNext << ",,,"  << static_cast<int>(parkingType)<< ",,," << idTransportLine;
    while (!passengers.isEmpty())
          oss << ",,," << passengers.dequeue()->toString();
    return oss.str();
    }

    static clsParking parse(string line) {
             DoubleLinkedList<string> tokens = Input::Split(line,",,,");
          
             if (tokens.size() < 5) {
                 throw invalid_argument("Not enough tokens in line");
             }
          
             int id = stoi(*tokens[0]);
             int stationId = stoi(*tokens[1]);
             double distance = stoi(*tokens[2]);
             enVehicleType type = static_cast<enVehicleType>(stoi(*tokens[3]));
             int idTransportLine= stoi(*tokens[4]);
             Queue<clsPassengerTrip> passengers;

             for (int i = 5; i < tokens.size(); ) {
          
                     int start = stoi(*tokens[i++]);
                     int end = stoi(*tokens[i++]);
                     int passengerId = stoi(*tokens[i++]);
                     bool heading = (*tokens[i++] == "1");
                     bool disabled = (*tokens[i++] == "1");
                     bool items = (*tokens[i++] == "1");
                     bool destination = (*tokens[i++] == "1");
                     float price = stof(*tokens[i++]);
          
                     clsPassengerTrip trip(start, end, passengerId, heading, disabled, items, destination , price);
                     passengers.enqueue(trip);
             }
          
             return clsParking(id, distance, stationId, type, idTransportLine, passengers);
    }




    static void saveParkings(DoubleLinkedList <clsParking> Parkings)
    {
        fstream TripsFile;

        TripsFile.open(clsParkingFileName, ios::out);

        if (TripsFile.is_open())
        {
            for (int i = 0; i < Parkings.size(); i++)
            {
                if (Parkings[i] != nullptr)
                {
                    clsParking p = *Parkings[i];
                    string Line = p.toString();
                    TripsFile << Line << endl;
                }
            }

            TripsFile.close();
        }
    }

    void Add()
    {
        fstream MyFile;
        MyFile.open(clsParkingFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << this->toString() << endl;
            MyFile.close();
        }
    }

    template <typename Key>
    static void saveParkingsFromOpenHash(OpenHash <Key, clsParking> Parkings)
    {
        fstream ParhingsFile;

        ParhingsFile.open(clsParkingFileName, ios::out);

        if (ParhingsFile.is_open())
        {
            for (int i = 0; i < Parkings.getCapicty(); i++) {
                Node <HashNode<Key, clsParking>>* d = Parkings.getHead(i);
                while (d != nullptr) {
                    ParhingsFile << d->item.item.toString() << endl;
                    d = d->next;
                }
            }

            ParhingsFile.close();
        }
    }

    static DoubleLinkedList <clsParking> GetAllParkings()
    {
        DoubleLinkedList <clsParking> AllParkings;

        fstream MyFile;
        MyFile.open(clsParkingFileName, ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsParking Trip = parse(Line);
                AllParkings.addLast(Trip);
            }

            MyFile.close();

        }


        return AllParkings;

    }


    static OpenHash<int, clsParking> loadParkings() {
        OpenHash<int, clsParking> parkings;
        ifstream file(clsParkingFileName);
        string line;

        while (getline(file, line)) {
            try {
                clsParking parking = clsParking::parse(line);
                parkings.insert(parking.getId(), parking);

                if (clsParking::getNumberOfAllParking() < parking.getId()) {
                    clsParking::setNumberOfAllParking(parking.getId());
                }
            }
            catch (...) {
                continue;
            }
        }

        return parkings;
    }



};
int clsParking::numberOfAllParking=0;

