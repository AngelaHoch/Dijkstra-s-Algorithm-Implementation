//Angela Hoch

#include <iostream>
#include <string>
using namespace std;

#ifndef C_H
#define C_H
class City {
public:
	City();
	City(string n);
	City(const City &x);				//copy constructor
	City& operator=(const City &x);		//copy assignment constructor
	~City();							//destructor
	void setName(string n);
	void setPerson(string p);
	void setScore(double s);
	void setWeight(double w);
	void setVisited(bool v);
	void setDisjV(bool d);
	void setNext(City *n);
	string getName();
	string getPerson();
	double getScore();
	double getWeight();
	bool getVisited();					//getVisited is used for the dijkstra algorithm, to keep track of what paths have been tested
	bool getDisjV();					//getDisjV is used for the dijkstra algorithm, to show the final path
	City* getNext();
private:
	string name, person;
	double score, weight;
	bool visited, disjV;
	City *next;
};
#endif