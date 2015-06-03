#include "robot.hpp"

Robot::Robot(Map const& map) : coordX(0), coordY(0), totalCost(0), map(map) {
}

float Robot::getEastCost() const {
	return map.eastCost(coordX, coordY);
}

float Robot::goEast() {
	float cost = map.eastCost(coordX, coordY);
	coordX++;
	totalCost += cost;
	return cost;
}

float Robot::getNorthCost() const {
	return map.northCost(coordX, coordY);
}

float Robot::goNorth() {
	float cost = map.northCost(coordX, coordY);
	coordY++;
	totalCost += cost;
	return cost;
}

float Robot::getNorthEastCost() const {
	return map.northEastCost(coordX, coordY);
}

float Robot::goNorthEast() {
	float cost = map.northEastCost(coordX, coordY);
	coordX++;
	coordY++;
	totalCost += cost;
	return cost;
}

float Robot::getTotalCost() const {
	return totalCost;
}

int Robot::getCoordX() const {
	return coordX;
}

int Robot::getCoordY() const {
	return coordY;
}

Map const& Robot::getMap() const {
	return map;
}
