#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

class airports {
    private:
    // contains all read airport IDs
    vector<int> airport_ids;
    // contains all airport latitudes
    vector<double> airport_latitudes;
    // contains all airport longitudes
    vector<double> airport_longitudes;
    // contains all airport names
    vector<string> airport_names;
    // contains all airport cities
    vector<string> airport_cities;
    // contains all airport countries
    vector<string> airport_countries;

    string file_name;
    int file_length;

    map<int, int> airIDtoIndex;

    public:
    // default constructor
    airports();
    // reads data from file and stores it privately
    void readData(string input_file);
    // prints all airports
    void printData();
    // prints length of file and file name
    void printGeneralData();

    bool contains_letter(string input);
    bool contains_null(string input);

    int getNumAirports();

    int getAirID(int i);

    double getAirLat(int i);

    double getAirLong(int i);

    // index based
    std::string getAirName(int i);
    // air id based
    std::string getAirNameID(int airID);

    std::string getCountry(int i);

    bool checkValidID(int airID);
};

