//Angela Hoch

#include <iostream>
#include <string>
#include "LinkedCities.h"
using namespace std;

#ifndef CG_H
#define CG_H
class CityGraph {
public:
	CityGraph();
	CityGraph(const CityGraph &x);				//copy constructor
	CityGraph& operator=(const CityGraph &x);	//copy assignment constructor
	~CityGraph();								//destructor
	void setHead(LinkedCities *h);
	LinkedCities* getHead();
	void dijkstraShortPathFrom(string startcity, string target);	//uses dijkstra's algorithm to find the shortest path between 2 cities
	void printPeople(LinkedCities* roadtrip, string ending);		//prints the students selected from eash city on the path
	void deleteGraph(CityGraph* &map);								//deletes visited cities from the graph
	void addCity(LinkedCities* newCity);							//adds city
	void addRoad(string city, Road* r);								//adds a new road connecting cities
	LinkedCities* getCity(string name);
	bool emptyCities();							//returns true if graph is empty
	bool emptyRoads();							//returns true if nothing connects to the city
private:
	LinkedCities *head;
};
#endif