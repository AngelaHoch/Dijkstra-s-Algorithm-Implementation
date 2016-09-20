//Angela Hoch

#include "City.h"
#include "CityGraph.h"
#include "LinkedCities.h"
#include "Road.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

double stringToNumber(string x);
void cityInfo(CityGraph* &map, string line);
void personInfoUpdate(CityGraph* &map, string line);
//"city=FILENAME_CITIES;people=FILENAME_STUDENTS;visit=FILENAME_DESTINATIONS": instructions for running it through the shell
int main(int argc, char* argv[]) {
	fstream people, cities, toFrom;
	string startCity, endCity;
	string fileP, fileC, fileTF;
	int index = 0;
	string line = " ";
	CityGraph *cityMap;
	cityMap = new CityGraph();

	fileC = argv[1];
	fileC.erase(0, 5);						//"FILENAME_CITIES;people=FILENAME_STUDENTS;visit=FILENAME_DESTINATIONS"
	while (fileC[index] != ';') {
		index++;
	}
	fileP = fileC;							//"FILENAME_CITIES;people=FILENAME_STUDENTS;visit=FILENAME_DESTINATIONS"
	fileC = fileC.substr(0, index);			//"FILENAME_CITIES
	fileP.erase(0, (index + 8));			//"FILENAME_STUDENTS;visit=FILENAME_DESTINATIONS"
	index = 0;
	while (fileP[index] != ';') {
		index++;
	}
	fileTF = fileP;							//"FILENAME_STUDENTS;visit=FILENAME_DESTINATIONS"
	fileP = fileP.substr(0, index);			//"FILENAME_STUDENTS
	fileTF.erase(0, (index + 7));			//"FILENAME_DESTINATIONS"

	cities.open(fileC.c_str());
	if (cities.fail()) {
		cout << "Oops, no cities.\n";
		return 1;
	}
	while (getline(cities, line)) {
		if (line[0] == '#') {
			continue;
		}
		cityInfo(cityMap, line);
	}
	cities.close();

	people.open(fileP.c_str());
	if (people.fail()) {
		cout << "Oops, no people.\n";
		return 1;
	}
	while (getline(people, line)) {
		if (line[0] == '#') {
			continue;
		}
		personInfoUpdate(cityMap, line);
	}
	people.close();

	toFrom.open(fileTF.c_str());
	if (toFrom.fail()) {
		cout << "Oops, no traveling.\n";
		return 1;
	}
	while (getline(toFrom, line)) {
		if (line[0] == '#') {
			continue;
		}
		index = 0;
		while (line[index] != '\t') {
			index++;
		}
		startCity = line.substr(0, index);
		line.erase(0, (index + 1));
		endCity = line;
		cityMap->dijkstraShortPathFrom(startCity, endCity);
	}
	toFrom.close();

	cityMap->deleteGraph(cityMap);
	delete cityMap;
	cityMap = NULL;

	return 0;
}

double stringToNumber(string x) {
	stringstream ss(x);
	double y = 0;
	ss >> y;
	return y;
}
void cityInfo(CityGraph* &map, string line) {			//seperates information and adds it to the graph
	string city1, city2;
	int index = 0;
	double miles = 0;
	LinkedCities *workingWith, *makeAnother;
	Road *road;
	workingWith = NULL;
	makeAnother = NULL;
	road = NULL;

	while (line[index] != '\t' && line[index] != '\0' && line[index] != '\n') {
		index++;
	}
	city1 = line.substr(0, index);
	line.erase(0, (index + 1));
	index = 0;
	while (line[index] != '\t' && line[index] != '\0' && line[index] != '\n') {
		index++;
	}
	city2 = line.substr(0, index);
	line.erase(0, (index + 1));
	miles = stringToNumber(line);

	workingWith = map->getCity(city1);
	if (workingWith == NULL) {
		makeAnother = new LinkedCities(city1);
		map->addCity(makeAnother);
		workingWith = makeAnother;
		makeAnother = NULL;
	}
	road = new Road(city2, miles);
	map->addRoad(city1, road);
	road = NULL;

	workingWith = map->getCity(city2);
	if (workingWith == NULL) {
		makeAnother = new LinkedCities(city2);
		map->addCity(makeAnother);
		workingWith = makeAnother;
		makeAnother = NULL;
	}
	road = new Road(city1, miles);
	map->addRoad(city2, road);
	road = NULL;										//if I delete road, i will delete the information it was pointing too
}
void personInfoUpdate(CityGraph* &map, string line) {	//seperates information and updates the graph
	string city, person, hold;
	int index = 0;
	double score = 0;
	LinkedCities *workingWith;
	workingWith = NULL;

	while (line[index] != '\t' && line[index] != '\0' && line[index] != '\n') {
		index++;
	}
	hold = line.substr(0, index);
	score = stringToNumber(hold);
	line.erase(0, (index + 1));
	index = 0;
	while (line[index] != '\t' && line[index] != '\0' && line[index] != '\n') {
		index++;
	}
	person = line.substr(0, index);
	line.erase(0, (index + 1));
	city = line;

	workingWith = map->getCity(city);
	if (workingWith == NULL) {
		return;
	}
	if (workingWith->getData()->getScore() < score) {
		workingWith->getData()->setScore(score);
		workingWith->getData()->setPerson(person);
	}
}