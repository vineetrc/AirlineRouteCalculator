#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>

using namespace std;

class routes {
    private:
    // contains all starting airport IDs
    vector<int> origin_ids;
    // contains all destination airport IDs
    vector<int> destination_ids;

    map<int, vector<int> > origin_to_destinations;

    // contains name of input file
    string file_name;
    // contains number of objects read
    int file_length;

    public:
    // default constructor
    routes();
    // reads data from file and stores it privately
    void readData(string input_file);
    // prints all routes
    void printData();
    // prints length of file and file name
    void printGeneralData();
    
    bool contains_letter(string input);
    bool contains_null(string input);

    int getOriginID(int index);

    int getDestinationID(int index);

    int getNumRoutes();

    void printAirportWarning(int index);
};