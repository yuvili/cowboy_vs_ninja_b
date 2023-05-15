#include <string>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#include "Team.hpp"

namespace ariel {
    Team::Team(Character* leader) {
        if(leader->getInTeam()){
            throw std::runtime_error(leader->getName() + " is already in a team.");
        }

        this->leader = leader;
        members.push_back(leader);
        leader->setInTeam(true);
    }

    Team::~Team(){
        for(std::vector<Character*>::iterator iter=members.begin(); iter != members.end(); iter++) {
            delete *iter;
        }
    } 

    Team::Team(const Team& other) : Team(other.leader) {
        for(size_t i = 0; i < other.members.size(); i++) {
            this->members.push_back(other.members[i]);
        }
    }

    Team::Team(Team&& other) noexcept : Team(other.leader) {
        for(size_t i = 0; i < other.members.size(); i++) {
            this->members.push_back(other.members[i]);
        }
        other.leader = nullptr;
        other.members.clear();
    }

    Team& Team::operator=(const Team& other){
        this->leader = other.leader;
        this->members = other.members;
        return *this;
    }

    Team& Team::operator=(Team&& other) noexcept{
        this->leader = other.leader;
        this->members = other.members;
        return *this;
    }


    void Team::add(Character* member){
        if(members.size() >= 10){
            throw std::runtime_error("Max characters in team excided.");
        }
        if(member->getInTeam()){
            throw std::runtime_error(member->getName() + " is already in a team.");
        }
        
        members.push_back(member);
        member->setInTeam(true);
    }

    void Team::attack(Team* enemy){
        if(enemy == nullptr) {
            throw std::invalid_argument("Can't attack nullptr.");
        }
        
        if(enemy == this) {
            throw std::invalid_argument("Can't attack self.");
        }

        if(enemy->stillAlive() <= 0) {
                throw std::runtime_error("Can't attack dead team.");
        }

        if (!this->leader->isAlive()) {
            chooseLeader();
        }

        Character* target = getTarget(enemy);

        for(size_t i = 0; i < this->members.size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!target->isAlive()) {
                target = getTarget(enemy);
            }

            Cowboy* cb = dynamic_cast<Cowboy*>(this->members.at(i));

            if(cb != nullptr && cb->isAlive()) {
                if(cb->hasboolets()) {
                    cb->shoot(target);
                }
                else {
                    cb->reload();
                }
            }
        }

        for(size_t i = 0; i < this->members.size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!target->isAlive()) {
                target = getTarget(enemy);
            }

            Ninja* ninja = dynamic_cast<Ninja*>(this->members.at(i));
            
            if(ninja != nullptr && ninja->isAlive()) {
                if(ninja->distance(target) <= 1) {
                    ninja->slash(target);
                }
                else {
                    ninja->move(target);
                }
            }
        }
    }

    int Team::stillAlive(){
        int counter = 0;
        for(size_t i = 0; i < members.size(); i++){
            if(members.at(i)->isAlive()) {
                counter++;
            }
        }
        return counter;
    }

    void Team::print(){
        cout << "Team members:" << endl;
        for(size_t i = 0; i < members.size(); i++) {
            Cowboy* cb = dynamic_cast<Cowboy*>(members.at(i));
            if(cb != nullptr) {
                cout << "   " << cb->print() << endl;
            }
        }

        for(size_t i = 0; i < members.size(); i++) {

            Ninja* ninja = dynamic_cast<Ninja*>(members.at(i));
            
            if(ninja != nullptr) {
                cout << "   " << ninja->print() << endl;
            }
        }
    }

    void Team::chooseLeader() {
        double distance = std::numeric_limits<double>::max();
        size_t index = (size_t)-1;
        
        for(size_t i = 0; i < members.size(); i++) {
            Character* optionalLeader = members.at(i);
            if (optionalLeader->isAlive() && optionalLeader != this->leader && optionalLeader->distance(this->leader) < distance) {
               distance = optionalLeader->distance(this->leader);
               index = i;
            }
        }
        
        if (index != -1) {
            this->leader = members.at(index);
        }
    }

    Character* Team::getTarget(Team* enemy) {
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

    std::vector<Character*> Team::getTeam() const {
        return this->members;
    }

    Character* Team::getLeader() const {
        return this->leader;
    }
}
