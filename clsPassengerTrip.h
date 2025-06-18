
#pragma once


#include <iostream>
#include <string>
#include <sstream>
#include "Input.h"
#include "clsCard.h"

using namespace std;

class clsPassengerTrip {
private:

    int idStarStation,idEndStation,idPassenger;
    float price;
    bool isDisabled,hasItems,destination;

public:
    clsPassengerTrip(int start, int end, int id, bool disabled, bool items,bool destination,float price) {
        idStarStation = start;
        idEndStation = end;
        idPassenger = id;
        isDisabled = disabled;
        hasItems = items;
        this->price=price;
    }

    clsPassengerTrip(){}

    int getStartStation() { return idStarStation; }
    int getEndStation() { return idEndStation; }
    int getPassengerId() { return idPassenger; }
    bool getDisabilityStatus() { return isDisabled; }
    bool getItemsStatus() { return hasItems; }
    bool getDestination() {return destination;}

    void setStartStation(int start) { idStarStation = start; }
    void setEndStation(int end) { idEndStation = end; }
    void setPassengerId(int id) { idPassenger = id; }
    void setDisabilityStatus(bool disabled) { isDisabled = disabled; }
    void setItemsStatus(bool items) { hasItems = items; }


    void displayInfo() {
        cout << "Passenger ID: " << idPassenger << endl;
        cout << "Start Station: " << idStarStation << endl;
        cout << "End Station: " << idEndStation << endl;
        cout << "Price: "<< price << endl;
        cout << "Heading to end: " << (destination ? "Yes" : "No") << endl;
        cout << "Disabled: " << (isDisabled ? "Yes" : "No") << endl;
        cout << "Has items: " << (hasItems ? "Yes" : "No") << endl;
    }

    bool setPrice(int amount,clsCard *card,bool transportingItems){

    if(hasItems)
        price+=20;

    if(transportingItems)
        price+=5;

    if(card->getFreeTrips()>0){
    bool r=Input::readBool("You have free trips. Do you want to use them? ");
    if(r)
    {
    card->setFreeTrips(card->getFreeTrips() - 1);
    return card->payment(price);
    }
    }

    price+=amount;

    if(card->isPremium())
        price*=0.7;// خصم

    return card->payment(price);

    }

    string toString() {
        ostringstream oss;
        oss << idStarStation << ",,," << idEndStation << ",,,"
            << idPassenger << ",,,"  << ",,,"
            << (isDisabled ? "1" : "0") << ",,," << (hasItems ? "1" : "0")<< ",,," <<(destination ? "1" : "0") << ",,," << price;

        return oss.str();
    }


};
