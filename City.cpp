//Angela Hoch

#include "City.h"

City::City() : name(" "), person(" "), score(0), weight(-1), visited(false), disjV(false), next(NULL){}
City::City(string n) : name(n), person(" "), score(0), weight(-1), visited(false), disjV(false), next(NULL) {}
City::City(const City & x)				//copy constructor
{
	if (&(x) != NULL) {
		name = x.name;
		person = x.person;
		score = x.score;
		weight = x.weight;
		visited = x.visited;
		disjV = x.disjV;
		if (x.next != NULL) {
			next = new City(*(x.next));
		}
	}
}
City & City::operator=(const City & x)	//copy assignment constructor
{
	name = x.name;
	person = x.person;
	score = x.score;
	weight = x.weight;
	visited = x.visited;
	disjV = x.disjV;
	return *this;
	if (next != NULL) {
		delete next;
	}
	next = x.next;
}
City::~City(){							// destructor
	delete next;
	next = NULL;
}
void City::setName(string n){name = n;}
void City::setPerson(string p){person = p;}
void City::setScore(double s){score = s;}
void City::setWeight(double w){weight = w;}
void City::setVisited(bool v){visited = v;}
void City::setDisjV(bool d) {disjV = d;}
void City::setNext(City * nextCity){next = nextCity;}
string City::getName(){return name;}
string City::getPerson(){return person;}
double City::getScore(){return score;}
double City::getWeight(){return weight;}
bool City::getVisited(){return visited;}
bool City::getDisjV(){return disjV;}
City * City::getNext(){return next;}