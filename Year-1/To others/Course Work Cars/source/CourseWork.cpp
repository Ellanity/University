#include <iostream>
#include <string>

#include "CourseWork.h"


/* Class Car constructors */
Car::Car() {
	std::string name;
	int speed;
	std::string type;
}
Car::Car(std::string name, int speed) {
	this->name = name;
	this->speed = speed;
	this->type = "simple";
}

/* Class Car methods */
int Car::cost() {
	return (speed * 100);
}
void Car::updatingModel() {
	speed += 10;
}

/* Class Car Getters and Setters */
std::string Car::getName() { return name; }
int Car::getSpeed() { return speed; }
std::string Car::getType() { return type; }
int Car::getCost() { return cost(); }

void Car::setName(std::string name) { this->name = name; }
void Car::setSpeed(int speed) { this->speed = speed; }



/* Class ExecutiveCar constructors */
ExecutiveCar::ExecutiveCar() : Car(){}
ExecutiveCar::ExecutiveCar(std::string name, int speed) : Car(name, speed) {
		this->name = name;
		this->speed = speed;
		this->type = "executive";
	}

/* Class ExecutiveCar methods */
int ExecutiveCar::cost() {
	return (speed * 250);
}
void ExecutiveCar::updatingModel() {
	speed += 5;
}

/* Class ExecutiveCar Getters and Setters */
int ExecutiveCar::getCost() { return cost(); }



/* Overloading of some operators */
bool operator < (Car c1, Car c2) {
	return (c1.getName() < c2.getName());
}
bool operator==(Car c1, Car c2)
{
	return (c1.getName() == c2.getName() &&
		c1.getSpeed() == c2.getSpeed() &&
		c1.getType() == c2.getType());
}
Car& Car::operator= (const Car& c) {
	name = c.name;
	speed = c.speed;
	type = c.type;
	return *this;
}