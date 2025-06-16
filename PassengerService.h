
#pragma once

#include "clsPassenger.h"
#include "Database.h"
#include "Input.h"

using namespace std;

class PassengerService {
public:
    static void printAllPassengers() {
        OpenHash<int , clsPassenger> passengers = Database::loadPassengersByName(Database::clsPassengerFileName);

        if (passengers.isEmpty()) {
            cout << "\nNo Passengers Found!\n";
            return;
        }
      
        cout << "\n===========================================\n";
        cout << "        All Passengers (" << passengers.size() << ")";
        cout << "\n===========================================\n"; 

        for (int i = 0; i < passengers.capacity; i++) {
            HashNode<int, clsPassenger>* current = passengers.getHead(i);
            while (current != nullptr) {
                current->data.item.printPassengerInfo();
                current = current->next;
            }
        }
    }

    static void addNewPassenger() {
        OpenHash<string, clsPassenger> passengers = Database::loadPassengersByName(Database::clsPassengerFileName);
      
        cout << "\n===========================================\n";
        cout << "        Add New Passenger";
        cout << "\n===========================================\n";
        while(true){
        string firstName = Input::readString("Enter First Name: ");
        string lastName = Input::readString("Enter Last Name: ");
        string fullName=firstName +" "+lastName;
        if(passengers[fullName]!=nullptr)
             cout<<" This name is already in use. You must use a unique name. \n";
        else
            break;
        }
        short age = Input::readInt("Enter Age: ");
        string phone = Input::readString("Enter Phone Number: ");
        string email = Input::readString("Enter Email: ");
        string password = Input::readPassword("Enter Password: ");

        cout << "\nCard Types:\n";
        cout << "1. Regular\n";
        cout << "2. Premium\n";
        int cardChoice = Input::ReadIntNumberBetween(1, 2, "Invalid choice. Enter 1-2: ");
        bool isPremium = (cardChoice == 2);
        double balance = Input::readDouble("Enter Initial Balance: ");
        bool isDisabled = Input::readBool("Is Disabled? (yes/no): ");

        clsCard card(isPremium, balance );
        clsPassenger newPassenger(age, firstName, lastName, phone, email, card, password, isDisabled);
        passengers.insert(newPassenger.GetFullName(), newPassenger);

        cout << "\nPassenger added successfully with ID: " << newPassenger.getId() << "\n";
        Database::savePassengers(Database::clsPassengerFileName, passengers);
    }

    static void deletePassenger() {
        cout << "\n===========================================\n";
        cout << "        Delete Passenger";
        cout << "\n===========================================\n";

        cout << "\nSearch by:\n";
        cout << "1. ID\n";
        cout << "2. Name\n";
        cout << "3. Exit\n";
        
        int choice = Input::ReadIntNumberBetween(1, 3, "Invalid choice. Enter 1-3: ");
        if (choice == 3) 
          return;

        bool success = false;
        if (choice == 1) {
            OpenHash<int, clsPassenger> passengers = Database::loadPassengers(Database::clsPassengerFileName);
            int id = Input::readInt("Enter Passenger ID to delete: ");
            success = passengers.remove(id);
            if (success) {
                cout<< "The deletion process was completed successfully." <<endl;
                Database::savePassengers(Database::clsPassengerFileName, passengers);
            }
        }
        else {
            OpenHash<string, clsPassenger> passengers = Database::loadPassengersByName(Database::clsPassengerFileName);
            string name = Input::readString("Enter Passenger Full Name to delete: ");
            success = passengers.remove(name);
            if (success) {
                cout<< "The deletion process was completed successfully." <<endl;
                Database::savePassengers(Database::clsPassengerFileName, tempHash);
                }  
            }   
    }

