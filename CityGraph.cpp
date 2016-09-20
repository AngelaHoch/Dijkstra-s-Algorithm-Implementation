//Angela Hoch

#include "CityGraph.h"

CityGraph::CityGraph()
{
	head = new LinkedCities();
}
CityGraph::CityGraph(const CityGraph & x)
{
	head = new LinkedCities(*(x.head));
}
CityGraph & CityGraph::operator=(const CityGraph & x)
{
	if (this != NULL) {
		if (head != NULL) {
			delete head;
		}
		head = x.head;
	}
	else if (this == NULL) {
		head = x.head;
	}
	return *this;
}
CityGraph::~CityGraph()
{
	delete head;
	head = NULL;
}
void CityGraph::setHead(LinkedCities * h){head = h;}
LinkedCities * CityGraph::getHead(){return head;}
void CityGraph::dijkstraShortPathFrom(string startcity, string target)
{
	LinkedCities *current, *current2, *setRightCopy;
	CityGraph *mapCopy;
	mapCopy = this;							//use mapCopy for all editing
	double min = -1;
	double dis = 0;
	current = mapCopy->head;
	current2 = NULL;
	setRightCopy = NULL;					//reversed path in the end
	Road *roads, *temp;
	roads = NULL;
	temp = NULL;
	string hold = " ";
	string hold2 = " ";
	//working in reverse: starting with the end city, ending with the start, because the pPath pointers will be backwards
	while (current != NULL && current->getData()->getName() != " ") {
		if (current->getData()->getName() == target) {
			current->getData()->setWeight(0);				//weight records the distance from city A to city B
			current2 = new LinkedCities(*current);
			break;
		}
		current = current->getNext();
	}														//current 2 points to the working city and its weight to 0
	
	setRightCopy = current2;								//just to start the loop correctly //couldve also used a do-while loop
	while (setRightCopy->getData()->getName() != startcity) {		//setRightCopy is updated during the loop to hold the current of the last node worked on
																	//so the loop exits after the city I need has been visited
		roads = current2->getHighway();
		current2->getData()->setDisjV(true);
		setRightCopy = current2;

		while (roads != NULL && roads->getLength() != -1) {			//goes through all the cities that current2 connects too //-1 is used in road empty node
			current = mapCopy->getCity(roads->getNextCity());		//finds the city in the map that the road connects with
			if (current->getData()->getDisjV() == true) {
				current = NULL;										//if its already fininshed with, skip this city
			}
			else if (current->getData()->getWeight() == -1) {		//if the city's weight hasnt been adjusted yet, it hasnt been visited
				dis = (roads->getLength()) + (current2->getData()->getWeight());
				current->getData()->setWeight(dis);
				current->setPPath(current2);						//if this is the first weight it receives, then its prev is set to its main connection
				dis = 0;
			}
			else {
				dis = (roads->getLength()) + (current2->getData()->getWeight());	//(weight of current2 + length between current 2 and 1)
				if (dis < (current->getData()->getWeight())) {
					current->getData()->setWeight(dis);
					current->setPPath(current2);
				}
				dis = 0;
			}			//sets the new weights
			roads = roads->getNext();
		}
		current = mapCopy->head;
		while(current != NULL && current->getData()->getName() != " "){
			if ((current->getData()->getDisjV() == false) && ((current->getData()->getWeight() < min && current->getData()->getWeight() > 0) || (current->getData()->getWeight() != min && min < 0))) {//out of all unvisited cities, find the smallest distance and set to current2
				min = (current->getData()->getWeight());
				current2 = current;
			}								//decides the next road to venture
			current = current->getNext();
											//sets new weights for cities next to this one//loads a path like a tree with everything pointing to the start city
		}
		min = -1;
	}
	//setRightCopy currently holds the path from startcity -> endcity
	printPeople(setRightCopy, target);
	//set all visited cities to true
	while (setRightCopy->getData()->getName() != " ") {
		if (setRightCopy->getData()->getVisited() == false) {
			setRightCopy->getData()->setVisited(true);
		}
		if (setRightCopy->getData()->getName() == target) { break; }
		hold = setRightCopy->getPPath()->getData()->getName();		//hold = the name of the city setRightCopy is goinng to
		hold2 = setRightCopy->getData()->getName();					//hold2 = name of setRightCopy
		roads = setRightCopy->getHighway();
		if (roads->getNextCity() == hold) {
			setRightCopy->setHighway(roads->getNext());
			roads->setNext(NULL);
			delete roads;
			roads = NULL;
		}
		else {
			temp = roads;
			roads = roads->getNext();	//if the first road isnt what I want, then there is more then one road
			while (roads->getNextCity() != hold && roads->getNextCity() != " ") {
				temp = temp->getNext();
				roads = roads->getNext();
			}							//roads is now the edge that points to hold2 //temp is right before roads
			temp->setNext(roads->getNext());
			roads->setNext(NULL);
			delete roads;
			roads = NULL;
		}
		current = this->getCity(hold);
		roads = current->getHighway();
		if (roads->getNextCity() == hold2) {
			current->setHighway(roads->getNext());
			roads->setNext(NULL);
			delete roads;
			roads = NULL;
		}
		else {
			temp = roads;
			roads = roads->getNext();				//if the first road isnt what I want, then there is more then one road
			while (roads->getNextCity() != hold2 && roads->getNextCity() != " ") {
				temp = temp->getNext();
				roads = roads->getNext();
			}										//roads is now the edge that points to hold2 //temp is right before roads
			temp->setNext(roads->getNext());
			roads->setNext(NULL);
			delete roads;
			roads = NULL;
		}
		setRightCopy = setRightCopy->getPPath();
	}
	current = head;
	while (current->getData()->getName() != " ") {
		current->getData()->setWeight(-1);
		current->getData()->setDisjV(false);
		current->setPPath(NULL);
		current = current->getNext();
	}
}
void CityGraph::printPeople(LinkedCities * roadtrip, string ending)
{
	LinkedCities *current;
	current = roadtrip;
	string person;

	while (current != NULL) {
		if (current->getData()->getVisited() == false) {
			person = current->getData()->getPerson();
			cout << person << endl;
		}
		if (current->getData()->getName() == ending) { break; }
		current = current->getPPath();
	}
}
void CityGraph::deleteGraph(CityGraph* &map)
{
	map->head->deleteCities();
	map->head = NULL;
}
void CityGraph::addCity(LinkedCities * newCity)
{
	newCity->setNext(head);
	head = newCity;
}
void CityGraph::addRoad(string city, Road* r)
{
	head->addRoad(city, r);
}
LinkedCities * CityGraph::getCity(string name)
{
	LinkedCities *current;
	current = head;
	while (current->getData()->getName() != name && (current != NULL && current->getData()->getName() != " ")) {
		current = current->getNext();
	}
	if (current == NULL || current->getData()->getName() == " ") {
		return NULL;
	}
	return current;
}
bool CityGraph::emptyCities(){return head->noCities();}
bool CityGraph::emptyRoads(){return head->getHighway()->noRoads();}