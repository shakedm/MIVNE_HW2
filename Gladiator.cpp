#include "Gladiator.h"

Gladiator::Gladiator(int ID, int Level)
        : GladiatorID(ID), Level(Level){}

int Gladiator::GetID() const{
    return GladiatorID;
}
int Gladiator::GetLvl() const{
    return Level;
}

bool operator==(const Gladiator& l, const Gladiator& r){
    return l.GetID() == r.GetID();
}
bool operator<(const Gladiator& l, const Gladiator& r){
    return l.GetID() < r.GetID();
}
bool operator>(const Gladiator& l, const Gladiator& r){
    return !(l<r);
}
bool operator!=(const Gladiator& l, const Gladiator& r){
    return !(l==r);
}