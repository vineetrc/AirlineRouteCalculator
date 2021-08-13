#include "airports.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

airports::airports(){
    airport_ids = {};
    airport_latitudes = {};
    airport_longitudes = {};
    airport_names = {};
    airport_cities = {};
    airport_countries = {};
    file_name = "";
    file_length = 0;
}

void airports::readData(string input_file){
    // airport id, name, city, country, IATA, ICAO, latitude, longitude,
    // altitude, timezone, DST, Tz database time zone, type, source
    // Only need to read string 0, 1, 2, 3, 6, 7
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
        while(s_stream.good()){
            string substring;
            // parse data by comma
            getline(s_stream, substring, ',');
            // if string contains , add to next input
            if(contains_letter(substring) && substring.back() != '"'){
                string second_string;
                getline(s_stream, second_string, ',');
                substring = substring + ',' + second_string;
            }
            // if string contains \N, skip over it
            if(contains_null(substring)){
                string_number+= 2;
                continue;
            }
            // remove quotation marks from string
            substring.erase(remove(substring.begin(), substring.end(), '"'), substring.end());
            
            if(string_number == 0){
                airport_ids.push_back(stoi(substring));
                airIDtoIndex[stoi(substring)] = airport_ids.size() - 1;
            }
            else if(string_number == 1)
                airport_names.push_back(substring);
            else if(string_number == 2)
                airport_cities.push_back(substring);
            else if(string_number == 3)
                airport_countries.push_back(substring);
            else if(string_number == 6)
                airport_latitudes.push_back(stod(substring));
            else if(string_number == 7)
                airport_longitudes.push_back(stod(substring));
            string_number++;
        }
    }
    file_length = airport_ids.size();
    my_file.close();
}

bool airports::contains_letter(string input){
    bool has_letter = false;
    for(unsigned i = 0; i < input.length(); i++){
        if(isalpha(input[i]))
            has_letter = true;
    }
    return has_letter;
}

bool airports::contains_null(string input){
    bool has_null = false;
    for(unsigned i = 0; i < input.length() - 1; i++){
        if(input[i] == '\\' && input[i + 1] == 'N')
            has_null = true;
    }
    return has_null;
}


void airports::printData(){
    cout << "File Length: " << file_length << endl;
    for(int i = 0; i < file_length; i++){
        cout << airport_ids[i] << ", "
        << airport_names[i] << ", "
        << airport_cities[i] << ", "
        << airport_countries[i] << ", "
        << airport_latitudes[i] << ", "
        << airport_longitudes[i] << endl;
    }
}

void airports::printGeneralData(){
    cout << "File: " << file_name << endl;
    cout << "File Length: " << file_length << endl;
}

int airports::getNumAirports(){
    return airport_ids.size();
}

int airports::getAirID(int i){
    return airport_ids[i];
}

double airports::getAirLat(int i){
    return airport_latitudes[i];
}

double airports::getAirLong(int i){
    return airport_longitudes[i];
}

std::string airports::getAirName(int i){
    return airport_names[i];
}

std::string airports::getAirNameID(int airID){
    if(airIDtoIndex.find(airID) != airIDtoIndex.end())
        return getAirName(airIDtoIndex[airID]);
    else
        return "Could not find air ID";
}

std::string airports::getCountry(int i){
    return airport_countries[i];
}

bool airports::checkValidID(int airID){
    if (find(airport_ids.begin(), airport_ids.end(), airID) != airport_ids.end())
        return true;
    else
        return false;
}