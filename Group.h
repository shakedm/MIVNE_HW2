#ifndef MIVNE_WET2_GROUP_H
#define MIVNE_WET2_GROUP_H

#include "Ranked_Tree.h"
#include "minHeap.h"

class Group{
private:
    int GroupID;
    Ranked_Tree gladiators;
    minHeap::Node* node;
public:
    Group();
    Group(int ID, minHeap::Node* node);
    void Insert(LvlNode& glad_pointer); //inserts a new pointer to the tree.
    friend bool operator==(const Group& l,const Group& r);
    friend bool operator<(const Group& l, const Group& r);
    friend bool operator>(const Group& l, const Group& r);
    friend bool operator!=(const Group& l, const Group& r);

    int GladCount();
    int GetID();
    int GetScore(int num);
    minHeap::Node* getNode();
    void Lost();
};

#endif //MIVNE_WET2_GROUP_H
