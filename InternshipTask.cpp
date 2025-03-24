#include <iostream>
#include <vector>

#include "Headers/json.hpp"
#include "Headers/httplib.h"
#include "Headers/Flight.h"
#include "Headers/Route.h"

using namespace httplib;

using json = nlohmann::json;

int main()
{
	/*vector<Flight> flights;

	flights.push_back(Flight("SOF", "LON", 20));
	flights.push_back(Flight("FRA", "LON", 30));
	flights.push_back(Flight("SOF", "FRA", 10));
	flights.push_back(Flight("LON", "FRA", 50));


	vector<Route> routeList = Route::PossibleRoutes(flights, "SOF", "FRA", 2);

	if (routeList.empty()) std::cout << "No available routes.";
	else
	{
		for (Route rt : routeList)
		{
			for (string str : rt.GetRouteStops())
			{
				std::cout << str << " , ";
			}
			std::cout << rt.GetRoutePrice() << endl;
		}
	}*/



	Server svr;

	svr.Post("/routes", [](const Request& req, Response& res)
		{
			vector<Flight> flights;

			flights.push_back(Flight("SOF", "LON", 20));
			flights.push_back(Flight("FRA", "LON", 30));
			flights.push_back(Flight("SOF", "FRA", 10));
			flights.push_back(Flight("LON", "FRA", 50));

			json requestBody;
			
			try
			{
				requestBody = json::parse(req.body);
			}
			catch (exception){
				res.set_content("{\"message\" : \"Unable to parse request body!\"}", "application/json");
				res.status = 400;
				return;
			}
			vector<Route> routeList;
			unsigned int maxFlights = UINT_MAX - 1;
			string origin, destination;


			//Checks
			{
				//Origin
				if (!requestBody.contains("origin"))
				{
					res.set_content("{\"message\" : \"Missing origin input!\"}", "application/json");
					res.status = 400;
					return;
				}
				if (requestBody["origin"].type() != json::value_t::string)
				{
					res.set_content("{\"message\" : \"The input for origin is not in the correct format!\"}", "application/json");
					res.status = 400;
					return;
				}
				origin = requestBody["origin"];

				//Destination
				if (!requestBody.contains("destination"))
				{
					res.set_content("{\"message\" : \"Missing destination input!\"}", "application/json");
					res.status = 400;
					return;
				}
				if (requestBody["destination"].type() != json::value_t::string)
				{
					res.set_content("{\"message\" : \"The input for destination is not in the correct format!\"}", "application/json");
					res.status = 400;
					return;
				}
				destination = requestBody["destination"];

				//maxFlights
				if (requestBody.contains("maxFlights"))
				{

					if (requestBody["maxFlights"].type() != json::value_t::number_unsigned)
					{
						res.set_content("{\"message\" : \"The input for maxFlights is not in the correct format!\"}", "application/json");
						res.status = 400;
						return;
					}
					if ((unsigned long long)requestBody["maxFlights"] != (unsigned int)requestBody["maxFlights"])
					{
						res.set_content("{\"message\" : \"You have gone over the maximum amount for the maxFlight filter!\"}", "application/json");
						res.status = 400;
						return;
					}
					maxFlights = requestBody["maxFlights"];
				}

				//Correct filters -> create route list
				routeList = Route::PossibleRoutes(flights, origin, destination, maxFlights);

				//Check if route list is empty
				if (routeList.empty())
				{
					res.set_content("[]", "application/json");
					return;
				}
			}
			

			json response;
			for (Route route : routeList)
			{
				response.push_back({
					{"route", route.GetRouteStops()},
					{"price", route.GetRoutePrice()}
					});
			}

			res.set_content(response.dump(), "application/json");
		});


	svr.listen("localhost", 5000);


}