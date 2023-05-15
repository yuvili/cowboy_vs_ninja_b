#include <bits/stdc++.h>
#include "Point.hpp"
using namespace std;

Point::Point() : _x(0.0), _y(0.0) {}

Point::Point(double x, double y) : _x(x), _y(y) {}

Point::~Point(){} // Destructor

// Copy constructor
Point::Point(const Point& other) : Point(other._x, other._y) {}

// Move constructor
Point::Point(Point&& other) noexcept : _x(other._x), _y(other._y){} 

Point& Point::operator=(const Point& other) {
    _x = other._x;
    _y = other._y;
    return *this;
}

Point& Point::operator=(Point&& other) noexcept{
    this->_x = other._x;
    this->_y = other._y;
    return *this;
}

std::ostream &operator<<(std::ostream& ost, const Point& point) {
    ost << "(" << point._x << "," << point._y << ")" << endl;
    return ost;
}

double Point::distance(const Point& point2){
    return sqrt(pow(point2._x - _x, 2) + pow(point2._y - _y, 2) * 1.0);
}

string Point::print(){
    return "(" + to_string(_x) + "," + to_string(_y) + ")";
}

Point Point::moveTowards(Point& src, Point& dest, double distance){
    if(distance < 0) {
        throw std::invalid_argument("Can't move in negative length.");
    }

    double dist = src.distance(dest);
    if(dist <= distance) {
        return dest;
    }

    double xDist = (dest._x - src._x) / dist;
    double yDist = (dest._y - src._y) / dist;

    double newX = src._x + (xDist * distance);
    double newY = src._y + (yDist * distance);
    return Point(newX, newY);
}

double Point::getX(){
    return _x;
}

double Point::getY(){
    return _y;
}