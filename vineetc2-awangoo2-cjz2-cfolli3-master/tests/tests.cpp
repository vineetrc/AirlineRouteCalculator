#include "../cs225/catch/catch.hpp"

#include "../airports.h"
#include "../routes.h"
#include "../graph.h"

TEST_CASE("testReadAirportsLength", "[weight=1]") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  REQUIRE( my_airports.getNumAirports() == 10 );
}

TEST_CASE("testReadRoutesLength", "[weight=1]"){
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");
  REQUIRE( my_routes.getNumRoutes() == 14);
  REQUIRE( 1 == 1);
}

// BFS Iterator test
TEST_CASE("Basic BFS from connected point", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_7node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_7node.dat");

  Graph graph(my_airports, my_routes, 0);
  auto it = graph.begin();

  REQUIRE( (*it).getID() == 1);
  ++it;
  REQUIRE( (*it).getID() == 10);
  ++it;
  REQUIRE( (*it).getID() == 6);
  ++it;
  REQUIRE( (*it).getID() == 2);
  ++it;
  REQUIRE( (*it).getID() == 5);
  ++it;
  REQUIRE( (*it).getID() == 7);
  ++it;
  REQUIRE( (*it).getID() == -1);
}

TEST_CASE("BFS iteration from 0 external routes node", "weight=1") { 
  airports my_airports;
  my_airports.readData("tests/airports_7node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_7node.dat");

  Graph graph(my_airports, my_routes, 7);
  auto it = graph.begin();

  ++it;
  REQUIRE( (*it).getID() == -1 );
}

TEST_CASE("BFS iteration on non-connected node doesn't go to main code", "weight=1") { 
airports my_airports;
  my_airports.readData("tests/airports_7node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_7node.dat");

  Graph graph(my_airports, my_routes, 11);
  auto it = graph.begin();

  ++it;
  REQUIRE( (*it).getID() == -1 );
}

TEST_CASE("Proper BFS iteration from most central point", "weight=1") { 
  airports my_airports;
  my_airports.readData("tests/airports_7node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_7node.dat");

  Graph graph(my_airports, my_routes, 6);
  auto it = graph.begin();
  
  ++it;
  REQUIRE( (*it).getID() == 2 );
  ++it;
  REQUIRE( (*it).getID() == 5 );
  ++it;
  REQUIRE( (*it).getID() == 7 );
  ++it;
  REQUIRE( (*it).getID() == 10 );
  ++it;
  REQUIRE( (*it).getID() == 1 );
  ++it;
  REQUIRE( (*it).getID() == -1 );
}

TEST_CASE("Start node does not exist", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_7node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_7node.dat");

  Graph graph(my_airports, my_routes, 1000);
  
  REQUIRE(!my_airports.checkValidID(1000));
}

// Dijkstra's Algorithm tests
TEST_CASE("Dijkstra's from point with path", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 2);
  
  vector<Airport> real = graph.NearestPath(2, 8);

  REQUIRE( real[0].getID() == 2 );
  REQUIRE( real[1].getID() == 4 );
  REQUIRE( real[2].getID() == 1 );
  REQUIRE( real[3].getID() == 8 );
}

TEST_CASE("Dijkstra's to point not connected to graph", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 2);
  
  vector<Airport> real = graph.NearestPath(2, 7);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("Dijkstra's from point not connected to graph", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 7);
  
  vector<Airport> real = graph.NearestPath(7, 4);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("Dijkstra's from point with no outgoing edges", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath(9, 4);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("Dijkstra's to itself", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath(9, 9);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("Dijkstra's with no existing startpoint", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath(90000, 3);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("Dijkstra's to no existing endpoint", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath(1, 9000);

  REQUIRE( real == vector<Airport>() );
}

// // A* Algorithm tests
TEST_CASE("A* from point with path", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 2);
  
  vector<Airport> real = graph.NearestPath_A_Star(2, 8);

  REQUIRE( real[0].getID() == 2 );
  REQUIRE( real[1].getID() == 4 );
  REQUIRE( real[2].getID() == 6 );
  REQUIRE( real[3].getID() == 8 );
}

TEST_CASE("A* to point not connected to graph", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 2);
  
  vector<Airport> real = graph.NearestPath_A_Star(2, 7);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("A* from point not connected to graph", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 7);
  
  vector<Airport> real = graph.NearestPath_A_Star(7, 4);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("A* from point with no outgoing edges", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath_A_Star(9, 4);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("A* to itself", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath_A_Star(9, 9);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("A* with no existing startpoint", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath_A_Star(90000, 3);

  REQUIRE( real == vector<Airport>() );
}

TEST_CASE("A* to no existing endpoint", "weight=1") {
  airports my_airports;
  my_airports.readData("tests/airports_10node.dat");
  routes my_routes;
  my_routes.readData("tests/routes_10node.dat");

  Graph graph(my_airports, my_routes, 9);
  
  vector<Airport> real = graph.NearestPath_A_Star(1, 9000);

  REQUIRE( real == vector<Airport>() );
}