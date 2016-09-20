//Angela Hoch

#include "Road.h"

Road::Road() : nextCity(" "), length(-1), next(NULL){}
Road::Road(string goingTo, double l) : nextCity(goingTo), length(l), next(NULL) {}
Road::Road(const Road & x)				//copy constructor
{
	nextCity = x.nextCity;
	length = x.length;
	if (x.next != NULL) {
		next = new Road(*(x.next));
	}
}
Road & Road::operator=(const Road & x)	//copy assingment constructor
{
	if (this != NULL) {
		if (next != NULL) {
			delete next;
		}
		nextCity = x.nextCity;
		length = x.length;
		next = x.next;
	}
	else if (this == NULL) {
		nextCity = x.nextCity;
		length = x.length;
		next = x.next;
	}
	return *this;
}
Road::~Road(){}					//destructor
void Road::setNextCity(string goingTo){nextCity = goingTo;}
void Road::setLength(double l){length = 0;}
void Road::setNext(Road * theNext){next = theNext;}
string Road::getNextCity(){return nextCity;}
double Road::getLength(){return length;}
Road * Road::getNext(){return next;}
void Road::deleteRoads()			//delete roads
{
	Road *current, *current2;
	current = this;
	current2 = NULL;
	while (current != NULL) {
		current2 = current->next;
		delete current;
		current = current2;
	}
	if (current != NULL) {
		delete current;
		current = NULL;
	}
	if (current2 != NULL) {
		delete current2;
		current2 = NULL;
	}
}
Road* Road::addRoad(Road * newRoad)
{
	Road *current;
	current = this;
	newRoad->next = current;
	current = newRoad;
	return current;
}
bool Road::noRoads(){return (this == NULL);}