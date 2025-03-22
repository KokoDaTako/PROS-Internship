#pragma once
#include <vector>
#include <algorithm>

#include "Flight.h"

class Route
{
	vector<string> routeStops;
	unsigned int routePrice = 0;

	Route(){}

	Route(vector<string> stops, unsigned int price) : routeStops(stops), routePrice(price) {}

	//compare function for the sorting method
	static bool PriceCompare(Route first, Route second);

	void AddFlight(Flight flight);
	static Route LoopThrough(vector<Flight> flights, Route& route, string destination);


public:
	static vector<Route> PossibleRoutes(vector<Flight> flights, string origin, string destination);
	static void SortRoutes(vector<Route>& routes);

	//Getters
	vector<string> GetRouteStops();
	unsigned int GetRoutePrice();
};
