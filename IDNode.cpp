#include "IDNode.h"

IDNode::IDNode(LinkedList<Gladiator>::Node* gladiator)
        : gladiator(gladiator){}

bool operator==(const IDNode& l,const IDNode& r){
    return l.gladiator->getData() == r.gladiator->getData();
}
bool operator<(const IDNode& l, const IDNode& r){
    return l.gladiator->getData() < r.gladiator->getData();
}
bool operator>(const IDNode& l, const IDNode& r){
    return !(l<r);
}
bool operator!=(const IDNode& l, const IDNode& r){
    return !(l==r);
}

int IDNode::GetID(){
    return this->gladiator->getData().GetID();
}