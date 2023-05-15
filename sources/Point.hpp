#ifndef POINT_HPP
#define POINT_HPP
#include <string>
using namespace std;

class Point{
    private:
        double _x, _y;
    
    public:
        Point();
        Point(double, double);
        ~Point(); // Destructor
        Point(const Point& other); // Copy constructor
        Point(Point&& other) noexcept; // Move constructor

        Point& operator=(const Point&);
        Point& operator=(Point&&) noexcept;

        friend std::ostream &operator<<(std::ostream& ost, const Point& point);

        double distance(const Point&);
        string print();
        static Point moveTowards(Point&, Point&, double);
        double getX();
        double getY();
};
#endif