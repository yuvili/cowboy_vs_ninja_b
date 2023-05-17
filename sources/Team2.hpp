#ifndef TEAM2_HPP
#define TEAM2_HPP
#include "Team.hpp"

namespace ariel{
    class Team2 : public ariel::Team {
        public:
            Team2(Character* leader);

            void attack(Team*);
            void print();
    };
};
#endif