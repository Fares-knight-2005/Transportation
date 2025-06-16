
#include <iostream>
#include "clsLogin.h"
#include "clsPassenger.h"
#include "clsCard.h"
#include "clsVehicleTrip.h"

using namespace std;



int main()
{
  //  clsLogin::Login();

	clsVehicleTrip v(3);



	cout << v.getNumberOfAllVehicleTrip();

}

