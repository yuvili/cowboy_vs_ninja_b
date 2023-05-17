#include "Ninja.hpp"

// Constructors
Ninja::Ninja(const string& name, Point& possition, int hits, int speed) : Character(name, possition, hits), _speed(speed) {}

void Ninja::move(Character *enemy){
    Point currentPos = this->getLocation();
    Point newPos = currentPos.moveTowards(currentPos, enemy->getLocation(), _speed);
    this->setPossition(newPos);
}

void Ninja::slash(Character *enemy){
    if(enemy == this) {
        throw std::runtime_error("Can't slash self.");
    }

    if(!enemy->isAlive()) {
        throw std::runtime_error("Enemy is already dead.");
    }

    if(!isAlive()) {
        throw std::runtime_error("Dead ninja can't slash");
    }

    if(isAlive() && this->getLocation().distance(enemy->getLocation()) <= 1 && enemy != nullptr && this != enemy){
        enemy->hit(40);
    }
}

string Ninja::print() {
     if(isAlive()){
        return "(N) Name: " + this->getName() + ", Position: " + getLocation().print() + ", Hit Points: " + to_string(this->getHitPoints());
    }
    return "(N) Name: (" + this->getName() + "), Position: " + getLocation().print();
}

int Ninja::getSpeed(){
    return this->_speed;
}

void Ninja::setSpeed(int newSpeed){
    this->_speed = newSpeed;
}