#include "LvlNode.h"

LvlNode::LvlNode() : gladiator(NULL){}

LvlNode::LvlNode(LinkedList<Gladiator>::Node* gladiator)
        : gladiator(gladiator){}


bool operator==(const LvlNode& l, const LvlNode& r){
    return ((l.gladiator->getData().GetID() == r.gladiator->getData().GetID()) &&
            (l.gladiator->getData().GetLvl() == r.gladiator->getData().GetLvl()));
}
bool operator<(const LvlNode& l, const LvlNode& r){
    if(l.gladiator->getData().GetLvl() == r.gladiator->getData().GetLvl()){
        return ((l.gladiator->getData().GetID() > r.gladiator->getData().GetID()));
    }
    else{
        return l.gladiator->getData().GetLvl() < r.gladiator->getData().GetLvl();
    }
}
bool operator>(const LvlNode& l , const LvlNode& r){
    return !(l<r);
}

int LvlNode::getScore(){
    return this->gladiator->getData().GetLvl();
}