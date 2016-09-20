//Angela Hoch

#include "LinkedCities.h"

LinkedCities::LinkedCities() : highways(new Road()), data(new City()), next(NULL), pPath(NULL){}
LinkedCities::LinkedCities(string n) : highways(new Road()), data(new City(n)), next(NULL), pPath(NULL) {}
LinkedCities::LinkedCities(const LinkedCities & x)
{
	highways = new Road(*(x.highways));
	data = x.data;
	if (x.next != NULL) {
		next = new LinkedCities(*(x.next));
	}
}
LinkedCities & LinkedCities::operator=(const LinkedCities & x)
{
	if (this != NULL) {
		if (highways != NULL) {
			delete highways;
		}
		if (next != NULL) {
			delete next;
		}
		if (pPath != NULL) {
			delete pPath;
		}
	}
	highways = x.highways;
	data = x.data;
	next = x.next;
	pPath = x.pPath;
	return *this;
}
LinkedCities::~LinkedCities()
{
	delete highways;
	delete pPath;
	delete next;
	highways = NULL;
	next = NULL;
	pPath = NULL;
}
void LinkedCities::setHighway(Road * r){highways = r;}
void LinkedCities::setData(City* d){data = d;}
void LinkedCities::setNext(LinkedCities * n){next = n;}
void LinkedCities::setPPath(LinkedCities * p){pPath = p;}
Road * LinkedCities::getHighway(){return highways;}
City* LinkedCities::getData(){return data;}
LinkedCities * LinkedCities::getNext(){return next;}
LinkedCities * LinkedCities::getPPath(){return pPath;}
void LinkedCities::deleteCities()									//deletes all the cities in the graph
{
	LinkedCities *current;
	current = this;
	while (current != NULL && current->data->getName() != " ") {
		if (current->highways->noRoads() == false) {				//if the city has roads, delete them
			current->highways->deleteRoads();
		}
		current = current->next;
	}
	if (current != NULL) {
		delete current;
		current = NULL;
	}
}
void LinkedCities::addCity(LinkedCities * newCity)
{
	LinkedCities *current, *current2;
	current = this;
	while (current->next != NULL && current->data->getName() != " ") {
		current = current->next;
	}
	current2 = current->next;					//current 2 either == NULL or an empty node
	current->next = newCity;
	newCity->next = current2;
	current = NULL;
	current2 = NULL;
}
bool LinkedCities::noCities()
{
	return (this == NULL);		//returns true if this has nothing in it
}
void LinkedCities::addRoad(string city, Road* r)
{
	LinkedCities *current;
	current = this;
	while (current->data->getName() != city) {
		current = current->next;
	}
	current->highways = current->highways->addRoad(r);
}