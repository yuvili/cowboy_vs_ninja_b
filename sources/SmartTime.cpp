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

    void SmartTeam::add(Character* member){
        if(this->members.size() >= 10){
            throw std::runtime_error("Max characters in team excided.");
        }
        if(member->getInTeam()){
            throw std::runtime_error(member->getName() + " is already in a team.");
        }
        
        this->members.push_back(member);
        member->setInTeam(true);
    }

    void SmartTeam::chooseLeader(Team* enemy) {
        int maxScore = 0;
        Character* selectedCandidate = nullptr;
        double distance = std::numeric_limits<double>::max();
        
        for(size_t i = 0; i < members.size(); i++) {
            int score = 0;

            Character* leadCandidate = members.at(i);
            if(!leadCandidate->isAlive()) {
                continue;
            }

            for(size_t j = 0; j < members.size(); j++) {
                if(leadCandidate == members.at(j)) {
                    continue;
                }

                YoungNinja* yninja = dynamic_cast<YoungNinja*>(this->members.at(j));
                TrainedNinja* tninja = dynamic_cast<TrainedNinja*>(this->members.at(j));
                OldNinja* oninja = dynamic_cast<OldNinja*>(this->members.at(j));
                Cowboy* cowboy = dynamic_cast<Cowboy*>(this->members.at(j));
                if(yninja != nullptr && yninja->distance(leadCandidate) <= yninja->_speed) {
                    score++;
                    continue;
                }
                else if(tninja != nullptr && tninja->distance(leadCandidate) <= tninja->_speed) {
                    score++;
                    continue;
                }
                else if(oninja != nullptr && oninja->distance(leadCandidate) <= oninja->_speed) {
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
                if(yninja != nullptr && yninja->distance(enemyMember) <= yninja->_speed) {
                    score++;
                    continue;
                }
                else if(tninja != nullptr && tninja->distance(enemyMember) <= tninja->_speed) {
                    score++;
                    continue;
                }
                else if(oninja != nullptr && oninja->distance(enemyMember) <= oninja->_speed) {
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
            this->leader = selectedCandidate;
        }
    }

    Character* SmartTeam::getTarget(Team* enemy) {
        double distance = std::numeric_limits<double>::max();
        size_t index = (size_t)-1;
        
        for(size_t i = 0; i < enemy->members.size(); i++) {
            Character* optionalTarget = enemy->members.at(i);
            
            if (optionalTarget->isAlive() && optionalTarget != this->leader && optionalTarget->distance(this->leader) < distance) {
               distance = optionalTarget->distance(this->leader);
               index = i;
            }
        }
        
        return (index != -1) ? enemy->members.at(index) : nullptr;
    }
}
