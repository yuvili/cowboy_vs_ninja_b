#ifndef SMARTTEAM_HPP
#define SMARTTEAM_HPP
#include "Team.hpp"

namespace ariel{
    class SmartTeam : public ariel::Team {
        public:
            SmartTeam(Character* leader);
            void add(Character* member) override;
            void attack(Team*);

            void chooseLeader(Team* enemy);
            Character* getTarget(Team* enemy);
    };
};
#endif