#pragma once
#include <string>

using namespace std;

struct Flight
{
	string flightOrigin = "";
	string flightDestination = "";
	unsigned int flightPrice = 0;

	Flight() {}

	Flight(string origin, string destination, unsigned int price) : flightOrigin(origin), flightDestination(destination), flightPrice(price)
	{

	}
};