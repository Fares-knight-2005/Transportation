#pragma once

#include <iostream>
#include "clsPerson.h"
#include "DataStructures.h"
#include "clsCard.h"
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

string clsPassengerFileName = "Passengers.txt";

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
        DoubleLinkedList<string> tokens = Split(line, ",,,");
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



    static DoubleLinkedList <string> Split(string s, string delim)
    {
        string Word = "";

        DoubleLinkedList <string> Words;

        short pos = s.find(delim);

        while (pos != string::npos)
        {
            Word = s.substr(0, pos);
            s.erase(0, pos + delim.length());

            if (Word != "")
                Words.addLast(Word);
            pos = s.find(delim);
        }

        if (s != "")
            Words.addLast(s);

        return Words;
    }

  
    static void savePassengers(DoubleLinkedList <clsPassenger> Passengers)
    {
        fstream PassengerFile;

        PassengerFile.open(clsPassengerFileName, ios::out);

        if (PassengerFile.is_open())
        {
            for (int i = 0; i < Passengers.size(); i++)
            {
                if(Passengers[i] != nullptr)
                {
                    clsPassenger p = *Passengers[i];
                    string Line = p.toString();
                    PassengerFile << Line << endl;
                }
            }

            PassengerFile.close();
        }
    }


    static DoubleLinkedList <clsPassenger> GetAllPassengers()
    {
        DoubleLinkedList <clsPassenger> AllPassengers;

        fstream MyFile;
        MyFile.open(clsPassengerFileName, ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsPassenger passenger = parse(Line);
                AllPassengers.addLast(passenger);
            }

            MyFile.close();

        }

        return AllPassengers;

    }


    //template<class Item>
    //static void savePassengers(string& filename, OpenHash<Item, clsPassenger>& passengers) {
    //    ofstream outFile(filename);

    //    for (int i = 0; i < passengers.capacity; i++) {
    //        Node<Item, clsPassenger>* current = passengers.getHead(i);
    //        while (current != nullptr) {
    //            outFile << current->item.toString() << endl;
    //            current = current->next;
    //        }
    //    }

    //    outFile.close();
    //}

   /* static OpenHash<int, clsPassenger> loadPassengers(string filename) {
        OpenHash<int, clsPassenger> passengers;
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            try {
                clsPassenger passenger = clsPassenger::parse(line);
                passengers.insert(passenger.getId(), passenger);

                if (clsPassenger::getNumberOfAllPassenger() < passenger.getId()) {
                    clsPassenger::setNumberOfAllPassenger(passenger.getId());
                }
            }
            catch (...) {
                continue;
            }
        }

        return passengers;
    }

    static OpenHash<string, clsPassenger> loadPassengersByName(string filename) {
        OpenHash<string, clsPassenger> passengers;
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            try {
                clsPassenger passenger = clsPassenger::parse(line);
                string fullNameKey = passenger.GetFullName();
                passengers.insert(fullNameKey, passenger);

                if (clsPassenger::getNumberOfAllPassenger() < passenger.getId()) {
                    clsPassenger::setNumberOfAllPassenger(passenger.getId());
                }
            }
            catch (...) {
                continue;
            }
        }

        return passengers;
    }*/

};

int clsPassenger::numberOfAllPassenger = 0;

