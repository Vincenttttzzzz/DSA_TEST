#include "Actor.h"
#include <iostream>
using namespace std;

Actor::Actor() {};

Actor::Actor(int ActorID, std::string Name, int Year) {
	actorID = ActorID;
	name = Name;
	year = Year;
}

// Implementation of Getters and Setters
int Actor::getActorID() const { return actorID; }
string Actor::getName() const { return name; }
int Actor::getYear() const { return year; }

void Actor::setActorID(int newActorID) { actorID = newActorID; }
void Actor::setName(const string& newName) { name = newName; }
void Actor::setYear(int newYear) { year = newYear; }


void Actor::print() {
	cout << "Actor ID: " << actorID << endl;
	cout << "Name: " << name << endl;
	cout << "Year: " << year << endl;
}

//friend ostream& operator<<(ostream& os, const Actor& actor) {
//    os << "ActorID: " << actorID
//        << ", Name: " << name
//        << ", Birth Year: " << birthYear;
//    return os;
//}