#ifndef OLDNINJA_HPP
#define OLDNINJA_HPP
#include <string>
#include "Ninja.hpp"
using namespace std;

class OldNinja : public Ninja {
    public:
        OldNinja(const string& name, Point possition);
};
#endif