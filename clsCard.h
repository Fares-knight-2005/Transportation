
#pragma once


#include <iostream>
#include "clsPerson.h"
#include "DataStructures.h"
#include <sstream>

using namespace std;

class clsCard {

protected:
	bool type;
	double balance;
        int freeTrips;
        static double amountForFreeTrip;


public:
	clsCard(bool type = false, int balance = 0,int freeTrips=0) {
		this->type = type;
		this->balance = balance;
		this->freeTrips = freeTrips;
	}

    
	bool payment(double amount) {
		if (balance >= amount) {
			balance -= amount;
			return true;
		}
		else
			return false;
	}

	void recharge(double amount) {
		balance += amount;
		if(amount==amountForFreeTrip)
			freeTrips++;
	}

	double getBalance()  {
	return balance;
	}

        int getFreeTrips(){
	return freeTrips;
	}

        void setFreeTrips(int freeTrips){
	this->freeTrips=freeTrips;
	}

        bool isPremium(){
	return type;
	}

        void setType(bool newType){
		
        if(newType){
	   if(payment(500)){
	      cout<<"Your type has been successfully modified and you have received three free trips.\n";
	      freeTrips+=3;
	      type=newType;
	   }
	   else
	       cout<< "The transfer was not completed because you do not have enough money. \n";	
	}
	else{
	      cout<<"Your type has been successfully modified.\n";
	      type=newType;	
	}
		
	}


        string getType(){
        return type ? "Premium" : "Regular";
        }

       string toString(){
        ostringstream oss;
        oss << (type ? "Premium" : "Regular") << ",,," << balance<< ",,," <<freeTrips;
        return oss.str();
       }


       static void setAmountForFreeTrip(double amount){
		   clsCard::amountForFreeTrip = amount;
       }

       static double getAmountForFreeTrip(){
        return clsCard::amountForFreeTrip;
       }


};
double clsCard::amountForFreeTrip=500;
