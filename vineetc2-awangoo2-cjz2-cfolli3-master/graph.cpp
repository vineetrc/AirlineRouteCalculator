#include "graph.h"
#include "airport.h"

Graph::Graph(airports& air_list, routes& route_list, int start_id_){
  int size = air_list.getNumAirports();
  num_airports = size;
  start_id = start_id_;
  
  adj_mat.resize(size);
  for (int i = 0; i < size; ++i)
    adj_mat[i].resize(size); // adj matrix resize

  for(int i = 0; i < size; i++){
    airdata.push_back(Airport(air_list.getAirID(i), air_list.getAirLat(i), 
    air_list.getAirLong(i), air_list.getAirName(i), air_list.getCountry(i)));
    id_dict.insert(std::pair<int,int>(air_list.getAirID(i), i));
  }
  int routes_size = route_list.getNumRoutes();
  num_routes = routes_size;
  for (int i = 0; i < routes_size; i++) {
    int source_index = id_dict[route_list.getOriginID(i)];
    int destination_index = id_dict[route_list.getDestinationID(i)];

    Airport source = airdata[source_index];
    Airport destination = airdata[destination_index];

    double distance = source.getDistance(destination);
    if (adj_mat[source_index][destination_index] == 0) {
      adj_mat[source_index][destination_index] = distance;
    }
  }
  double long total_distance = 0;
  for(unsigned i = 0; i < adj_mat.size(); i++)
    for(unsigned j = 0; j < adj_mat[i].size(); j++)
      total_distance += adj_mat[i][j];
  avg_distance = total_distance / num_routes;
}

Graph::Iterator::Iterator(Airport& start, Graph* parent) {
  this->current = parent->id_dict[start.getID()];
  this->parent = parent;
  this->start = current;

  visited_nodes.resize(parent->airdata.size(), false);
  visited_nodes[current] = true;

  for (unsigned i = 0 ; i  < parent->adj_mat.size() ; i++) {
    if (parent->adj_mat[current][i] != 0) {
      queue.push(i);
    }
  }
}

Graph::Iterator::Iterator() {
  current = -1;
  parent = nullptr;
}

Graph::Iterator& Graph::Iterator::operator++() {
  if (!queue.empty()) {
    int node = current;

    while (visited_nodes[node] && !queue.empty()) {
      node = queue.front();
      queue.pop();
    }
    
    current = node;
    visited_nodes[current] = true;

    for (unsigned i = 0 ; i  < parent->adj_mat.size() ; i++) {
      if (!visited_nodes[i]) {
        if (parent->adj_mat[current][i] != 0) {
          queue.push(i);
        }
      }
    }
  } else {
    if (current != -1) 
      current = -1;
  }
  
  return *this;
}

Airport Graph::Iterator::operator*() {
  if (current == -1) {
    return Airport(-1,-1,-1,"","");
  }
  return parent->airdata[current];
}

bool Graph::Iterator::operator!=(const Iterator &other) {
  return !(queue.empty() && other.queue.empty() && current == -1);
}

std::vector<Airport> Graph::NearestPath(int orgID, int destID) {
  // Dijkstra's algorithm 
  /*find way to get adjacent vertices, and iterate through them*/
  /*calculate minimum distance from given vertex to other vertices*/

  int org_mat_ID = getIndex(orgID);
  int dest_mat_ID = getIndex(destID);

  std::vector<double> vert_dist; //distance from origin to vertices
  vert_dist.resize(airdata.size(), INT_MAX);

  std::vector<bool> hasVisited;   // visited
  hasVisited.resize(airdata.size(), false);

  std::vector<int> parSet; // parents, uses indexes in airdata
  parSet.resize(airdata.size(), -1);

  vert_dist[org_mat_ID] = 0;

  std::vector<double> row = adj_mat[org_mat_ID];
  bool is_iso = true;
  for (unsigned int i = 0 ; i < row.size(); i++) {
    if (row[i] != 0) {
      is_iso = false;
      break;
    }
  }
  
  if (is_iso) {
    return std::vector<Airport>();
  }

  for (unsigned int count = 0; count < airdata.size()- 1; count++){
    int minIdx= -1;
    double mindist = INT_MAX;

    // getting smallest dist not processsed
    for(unsigned int i = 0; i < hasVisited.size(); i++){
      if(vert_dist[i] <= mindist && !hasVisited[i]){
          mindist = vert_dist[i];
          minIdx= i;
      }
    }

    hasVisited[minIdx] = true;

    for(unsigned int v = 0; v < airdata.size(); v++){
      if (!hasVisited[v] && adj_mat[minIdx][v]!=0 && vert_dist[minIdx] != INT_MAX && (vert_dist[minIdx] + adj_mat[minIdx][v]) < vert_dist[v]) {
        vert_dist[v] = vert_dist[minIdx] + adj_mat[minIdx][v];
        parSet[v] = minIdx;
      }
    } 
  }

  if(parSet[dest_mat_ID]==-1)
    return std::vector<Airport>();

  std::stack<int> path;
  int cur_id = parSet[dest_mat_ID];
  path.push(dest_mat_ID);
  path.push(cur_id);
  
  while(cur_id != org_mat_ID){
    cur_id = parSet[cur_id];
    path.push(cur_id);
  }

  std::vector<Airport> finpath;
  while(!path.empty()){
    int tempair = path.top();
    finpath.push_back(airdata[tempair]);
    path.pop();
  }
  return finpath;
}

