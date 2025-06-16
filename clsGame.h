#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class clsGame {
    int static ReadPoseteveNumber(string messege)
    {
        int num;

        do
        {
            cout << messege;
            cin >> num;

        } while (num <= 0 || num > 10);

        return num;

    }


    static int RandomNumber(int from, int to)
    {
        return rand() % (to - from + 1) + from;
    }

    static string whatIsTheChoice(int choice)
    {
        switch (choice)
        {
        case 1: return "stone";
        case 2: return "paper";
        case 3: return "scissors";


        }

    }

    static string prossingWiner(string player, string computer)
    {
        if (player == computer)
            return "NO winner";
        if (player == "stone" && computer == "paper" || player == "paper" && computer == "scissors" || player == "scissors" && computer == "stone")
            return "computer";
        return "player";

    }

    static void RoundxTop(int x)
    {
        cout << "\n\n_____________________________________________" << " Round [" << x << "] _____________________________________________\n";
    }

    static void Roundxdwon()
    {
        cout << "\n_____________________________________________________________________________________________________\n";
    }

    static void ChangeColor(string winner, int& playercounter, int& computercounter)
    {

        if (winner == "computer") { system("color 4F"); cout << "\a"; computercounter++; }

        else if (winner == "player") { system("color 2F"); playercounter++; }

        else system("color 6F");

    }


    static void Roundx(int X, int& playercounter, int& computercounter)
    {
        cout << endl << endl << "Round [" << X << "] begins :\n\n";
        int player;
        cout << "your choice : [1].stone , [2].paper , [3],scissors ? ";
        cin >> player;
        int computer = RandomNumber(1, 3);

        string playerChoice = whatIsTheChoice(player), computerChoice = whatIsTheChoice(computer);

        RoundxTop(X);

        ChangeColor(prossingWiner(playerChoice, computerChoice), playercounter, computercounter);
        cout << "player   choice: " << playerChoice << endl;
        cout << "computer choice: " << computerChoice << endl;
        cout << "Round winner   : " << "[" << prossingWiner(playerChoice, computerChoice) << "]";

        Roundxdwon();
    }

    static void endrounds()
    {
        system("color 3F");

        cout << "\n\n\n\n\n\t\t___________________________________________________________________________________________\n\n";
        cout << "\t\t\t\t\t\t    +++ Game Over +++\n";
        cout << "\t\t___________________________________________________________________________________________\n\n";
        cout << "\t\t____________________________________ [ Game Results ] _____________________________________\n\n";
    }

    static void printInformation(int GameRounds, int playerwon, int computerwon)
    {
        cout << "\t\tGame Rounds\t\t: " << GameRounds << endl;
        cout << "\t\tPlayer won times\t: " << playerwon << endl;
        cout << "\t\tcomputer won times\t: " << computerwon << endl;
        cout << "\t\tDraw times\t\t: " << GameRounds - playerwon - computerwon << endl;
        cout << "\t\tFinal winner\t\t: ";
        if (playerwon > computerwon)
            cout << "[ player ]";
        else if (playerwon < computerwon)
            cout << "[ computer ]";
        else cout << "[ No winner ]";

    }

    public:
   
        
     static void Game()
    {

        srand((unsigned)time(NULL));
        bool a;
        do {


            int timesToPlay;

            timesToPlay = ReadPoseteveNumber("How many rounds do you want to play (1 - 10) : ");

            int playercounter = 0, computercounter = 0;

            for (int i = 1; i <= timesToPlay; i++)
            {
                Roundx(i, playercounter, computercounter);
            }

            endrounds();

            printInformation(timesToPlay, playercounter, computercounter);

            cout << "\n\n\t\t___________________________________________________________________________________________\n\n";
            string b;
            cout << "Do you want to start a new game ? [y/N] : ";
            cin >> b;

            if (b == "y" || b == "Y" || b == "yes" || b == "Yes")
                a = 1;

            else a = 0;

        } while (a);

        system("color 0F");
           return;
        }
     };
