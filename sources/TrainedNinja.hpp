#ifndef TRAINEDNINJA_HPP
#define TRAINEDNINJA_HPP
#include <string>
#include "Ninja.hpp"
using namespace std;

class TrainedNinja : public Ninja {
    public:
        TrainedNinja(const string& name, Point possition);
};
#endif