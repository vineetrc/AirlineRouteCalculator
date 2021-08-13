// Class representing node in graph
#pragma once
#include <cmath>
#include <string>
#include <vector>

class Airport {
public:
  Airport(int id, double latitude, double longitude, std::string name, std::string country);

  double getDistance(Airport& other);
  int getID();
  std::string getName();
  std::string getCountry();

  bool operator==(const Airport &other) const;
private:
  int id;
  double latitude;
  double longitude;
  std::string name;
  std::string country;
};
