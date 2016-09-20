//Angela Hoch

#include <iostream>
#include <string>
#include "City.h"
using namespace std;

#ifndef R_H
#define R_H
class Road {
public:
	Road();
	Road(string goingTo, double l);
	Road(const Road &x);				//copy constructor
	Road& operator=(const Road &x);		//copy assignment constructor
	~Road();							//destructor
	void setNextCity(string goingTo);
	void setLength(double l);
	void setNext(Road *theNext);
	string getNextCity();
	double getLength();
	Road* getNext();
	void deleteRoads();					//deletes roads
	Road* addRoad(Road* newRoad);
	bool noRoads();
private:
	string nextCity;
	double length;
	Road *next;
};
#endif