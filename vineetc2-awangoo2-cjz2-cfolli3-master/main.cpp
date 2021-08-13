#include "airports.h"
#include "routes.h"
#include "graph.h"
#include <iostream>

int main(int argc, char *argv[]){
    (void)argc;
    std::string airports_file = argv[1];
    std::string routes_file = argv[2];

    airports my_airports;
    my_airports.readData(airports_file);
    
    routes my_routes;
    my_routes.readData(routes_file);

    // GET ORIGIN ID
    int start_id = -1;
    while(1){
        std::cout << "Please enter a starting Airport ID: ";
        std::cin >> start_id;
        if(std::cin.fail()){
            std::cout << "Please enter an integer!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(my_airports.checkValidID(start_id))
            break;
        std::cout << "Invalid Airport ID!" << std::endl;
    }
    my_routes.printAirportWarning(start_id);

    // GET DESTINATION ID
    int end_id = -1;
    while(1){
        std::cout << "Please enter a destination Airport ID: ";
        std::cin >> end_id;
        if(std::cin.fail()){
            std::cout << "Please enter an integer!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(my_airports.checkValidID(end_id))
            break;
        std::cout << "Invalid Airport ID!" << std::endl;
    }
    my_routes.printAirportWarning(end_id);

    // INITIALIZE GRAPH
    Graph my_graph(my_airports, my_routes, start_id);    

    // SOLVE FOR BOTH ALGORITHMS
    std::cout << "Working on Dijkstra's Algorithm..." << std::endl;
    std::vector<Airport> path = my_graph.NearestPath(start_id, end_id);
    std::cout << "Working on A* Algorithm..." << std::endl << std::endl;
    std::vector<Airport> path_a_star = my_graph.NearestPath_A_Star(start_id, end_id);

    // CHECK IF THERE EXISTS A PATH
    if(path == std::vector<Airport>()){
        std::cout << "No valid path from " << my_graph.getAirportFromID(start_id).getName() << " to " << my_graph.getAirportFromID(end_id).getName() << std::endl;
        exit(EXIT_FAILURE);
    } 
    if(path_a_star == std::vector<Airport>()){
        std::cout << "No valid path from " << my_graph.getAirportFromID(start_id).getName() << " to " << my_graph.getAirportFromID(end_id).getName() << std::endl;
        exit(EXIT_FAILURE);
    }

    // PRINT DIJKSTRA RESULTS
    my_graph.print_Dijkstra(path);
    
    // PRINT A* RESULTS
    my_graph.print_A_Star(path_a_star);

    // PRINT TRAVERSAL?
    std::string input;
    while(1){
        std::cout << "Would you like to print all the aiports connected to the starting airport? (y/n) ";
        std::cin >> input;
        if(input == "y" || input == "n" || input == "Y" || input == "N")
            break;
        std::cout << "Invalid input!" << std::endl;
    }

    int amount = 0;
    if(input == "Y" || input == "y"){
        Graph::Iterator it = my_graph.begin();
        for (;it != my_graph.end(); ++it){
            std::cout << (*it).getName() << std::endl;
            amount++;
        }
        std::cout << "Number of connected airports: " << amount << std::endl;
    }

    std::cout << std::endl << "Thank you for using our program!" << std::endl;
    return 0;
}
