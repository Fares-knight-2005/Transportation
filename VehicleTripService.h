
#pragma once

#include "clsVehicleTrip.h"
#include "DataStructures.h"
#include "clsVehicle.h"
#include "clsTransportLine.h"
#include "VehicleService.h"
#include "TransportLineService.h"
#include "VehicleService.h"
#include "clsStation.h"
#include "Input.h"

using namespace std;

class VehicleTripService {
public:

    static void recordingVehicleMovements(clsVehicle vehicle,clsTransportLine line,clsVehicleTrip &trip){

    vehicle.setDestination(true);
    DoubleNode<clsStation> *station=line.getFirstStation();

    while(station!=nullptr||vehicle.getDestination()){
    clsParking *parking= station->item.getParking(line.getId());
    if(parking==nullptr)
        cout<<"yes";
    cout<<parking->getId();
    Queue<clsPassengerTrip> s;
    parking->addVehicle(vehicle);

    if(parking->getnumberOfAllVehicle()==1){


    while(vehicle.hasCapacity()&&parking->hasPassengers()){
    clsPassengerTrip *passenger= parking->getPassengerTrip();
    strVehicleMovements *movement=trip.insertVehicleMovements(passenger->getStartStation());

    bool destination=vehicle.getDestination();
    bool hasDisablity=vehicle.hasDisabilityAccess();
    bool hasPackage=vehicle.hasPackageSpace();

    if(passenger->getDestination()==destination&&(!passenger->getDisabilityStatus()||hasDisablity)&&(!passenger->getItemsStatus()||hasPackage)){

    movement->passengers.addFirst(*passenger);
    vehicle.currSeats++;
    if(passenger->getDisabilityStatus()){
      movement->currDisabilitSeat++;
      vehicle.currDisabilitySeats++;
    }
    if(passenger->getItemsStatus()){
      movement->currPackageSize++;
      vehicle.currPackageSize++;
    }
    }
    else
        s.push(*passenger);
    }
    if(!s.isEmpty())
        parking->GetPassengerQueue()->addQueue(s);

    strVehicleMovements *curr=trip.getVehicleMovements(station->item.getid());
    if(curr!=nullptr){
      vehicle.currSeats-=curr->passengers.size();
      vehicle.currDisabilitySeats-=curr->currDisabilitSeat;
      curr->currDisabilitSeat=0;
      vehicle.currPackageSize-=curr->currPackageSize;
      curr->currPackageSize=0;
    }



      if(station->next==nullptr)
          vehicle.setDestination(false);
      if(vehicle.getDestination())
          station=station->next;
      else
          station=station->previous;

      parking->removeVehicle();
    }

    }
    }

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
        OpenHash<int, clsVehicleTrip> trips= clsVehicleTrip::loadVehicleTrips();
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

        clsTransportLine* line;
        clsVehicle* vehicle;
        int idTransportLine=0;
        int numberOfStations = 0;
        TransportLineService::printAllTransportLines();
        while (true) {
            idTransportLine = Input::readInt("Invalid input. Please enter a number : ","Enter Transport Line ID (0 to cancel):");
            line = transportLines[idTransportLine];

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

            vehicle = vehicles[idVehicle];
            if (vehicle->getVehicleType() != line->getVehicleType()) {
                cout << "Error: Vehicle type doesn't match transport line type!\n";
                continue;
            }

            break;
        }


        clsVehicleTrip newTrip(numberOfStations, idVehicle, idTransportLine);

        recordingVehicleMovements(*vehicle,*line,newTrip);
        vehicle->addVehicleTrip(newTrip);
        trips.insert(newTrip.getId(),newTrip);

        cout << "\nVehicle Trip added successfully with ID: " << newTrip.getId() << "\n";

    }


/*
    void addNewVehicleTrip(DoubleNode<clsStation> *station,clsVehicleTrip &trip){


      destination=true;// Heading to the end of the line

      while(station!=nullptr||destination){

      clsParking *parking= station->item.getParking(line.getId());
      Stack<clsPassengerTrip> s;
      parking->addVehicle(*this);

      if(parking->getnumberOfAllVehicle()==1){

      while(hasCapacity()&&parking->hasPassengers()){
      clsPassengerTrip *passenger= parking->getPassengerTrip();
      strVehicleMovements *movement=trip.insertVehicleMovements(passenger->getStartStation());

      if(passenger->getDestination()==destination&&(!passenger->getDisabilityStatus()||hasDisabilityAccess())&&(!passenger->getItemsStatus()||hasPackageSpace())){


      currSeats++;
      if(passenger->getDisabilityStatus())
      {
      movement->currDisabilitSeat++;
      currDisabilitySeats++;
      }
      if(passenger->getItemsStatus())
      {
      movement->currPackageSize++;
      currPackageSize++;
      }
      }
      else
          s.push(*passenger);
      }

      if(!s.isEmpty())
          s.toQueue(parking->GetAllParkings());

      strVehicleMovements *curr=trip.getVehicleMovements(station->item.getid());
      if(curr!=nullptr)
      {
      currSeats-=curr->passengers.size();
      currDisabilitySeats-=curr->CurrDisability;
      curr->currDisabilitSeat=0;
      currPackageSize-=curr->CurrPackageSize;
      curr->currPackageSize=0;
      }
      if(station->next==nullptr)
          destination=false;
      if(destination)
          station=station->next;
      else
          station=station->previous;

      parking->vehicle.dequeue();
      }
    }

    vehicleTrips.addFirst(trip);
    }

*/




};
