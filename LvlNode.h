#ifndef MIVNE_WET2_LVLNODE_H
#define MIVNE_WET2_LVLNODE_H

#include "Gladiator.h"
#include "LinkedList.h"

class LvlNode{
public:
    LinkedList<Gladiator>::Node* gladiator;
public:
    LvlNode();
    //~LvlNode() = default;
    LvlNode(LinkedList<Gladiator>::Node* gladiator);
    friend bool operator==(const LvlNode& l, const LvlNode& r);
    friend bool operator<(const LvlNode& l, const LvlNode& r);
    friend bool operator>(const LvlNode& l , const LvlNode& r);

    int getScore();
};


#endif //MIVNE_WET2_LVLNODE_H
