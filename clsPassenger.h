#pragma once

#include <iostream>
#include "clsPerson.h"
#include "DataStructures.h"
#include "clsCard.h"
#include <sstream>
#include <string>
#include <fstream>
#include "Input.h"

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


    template <typename Key>
    static void savePassengersFromOpenHash(OpenHash <Key ,clsPassenger> Passengers)
    {
        fstream PassengerFile;

        PassengerFile.open(clsPassengerFileName, ios::out);

        if (PassengerFile.is_open())
        {
            for (int i = 0; i < Passengers.getCapicty(); i++) {
                Node <HashNode<Key, clsPassenger>>* d = Passengers.getHead(i);
                while (d != nullptr) {
                    PassengerFile << d->item.item.toString() << endl;
                    d = d->next;
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

  static OpenHash<int, clsPassenger> loadPassengers() {
        OpenHash<int, clsPassenger> passengers;
        ifstream file(clsPassengerFileName);
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


  void Add()
  {
      fstream MyFile;
      MyFile.open(clsPassengerFileName, ios::out | ios::app);

      if (MyFile.is_open())
      {
          MyFile << this->toString() << endl;
          MyFile.close();
      }
  }

  void updateCardInfo() {
      cout << "\nCurrent Card Information:";
      cout << "\nType: " << (Card.isPremium() ? "Premium" : "Regular");
      cout << "\nBalance: " << Card.getBalance();
      if (Card.isPremium()) {
          cout << "\nFree Trips: " << Card.getFreeTrips();
      }

      cout << "\n\nWhat would you like to update?\n";
      cout << "1. Card Type\n";
      cout << "2. Recharge\n";
      cout << "0. Cancel\n";

      int choice = Input::ReadIntNumberBetween(0, 2, "Invalid choice. Enter 0-2: ");
      if (choice == 0)
          return;

      switch (choice) {
      case 1: {
          cout << "\nCard Types:\n";
          cout << "1. Regular\n";
          cout << "2. Premium\n";
          cout << "Converting the card to Premium requires $500.\n";
          int cardChoice = Input::ReadIntNumberBetween(1, 2, "Invalid choice. Enter 1-2: ");
          Card.setType(cardChoice == 2);
          break;
      }
      case 2: {
        //  if (Card.isPremium())
        //      cout << "You can get a free trips if you add an amount $" + clsCard::getAmountForFreeTrip();
          double amount = Input::readDouble("Enter amount: ");
          Card.recharge(amount);
          break;
      }
      }
  }

  clsCard *getCard() {
      return &Card;
  }

  void setDisabled(bool d) {
      isDisabled = d;
  }
  
  

  static OpenHash<string, clsPassenger> loadPassengersByName() {
      OpenHash<string, clsPassenger> passengers;
      ifstream file(clsPassengerFileName);
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
  }



  static OpenHash<string, clsPassenger> loadPassengersByPassword() {
      OpenHash<string, clsPassenger> passengers;
      ifstream file(clsPassengerFileName);
      string line;

      while (getline(file, line)) {
          try {
              clsPassenger passenger = clsPassenger::parse(line);
              string fullNameKey = passenger.getPassword();
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
  }


};

int clsPassenger::numberOfAllPassenger = 0;

