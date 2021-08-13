#pragma once

#include "airport.h"
#include "airports.h"
#include "routes.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <stack>
#include <queue>

class Graph {
public:
	class Iterator: std::iterator<std::forward_iterator_tag, Airport> {
	public:
		Iterator(Airport& start, Graph* parent);

		Iterator();
  	  	Iterator & operator++();
    	Airport operator*();
    	bool operator!=(const Iterator &other);
	private:
		int current;
		int start;
		
		std::vector<bool> visited_nodes;
		std::queue<int> queue;

		Graph* parent;
	};
	
	Graph(airports& air_list, routes& route_list, int start_id_);

	std::vector<Airport> NearestPath(int orgID, int destID);

	void print_Dijkstra(std::vector<Airport> path);

	double getHeuristic(Airport& a1, Airport& a2);

	std::vector<Airport> NearestPath_A_Star(int orgID, int destID);

	void print_A_Star(std::vector<Airport> path_a_star);

	std::vector<std::vector<double>> getMatrix();

	int getAirDictID(int index);

	int getIndex(int airID);

	Airport getAirportFromID(int airID);

	Graph::Iterator begin();
  	
	Graph::Iterator end();

private:
	std::vector<Airport> airdata;
	std::vector<std::vector<double> > adj_mat; // rows/columns correspond to indexes in airdata
	std::map<int, int> id_dict; // dictionary mapping airport ID to their index in the vector of airports. ID -> Index
	int start_id;
	int num_routes;
	int num_airports;
	double avg_distance;
};
