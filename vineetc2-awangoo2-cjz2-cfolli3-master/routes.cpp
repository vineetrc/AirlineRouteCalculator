#include "routes.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

routes::routes(){
    origin_ids = {};
    destination_ids = {};

    file_name = "";
    file_length = 0;
}

void routes::readData(string input_file){
    // airline, airline ID, source airport, source airport ID
    // destination airport, destination airport ID, codeshare
    // stops, equipment
    // Only need to read string 3 and 5
    ifstream my_file;
    my_file.open(input_file);
    if(!my_file){
        cout << "Could Not Open File: " << input_file << endl;
        cout << "Exiting program..." << endl;
        exit(EXIT_FAILURE);
        return;
    }
    file_name = input_file;

    string line;
    // iterates through entire .dat file, line by line
    while(getline(my_file, line)){
        int string_number = 0;
        stringstream s_stream(line);
        while(s_stream.good() && string_number < 7){
            string substring;
            // parse data by comma
            getline(s_stream, substring, ',');

            if(string_number == 4)
                origin_ids.push_back(stoi(substring));
            else if(string_number == 6)
                destination_ids.push_back(stoi(substring));
            string_number++;
        }
    }
    file_length = origin_ids.size();
    my_file.close();
}

void routes::printData(){
    cout << "File Length: " << file_length << endl;
    for(int i = 0; i < file_length; i++){
        cout << origin_ids[i] << ", "
        << destination_ids[i] << endl;
    }
}

void routes::printGeneralData(){
    cout << "File: " << file_name << endl;
    cout << "File Length: " << file_length << endl;
    cout << "Num Origins: " << origin_ids.size() << endl;
    cout << "Num Destinations: " << destination_ids.size() <<endl;
}

bool routes::contains_null(string input){
    bool has_null = false;
    for(unsigned i = 0; i < input.length() - 1; i++){
        if(input[i] == '\\' && input[i + 1] == 'N')
            has_null = true;
    }
    return has_null;
}

int routes::getOriginID(int index) {
    return origin_ids[index];
}

int routes::getDestinationID(int index) {
    return destination_ids[index];
}

int routes::getNumRoutes() {
    return (origin_ids.size() + destination_ids.size()) / 2;
}

void routes::printAirportWarning(int index){
    pair<bool, bool> result;
    if (find(origin_ids.begin(), origin_ids.end(), index) != origin_ids.end())
        result.first = true;
    else
        result.first = false;
    if (find(destination_ids.begin(), destination_ids.end(), index) != destination_ids.end())
        result.second = true;
    else
        result.second = false;
    if(result.first == false && result.second == false){
        cout << "Warning: Airport " << index << " has no incoming or outgoing routes" << endl << "Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    else if(result.first == false)
        cout << "Warning: Airport " << index << " has no outgoing routes" << endl;
    else if(result.second == false)
        cout << "Warning: Airport " << index << " has no incoming routes" << endl;
    else
        cout << "Airport " << index << " looks good to go!" << endl;
    cout << endl;
}