#include <string>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#include "Team2.hpp"

namespace ariel{
    Team2::Team2(Character* leader) : Team(leader) {}

    void Team2::add(Character* member){
        if(this->members.size() >= 10){
            throw std::runtime_error("Max characters in team excided.");
        }
        if(member->getInTeam()){
            throw std::runtime_error(member->getName() + " is already in a team.");
        }
        
        this->members.push_back(member);
        member->setInTeam(true);
    }

    int Team2::stillAlive(){
        int counter = 0;
        for(size_t i = 0; i < members.size(); i++){
            if(members.at(i)->isAlive()) {
                counter++;
            }
        }
        return counter;
    }

    void Team2::attack(Team* enemy){
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
            chooseLeader();
        }

        Character* target = getTarget(enemy);

        for(size_t i = 0; i < getTeam().size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!target->isAlive()) {
                target = getTarget(enemy);
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

    void Team2::print(){
        cout << "Team members:" << endl;
        for(size_t i = 0; i < getTeam().size(); i++) {
            Cowboy* cb = dynamic_cast<Cowboy*>(getTeam().at(i));
            if(cb != nullptr) {
                cout << "   " << cb->print() << endl;
            }
            else {
                Ninja* ninja = dynamic_cast<Ninja*>(getTeam().at(i));
            
                if(ninja != nullptr) {
                    cout << "   " << ninja->print() << endl;
                }
                else {
                    throw std::runtime_error("Character type not found.");
                }
            }
        }
    }

    std::vector<Character*> Team2::getTeam() const {
        return this->members;
    }

    Character* Team2::getLeader() const {
        return this->leader;
    }
}
