#include "airport.h"

Airport::Airport(int id, double latitude, double longitude, std::string name, std::string country) {
  this->name = name;
  this->id = id;
  this->latitude = latitude;
  this->longitude = longitude;
  this->country = country;
}

double Airport::getDistance(Airport& other) {
  // Source https://www.geeksforgeeks.org/haversine-formula-to-find-distance-between-two-points-on-a-sphere/

  double lat1 = this->latitude, lat2 = other.latitude, lon1 = this->longitude, lon2 = other.longitude;
  double dLat = (lat2 - lat1) * M_PI / 180.0;
  double dLon = (lon2 - lon1) * M_PI / 180.0;
  
  // convert to radians
  lat1 = (lat1) * M_PI / 180.0;
  lat2 = (lat2) * M_PI / 180.0;
  
  // apply formulae
  double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
  double rad = 6371;
  double c = 2 * asin(sqrt(a));
  return rad * c;
}

int Airport::getID(){
  return id;
}

std::string Airport::getName(){
  return name;
}

std::string Airport::getCountry(){
  return country;
}

bool Airport::operator==(const Airport &other) const{
  if(this -> id == other.id &&
  this -> latitude == other.latitude &&
  this -> longitude == other.longitude &&
  this -> name == other.name)
    return true;
  else
    return false;
}