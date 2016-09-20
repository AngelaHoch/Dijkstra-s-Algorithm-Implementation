//Angela Hoch

#include <iostream>
#include <string>
#include "Road.h"
using namespace std;

#ifndef LC_H
#define LC_H
class LinkedCities {
public:
	LinkedCities();
	LinkedCities(string n);								
	LinkedCities(const LinkedCities &x);				//copy constructor
	LinkedCities& operator=(const LinkedCities &x);		//copy assingment constructor
	~LinkedCities();									//destructor
	void setHighway(Road* r);
	void setData(City *d);
	void setNext(LinkedCities *n);
	void setPPath(LinkedCities *p);
	Road* getHighway();
	City* getData();
	LinkedCities* getNext();
	LinkedCities* getPPath();
	void deleteCities();
	void addCity(LinkedCities* newCity);
	bool noCities();
	void addRoad(string city, Road* r);
private:
	Road* highways;					//points to a linked list of highways associated with city
	City* data;						//general city data
	LinkedCities* next, *pPath;		//next: next city in the graph, pPath: path found through dijkstra'a algorithm, the previous city used to visit it
};
#endif