#pragma once
#ifndef CourseWork_H
#define CourseWork_H

#include <string>

/* Main class of Car */
class Car {
protected:
	/* Class Car protected fields to inherit them */
	std::string name;
	int speed;
	std::string type;
	
private:
	/* Class Car private methods */
	int cost();

public:
	/* Class Car constructors */
	Car();
	Car(std::string name, int speed);
	
	/* Class Car public methods */
	void updatingModel();
	
	/* Class Car Getters and Setters */
	std::string getName();
	int getSpeed();
	std::string getType();
	int getCost();

	void setName(std::string name);
	void setSpeed(int speed);
	
	Car& operator= (const Car& c);
};


/* Class the heir of Car with some differences */
class ExecutiveCar : public Car
{
private:
	/* Class ExecutiveCar private methods */
	int cost();

public:
	/* Class ExecutiveCar constructors */
	ExecutiveCar();
	ExecutiveCar(std::string name, int speed);

	/* Class ExecutiveCar public methods */
	void updatingModel();

	/* Class ExecutiveCar Getters and Setters */
	int ExecutiveCar::getCost();
};


/* Overloading of some operators */
bool operator< (Car c1, Car c2);
bool operator== (Car c1, Car c2);
#endif // !1