void Graph::print_Dijkstra(std::vector<Airport> path){
   // PRINT DIJKSTRA'S RESULTS
  std::cout << "Dijkstra's Output:" << std::endl;
  double path_distance = 0, dijkstras_dist_from_destination = 0;
  for( Airport x:path){
      std::cout << x.getID() << " " << x.getName() << ", "  << x.getCountry() << ", Distance from destination: " << getHeuristic(x, path.back()) << " km" << std::endl;
  }
  for(unsigned i = 0; i < path.size() - 1; i++){
      path_distance += path[i].getDistance(path[i+1]);
      if(i != 0)
        dijkstras_dist_from_destination += path[i].getDistance(path.back());
  }
  std::cout << "Total flights: " << path.size() - 1 << std::endl 
  << "Total distance traveled: "<< path_distance << " km" << std::endl
  << "Average airport distance from destination (excluding origin and destination): " << dijkstras_dist_from_destination / (path.size()-2) << std::endl << std::endl;
}

// Our Hueristic gets the distance from the current airport to the
// destination airport. This is because A-Star is a greedy algorithm
// and will ignore far airports.
double Graph::getHeuristic(Airport& current, Airport& destination){
  return current.getDistance(destination);
}

std::vector<Airport> Graph::NearestPath_A_Star(int orgID, int destID){
  int org_mat_ID = getIndex(orgID);
  int dest_mat_ID = getIndex(destID);

  std::vector<double> cost;
  cost.resize(airdata.size(), INT_MAX);

  std::vector<bool> hasVisited;
  hasVisited.resize(airdata.size(), false);

  std::vector<int> parSet; //uses indexes in airdata
  parSet.resize(airdata.size(), -1);

  cost[org_mat_ID] = 0;

  std::vector<double> row = adj_mat[org_mat_ID];
  bool is_iso = true;
  for (unsigned int i = 0 ; i < row.size(); i++) {
    if (row[i] != 0) {
      is_iso = false;
      break;
    }
  }
  
  if (is_iso) {
    return std::vector<Airport>();
  }

  for (unsigned int count = 0; count < airdata.size()- 1; count++){
    int minIdx= -1;
    double mincost = INT_MAX;

    // getting smallest cost not processsed
    for(unsigned int i = 0; i < hasVisited.size(); i++){
      if(cost[i] <= mincost && !hasVisited[i]){
          mincost = cost[i];
          minIdx= i;
      }
    }

    hasVisited[minIdx] = true;

    for(unsigned int v = 0; v < airdata.size(); v++){
      if (!hasVisited[v] && adj_mat[minIdx][v]!=0 && cost[minIdx] != INT_MAX &&
      (cost[minIdx] + adj_mat[minIdx][v] + getHeuristic(airdata[minIdx], airdata[dest_mat_ID])) < cost[v]) {
        cost[v] = cost[minIdx] + adj_mat[minIdx][v] + getHeuristic(airdata[minIdx], airdata[dest_mat_ID]);
        parSet[v] = minIdx;
      }
    } 
  }

  if(parSet[dest_mat_ID]==-1)
    return std::vector<Airport>();

  std::stack<int> path;
  int cur_id = parSet[dest_mat_ID];
  path.push(dest_mat_ID);
  path.push(cur_id);
  
  while(cur_id != org_mat_ID){
    cur_id = parSet[cur_id];
    path.push(cur_id);
  }

  std::vector<Airport> finpath;
  while(!path.empty()){
    int tempair = path.top();
    finpath.push_back(airdata[tempair]);
    path.pop();
  }
  return finpath;
  return std::vector<Airport>();
}

void Graph::print_A_Star(std::vector<Airport> path_a_star){
  // PRINT A* RESULTS
  std::cout << "A* Output:" << std::endl;
  double path_a_star_distance = 0, a_star_dist_from_destination = 0;
  for( Airport x:path_a_star){
      std::cout << x.getID() << " " << x.getName() << ", " << x.getCountry() << ", Distance from destination: " << getHeuristic(x, path_a_star.back()) << " km" << std::endl;
  }
  for(unsigned i = 0; i < path_a_star.size() - 1; i++){
    path_a_star_distance += path_a_star[i].getDistance(path_a_star[i+1]);
    if(i != 0)
      a_star_dist_from_destination += path_a_star[i].getDistance(path_a_star.back());;
  }
  std::cout << "Total flights: " << path_a_star.size() - 1 << std::endl 
  << "Total distance traveled: "<< path_a_star_distance << " km" << std::endl
  << "Average airport distance from destination (excluding origin and destination): " << a_star_dist_from_destination / (path_a_star.size()-2) << std::endl << std::endl;
}

std::vector<std::vector<double>> Graph::getMatrix() {
  return adj_mat;
}

int Graph::getAirDictID(int index){
  return airdata[index].getID();
}

int Graph::getIndex(int airID){
  return id_dict[airID];
}

Airport Graph::getAirportFromID(int airID){
  return airdata[getIndex(airID)];
}

Graph::Iterator Graph::begin(){
  return Graph::Iterator(airdata[id_dict[start_id]], this);
}
  	
Graph::Iterator Graph::end(){
  return Graph::Iterator();
}
