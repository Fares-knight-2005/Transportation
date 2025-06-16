
#include <iostream>
#include "clsLogin.h"
#include "clsPassenger.h"
#include "clsCard.h"
#include "clsVehicleTrip.h"

using namespace std;



int main()
{
  //  clsLogin::Login();

	clsCard C(1, 200, 3);

	clsPassenger Pa(18 , "Fares" , "Oyion" , "0981883592" , "Fares@gmail.com" , 1 , C , "1234" , 0);

	cout << Pa.toString();

}

