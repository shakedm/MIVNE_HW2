#ifndef MIVNE_WET2_GRANDARENA_H
#define MIVNE_WET2_GRANDARENA_H

#include "Group.h"
#include "LinkedList.h"
#include "Gladiator.h"
#include "IDNode.h"
#include "SPlay_Tree.h"
#include "dynamicHash_LinkedList.h"
#include "minHeap.h"

class GrandArena {
private:
    minHeap activeGroups;
    dynamicHash Groups;
    LinkedList<Gladiator> Glad_List;
    SPlay_Tree<IDNode> IDNode_Tree;

public:
    GrandArena(int n, int *IDs);
    //~GrandArena(){};
    GrandArena(const GrandArena& arena);


    bool groupExist(int groupID);
    bool gladExist(int GladID);
    bool isEnoughGlads(int needed, int groupID);
    bool isLost(int ID);

    void addGroup(int groupID);
    void addGladiator(int gladID, int score, int groupID);
    void Fight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    int getMin();

};


#endif //MIVNE_WET2_GRANDARENA_H
