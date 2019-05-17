#include "GrandArena.h"

GrandArena::GrandArena(int n, int *IDs) : activeGroups(), Groups(), Glad_List(), IDNode_Tree() {
    minHeap::Node** array = activeGroups.makeHeap(n, IDs);

    for(int i = 0; i < n ; i++){
        Groups.insert(array[i]->groupID, array[i]);
    }

    delete[] array;
}

GrandArena::GrandArena(const GrandArena& arena){
    activeGroups = arena.activeGroups;
    Glad_List = arena.Glad_List;
    IDNode_Tree = arena.IDNode_Tree;
    Groups = arena.Groups;
}

bool GrandArena::groupExist(int groupID){
    if(!Groups.find(groupID)){
        return false;
    }
        return true;
}

bool GrandArena::gladExist(int GladID) {
    Gladiator dummy_glad(GladID, 0);

    LinkedList<Gladiator>::Node dummy_node(dummy_glad);

    IDNode pointer(&dummy_node);
    IDNode* found = IDNode_Tree.Get(pointer);
    if(found != NULL){
        if(found->GetID() == GladID){
            return true;
        }
    }
    return false;
}

bool GrandArena::isEnoughGlads(int needed, int groupID){

    Group* group = this->Groups.find(groupID);

    int count = group->GladCount();

    if(count < needed){
        return false;
    }
    return true;
}

bool GrandArena::isLost(int ID){
    Group* group = Groups.find(ID);
    if(group->getNode() == NULL){
        return true;
    }
    return false;
}

void GrandArena::addGroup(int groupID){
    this->Groups.insert(groupID, this->activeGroups.insert(groupID));
}

void GrandArena::addGladiator(int gladID, int score, int GroupID) {
    Gladiator temp_glad(gladID, score);

    Group *group = this->Groups.find(GroupID);

    LinkedList<Gladiator>::Node *GladNode = this->Glad_List.Insert(temp_glad);

    IDNode temp_IDNode(GladNode);
    LvlNode temp_LvlNode(GladNode);

    this->IDNode_Tree.Insert(temp_IDNode);
    group->Insert(temp_LvlNode);
}

void GrandArena::Fight(int trainingGroup1, int trainingGroup2, int k1, int k2) {
    Group* group1 = this->Groups.find(trainingGroup1);
    Group* group2 = this->Groups.find(trainingGroup2);

    if(group1->GetScore(k1) == group2->GetScore(k2)){
        if(trainingGroup1 < trainingGroup2){
            activeGroups.RemoveNode(group2->getNode());
            group2->Lost();
        }
        else{
            activeGroups.RemoveNode(group1->getNode());
            group1->Lost();
        }
        return;
    }

    if(group1->GetScore(k1) > group2->GetScore(k2)){
        activeGroups.RemoveNode(group2->getNode());
        group2->Lost();
    }
    else{
        activeGroups.RemoveNode(group1->getNode());
        group1->Lost();
    }
}

int GrandArena::getMin(){
    return this->activeGroups.GetMin();
}
