#include <string>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#include "SmartTeam.hpp"

namespace ariel{
    SmartTeam::SmartTeam(Character* leader) : Team(leader) {}

    void SmartTeam::attack(Team* enemy){
        if(enemy == nullptr) {
            throw std::invalid_argument("Can't attack nullptr.");
        }
        
        if(enemy == this) {
            throw std::invalid_argument("Can't attack self.");
        }

        if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
            return;
        }

        if (!this->getLeader()->isAlive()) {
            chooseLeader(enemy);
        }

        Character* target = getTarget(enemy);
        if(target == nullptr) return;

        for(size_t i = 0; i < getTeam().size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!target->isAlive()) {
                target = getTarget(enemy);
                if(target == nullptr) return;
            }

            Cowboy* cb = dynamic_cast<Cowboy*>(getTeam().at(i));
            if(cb != nullptr && cb->isAlive()) {
                if(cb->hasboolets()) {
                    cb->shoot(target);
                }
                else {
                    cb->reload();
                }
            }
            else {
                Ninja* ninja = dynamic_cast<Ninja*>(getTeam().at(i));
            
                if(ninja != nullptr && ninja->isAlive()) {
                    if(ninja->distance(target) < 1) {
                        ninja->slash(target);
                    }
                    else {
                        ninja->move(target);
                    }
                }
            }
        }
    }


    void SmartTeam::chooseLeader(Team* enemy) {
        int maxScore = 0;
        Character* selectedCandidate = nullptr;
        double distance = std::numeric_limits<double>::max();
        std::vector<Character*> teamMembers = this->getTeam();
        
        for(size_t i = 0; i < teamMembers.size(); i++) {
            int score = 0;

            Character* leadCandidate = teamMembers.at(i);
            if(!leadCandidate->isAlive()) {
                continue;
            }

            for(size_t j = 0; j < teamMembers.size(); j++) {
                if(leadCandidate == teamMembers.at(j)) {
                    continue;
                }

                YoungNinja* yninja = dynamic_cast<YoungNinja*>(teamMembers.at(j));
                TrainedNinja* tninja = dynamic_cast<TrainedNinja*>(teamMembers.at(j));
                OldNinja* oninja = dynamic_cast<OldNinja*>(teamMembers.at(j));
                Cowboy* cowboy = dynamic_cast<Cowboy*>(teamMembers.at(j));
                if(yninja != nullptr && yninja->distance(leadCandidate) <= yninja->getSpeed()) {
                    score++;
                    continue;
                }
                else if(tninja != nullptr && tninja->distance(leadCandidate) <= tninja->getSpeed()) {
                    score++;
                    continue;
                }
                else if(oninja != nullptr && oninja->distance(leadCandidate) <= oninja->getSpeed()) {
                    score++;
                    continue;
                }
                else if(cowboy != nullptr) {
                    score++;
                    continue;
                }
            }
            
            for(size_t j = 0; j < enemy->getTeam().size(); j++){
                Character* enemyMember = enemy->getTeam().at(j);

                YoungNinja* yninja = dynamic_cast<YoungNinja*>(leadCandidate);
                TrainedNinja* tninja = dynamic_cast<TrainedNinja*>(leadCandidate);
                OldNinja* oninja = dynamic_cast<OldNinja*>(leadCandidate);
                Cowboy* cowboy = dynamic_cast<Cowboy*>(leadCandidate);
                if(yninja != nullptr && yninja->distance(enemyMember) <= yninja->getSpeed()) {
                    score++;
                    continue;
                }
                else if(tninja != nullptr && tninja->distance(enemyMember) <= tninja->getSpeed()) {
                    score++;
                    continue;
                }
                else if(oninja != nullptr && oninja->distance(enemyMember) <= oninja->getSpeed()) {
                    score++;
                    continue;
                }
                else if(cowboy != nullptr && cowboy->hasboolets()) {
                    score++;
                    continue;
                }
            }

            if(maxScore < score) {
                maxScore = score;
                selectedCandidate = leadCandidate;
            }
        }
        if(selectedCandidate != nullptr) {
            this->setLeader(selectedCandidate);
        }
    }

    Character* SmartTeam::getTarget(Team* enemy) {
        double distance = std::numeric_limits<double>::max();
        size_t index = (size_t)-1;
        std::vector<Character*> enemyMembers = enemy->getTeam();
        
        for(size_t i = 0; i < enemyMembers.size(); i++) {
            Character* optionalTarget = enemyMembers.at(i);
            
            if (optionalTarget->isAlive() && optionalTarget != this->getLeader() && optionalTarget->distance(this->getLeader()) < distance) {
               distance = optionalTarget->distance(this->getLeader());
               index = i;
            }
        }
        
        return (index != -1) ? enemyMembers.at(index) : nullptr;
    }
}
