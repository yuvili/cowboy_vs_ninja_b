#ifndef COWBOY_HPP
#define COWBOY_HPP
#include <string>
#include "Character.hpp"
using namespace std;

class Cowboy : public Character {
    private:
        int bullets_count;

    public:
        // Constructors
        Cowboy(string, Point);

        // Functions
        void shoot(Character *enemy); // If cowbow not dead and boolets_count>0 it shoot the enamy and subtract 10 hit_point from the enamy and boolets_count--
        bool hasboolets();
        void reload(); // reloads 6 new boolets
        string print() override;
};
#endif
