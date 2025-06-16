
#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <cctype>

using namespace std;

class Input {

    static string toLowerString(string str) {
    string lowerStr;
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
    }

    static void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

public:

    static void pressAnyKeyToContinue() {
        system("pause");
        system("cls");
    }

   static int readInt(string ErrorMessage = "Invalid input. Please enter a number : " ,string message="Please enter a number : ") {
      int input;
      cout << message;
      while (!(cin>>input)) {
          system("color");
          cout<<"\033[1;31m" + ErrorMessage +" \033[0m";
          clearInput();
      }

      return input;
  }

    static float readFloat(string message="Please enter a number: ") {
        float input;
        cout << message;
        while (!(cin>>input)) {
            system("color");
            cout<<"\033[1;31mInvalid input. Please enter a number: \033[0m";
            clearInput();
        }

        return input;
    }

    static double readDouble(string message="Please enter a number: ") {
        double input;
        cout << message;
        while (!(cin>>input)) {
            system("color");
            cout<<"\033[1;31mInvalid input. Please enter a number: \033[0m";
            clearInput();
        }

        return input;
    }

    static string readString(string message="Please enter text: ") {
       string input;
       cout << message;
       if(cin.peek()=='\n')
           cin.ignore();
       getline(cin, input);
       return input;
    }

    static string readString(int maxLength,int minLength=1,string message="Please enter text: ") {
        string input;
        while(true){
            input=readString(message);
            if(input.length()<=maxLength&&input.length()>= minLength) {
                return input;
            }
            else {
                system("color");
                cout << "\033[1;31mPlease try again. You have entered " << input.length()
                     << " characters.\033[0m" << endl;
                cout << "\033[1;31mThe allowed number of characters is between " << minLength
                     << " and " << maxLength << ".\033[0m" << endl;
            }
        }
    }

    static string readPassword(string message="Please enter password: ",int maxLength=50,int minLength=8){
        string password;
        bool hasUpper,hasDigit;
        while(true){
           password=readString(maxLength,minLength,message);
           hasUpper=hasDigit=false;
           for (char c : password) {
                if (isupper(c))
                    hasUpper = true;
                if (isdigit(c))
                    hasDigit = true;
           }
           if(hasUpper&&hasDigit)
               return password;
           else if(!hasUpper){
               system("color");
               cout<<"\033[1;31mPassword must contain at least one uppercase letter.\033[0m\n";
           }
           else{
               system("color");
               cout<<"\033[1;31mPassword must contain at least one number.\033[0m\n";
           }

        }
    }

    static bool readBool(string message="Please enter yes or no: ",string trueInput="yes",string falseInput="no") {
        string input;
        while (true) {
            input = readString(message);
            string inputLower = toLowerString(input);
            string trueLower = toLowerString(trueInput);
            string falseLower = toLowerString(falseInput);
            if (inputLower == trueLower)
                return true;
            if (inputLower == falseLower)
                return false;
            system("color");
            cout << "\033[1;31mInvalid input. Please enter either " << trueInput << " or " << falseInput << "\033[0m\n";
        }
    
    }



    static void Clear()
    {
        system("cls");
    }


    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n", string ErrorMessageLetters = "You Can't Enter Text Enter Number : ")
    {
        int Number = readInt(ErrorMessageLetters);

        while (!(Number >= From && Number <= To))
        {
            cout << ErrorMessage;
            Number = readInt(ErrorMessageLetters);
        }
        return Number;
    }

};

