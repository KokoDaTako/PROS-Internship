#include "../Headers/Route.h"
#include <iostream>

vector<string> Route::GetRouteStops()
{
    return routeStops;
}

unsigned int Route::GetRoutePrice()
{
	return routePrice;
}

bool Route::PriceCompare(Route first, Route second)
{
	return (first.routePrice < second.routePrice);
}

void Route::SortRoutes(vector<Route>& routes)
{
	sort(routes.begin(), routes.end(), PriceCompare);
}

void Route::AddFlight(Flight flight)
{
	if (routeStops.empty())
	{
		routeStops.push_back(flight.flightOrigin);
		routeStops.push_back(flight.flightDestination);
		routePrice += flight.flightPrice;
	}
	else if (flight.flightOrigin == routeStops.back())
	{
		routePrice += flight.flightPrice;
		routeStops.push_back(flight.flightDestination);
	}
	else cout << "Flight destination does not match last stop. Flight can not be added to this route";
}

Route Route::LoopThrough(vector<Flight> flights, Route& route, string destination)
{
	if (route.routeStops.back() == destination) return route;

	for (Flight fl : flights)
	{
		if (fl.flightOrigin == route.routeStops.back() && find(route.routeStops.begin(), route.routeStops.end(), fl.flightDestination) == route.routeStops.end())
		{
			route.AddFlight(fl);
			LoopThrough(flights, route, destination);
		}
	}

	return route;
}

vector<Route> Route::PossibleRoutes(vector<Flight> flights, string origin, string destination, unsigned int maxFlights)
{
	vector<Route> result;
	Route route = Route();


	for (int i = 0; i < flights.size(); i++)
	{
		route.routeStops.clear();
		route.routePrice = 0;
		if (flights[i].flightOrigin == origin)
		{
			route.AddFlight(flights[i]);
			Route current = LoopThrough(flights, route, destination);
			if (!current.routeStops.empty() && current.GetRouteStops().size() <= maxFlights + 1)
			{
				if (current.routeStops.back() == destination)
					result.push_back(current);
			}
		}
	}

	Route::SortRoutes(result);
	return result;
}