    static void updatePassenger() {
        cout << "\n===========================================\n";
        cout << "        Update Passenger";
        cout << "\n===========================================\n";

        cout << "\nSearch by:\n";
        cout << "1. ID\n";
        cout << "2. Name\n";
        cout << "3. Exit\n";
        
        int choice = Input::ReadIntNumberBetween(1, 3, "Invalid choice. Enter 1-3: ");
        if (choice == 3) 
              return;

        clsPassenger* passengerToUpdate = nullptr;
        OpenHash<int, clsPassenger> passengersById;
        OpenHash<string, clsPassenger> passengersByName;

        if (choice == 1) {
            passengersById = Database::loadPassengers(Database::clsPassengerFileName);
            int id = Input::readInt("Enter Passenger ID to update: ");
            passengerToUpdate = passengersById[id];
        }
        else {
            passengersByName = Database::loadPassengersByName(Database::clsPassengerFileName);
            string name = Input::readString("Enter Passenger Full Name to update: ");
            passengerToUpdate = passengersByName[name];
        }

        if (passengerToUpdate == nullptr) {
            cout << "\nPassenger not found!\n";
            return;
        }

        printPassengerInfo(*passengerToUpdate);
        cout << "\nWhat would you like to update?\n";
        cout << "1. First Name\n";
        cout << "2. Last Name\n";
        cout << "3. Age\n";
        cout << "4. Phone Number\n";
        cout << "5. Email\n";
        cout << "6. Password\n";
        cout << "7. Card Information\n";
        cout << "8. Disabled Status\n";
        cout << "0. Cancel\n";

        int updateChoice = Input::ReadIntNumberBetween(0, 8, "Invalid choice. Enter 0-8: ");
        if (updateChoice == 0) return;

        switch (updateChoice) {
            case 1: {
                string newName = Input::readString("Enter new First Name: ");
                passengerToUpdate->SetFirstName(newName);
                break;
            }
            case 2: {
                string newName = Input::readString("Enter new Last Name: ");
                passengerToUpdate->SetLastName(newName);
                break;
            }
            case 3: {
                short newAge = Input::readInt("Enter new Age: ");
                passengerToUpdate->SetAge(newAge);
                break;
            }
            case 4: {
                string newPhone = Input::readString("Enter new Phone Number: ");
                passengerToUpdate->SetPhoneNumber(newPhone);
                break;
            }
            case 5: {
                string newEmail = Input::readString("Enter new Email: ");
                passengerToUpdate->SetEmail(newEmail);
                break;
            }
            case 6: {
                string newPassword = Input::readPassword("Enter new Password: ");
                passengerToUpdate->setPassword(newPassword);
                break;
            }
            case 7: {
                PassengerService::updateCardInfo(passengerToUpdate->Card);
                break;
            }
            case 8: {
                bool isDisabled = Input::readBool("Is Disabled? (yes/no): ");
                passengerToUpdate->setDisabled(isDisabled);
                break;
            }
        }

        if (choice == 1) 
            Database::savePassengers(Database::clsPassengerFileName, passengersById);
        else 
            Database::savePassengers(Database::clsPassengerFileName, passengersByName);
           
        }

        cout << "\nPassenger updated successfully.\n";
    }

private:

    static void updateCardInfo(clsCard& card) {
        cout << "\nCurrent Card Information:";
        cout << "\nType: " << (card.isPremium() ? "Premium" : "Regular");
        cout << "\nBalance: " << card.getBalance();
        if (card.isPremium()) {
            cout << "\nFree Trips: " << card.getFreeTrips();
        }

        cout << "\n\nWhat would you like to update?\n";
        cout << "1. Card Type\n";
        cout << "2. Recharge\n";
        cout << "0. Cancel\n";

        int choice = Input::ReadIntNumberBetween(0, 2, "Invalid choice. Enter 0-" + to_string(maxChoice) + ": ");
        if (choice == 0) 
          return;

        switch (choice) {
            case 1: {
                cout << "\nCard Types:\n";
                cout << "1. Regular\n";
                cout << "2. Premium\n";
                cout << "Converting the card to Premium requires $500.\n";
                int cardChoice = Input::ReadIntNumberBetween(1, 2, "Invalid choice. Enter 1-2: ");
                card.setType(cardChoice == 2);
                break;
            }
            case 2: {
                if(card.isPremium())
                    cout << "You can get a free trips if you add an amount $"+clsCard::getAmountForFreeTrip();
                double amount = Input::readDouble("Enter amount: ");
                card.Recharge(amount);
                break;
            }
        }
    }
};
