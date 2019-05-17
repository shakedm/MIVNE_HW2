#include "Group.h"

Group::Group(){
    this->GroupID = 0;
    this->node = NULL;
}

Group::Group(int ID, minHeap::Node* node) : GroupID(ID), gladiators(){
    this->node = node;
}

void Group::Insert(LvlNode& glad_pointer){
    this->gladiators.Insert(glad_pointer);
}

bool operator==(const Group& l,const Group& r) {
    return l.GroupID == r.GroupID;
}
bool operator<(const Group& l, const Group& r){
    return  l.GroupID < r.GroupID;
}
bool operator>(const Group& l, const Group& r){
    return !(l<r);
}
bool operator!=(const Group& l, const Group& r){
    return !(l==r);
}

int Group::GladCount(){
    return this->gladiators.getCount();
}
int Group::GetID() {
    return this->GroupID;
}

int Group::GetScore(int num){
    return gladiators.getScore(num);
}

minHeap::Node* Group::getNode(){
    return this->node;
}

void Group::Lost(){
    this->node = NULL;
}