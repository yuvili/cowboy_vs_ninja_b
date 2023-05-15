#ifndef YOUNGNINJA_HPP
#define YOUNGNINJA_HPP
#include <string>
#include "Ninja.hpp"
using namespace std;

class YoungNinja : public Ninja {
    public:
        YoungNinja(const string& name, Point possition);
};
#endif