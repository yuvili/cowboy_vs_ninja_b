#ifndef NINJA_HPP
#define NINJA_HPP
#include <string>
#include "Character.hpp"
using namespace std;


class Ninja : public Character {
    public:
        // Constructor
        Ninja(const string&, Point&, int, int);

        // Functions
        virtual void move(Character *enemy);
        virtual void slash(Character *enemy);
        string print() override;

        int _speed;
};
#endif