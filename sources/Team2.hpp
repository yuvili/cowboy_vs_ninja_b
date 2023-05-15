#ifndef TEAM2_HPP
#define TEAM2_HPP
#include "Team.hpp"

namespace ariel{
    class Team2 : public ariel::Team {
        public:
            Team2(Character* leader);

            void add(Character* member) override;
            int stillAlive();
            void attack(Team*);
            void print();

            std::vector<Character*> getTeam() const;
            Character* getLeader() const;
    };
};
#endif