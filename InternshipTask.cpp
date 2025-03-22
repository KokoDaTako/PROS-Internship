#include <iostream>
#include <vector>


#include "Headers/Flight.h"
#include "Headers/Route.h"

using namespace std;





int main()
{
	vector<Flight> flights;

	flights.push_back(Flight("SOF", "LON", 20));
	flights.push_back(Flight("FRA", "LON", 30));
	flights.push_back(Flight("SOF", "FRA", 10));
	flights.push_back(Flight("LON", "FRA", 50));
	

	vector<Route> routeList = Route::PossibleRoutes(flights, "SOF", "LON");

	if (routeList.empty()) cout << "No available routes.";
	else
	{
		for (Route rt : routeList)
		{
			for (string str : rt.GetRouteStops())
			{
				cout << str << " , ";
			}
			cout << rt.GetRoutePrice() << endl;
		}
	}
}