#pragma once

#include <iostream>
#include "clsPerson.h"
#include "DataStructures.h"
#include "clsCard.h"
#include <sstream>

using namespace std;

class clsPassenger : public clsPerson {
protected:
    clsCard Card;
    string Password;
    bool isDisabled;
    static int numberOfAllPassenger;
    
public:
    clsPassenger(short Age, string FirstName, string LastName, string PhoneNumber, string Email,
                 int id, clsCard card, string password ,bool isDisabled)
        : clsPerson(id, Age, FirstName, LastName, PhoneNumber, Email), 
          Card(card), Password(password),isDisabled(isDisabled) {}

    clsPassenger(short Age, string FirstName, string LastName, string PhoneNumber, string Email,
                 clsCard card, string password , bool isDisabled)
        : clsPerson(Age, FirstName, LastName, PhoneNumber, Email), 
          Card(card), Password(password),isDisabled(isDisabled) {
            this->Id=++numberOfAllPassenger;
          }

    string getPassword() {
        return Password;
    }

    void setPassword(string& newPassword) {
        Password = newPassword;
    }

    bool getDisabled(){
        return isDisabled;
    }

    static int getNumberOfAllPassenger(){
          return numberOfAllPassenger;     
    }

    static void setNumberOfAllPassenger(int n){
          numberOfAllPassenger=n;
    }

    void printPassengerInfo() {
        cout << "\nID: " << getId();
        cout << "\nName: " << GetFullName();
        cout << "\nAge: " << GetAge();
        cout << "\nPhone: " << GetPhoneNumber();
        cout << "\nEmail: " << GetEmail();
        cout << "\nCard Type: " << (Card.isPremium() ? "Premium" : "Regular");
        cout << "\nCard Balance: " << Card.getBalance();
        if (Card.isPremium()) {
            cout << "\nFree Trips: " << Card.getFreeTrips();
        }
        cout << "\nDisabled: " << (isDisabled ? "Yes" : "No");
        cout << "\n-------------------------------------------\n";
    }

    string toString() {
        ostringstream oss;
        oss << personToString() << ",,," << Card.toString() << ",,," << Password<< ",,," <<isDisabled;
        return oss.str();
    }

    static clsPassenger parse(string line) {
        DoubleLinkedList<string> tokens = Database::Split(line, ",,,");
        if (tokens.size() < 10) {
            throw invalid_argument("Not enough tokens in line");
        }

        int id = stoi(*tokens[0]);
        short age = stoi(*tokens[1]);
        string firstName = *tokens[2];
        string lastName = *tokens[3];
        string phoneNumber = *tokens[4];
        string email = *tokens[5];
        
        bool cardType = (*tokens[6] == "Premium");
        double cardBalance = stod(*tokens[7]);
        int freeTrips= stod(*tokens[8]);
        string password = *tokens[9];
        bool isDisabled= (stoi(*tokens[10])==1);
        
        clsCard card(cardType, cardBalance,freeTrips);
        
        return clsPassenger(age, firstName, lastName, phoneNumber, email, id, card, password, isDisabled);
    }
};

int clsPassenger::numberOfAllPassenger = 0;
