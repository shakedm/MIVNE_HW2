#ifndef MIVNE_WET2_IDNODE_H
#define MIVNE_WET2_IDNODE_H

#include "Gladiator.h"
#include "LinkedList.h"

class IDNode{
public:
    LinkedList<Gladiator>::Node* gladiator;
public:
    IDNode(LinkedList<Gladiator>::Node* gladiator);

    friend bool operator==(const IDNode& l,const IDNode& r);
    friend bool operator<(const IDNode& l, const IDNode& r);
    friend bool operator>(const IDNode& l, const IDNode& r);
    friend bool operator!=(const IDNode& l, const IDNode& r);

    int GetID();

};

#endif //MIVNE_WET2_IDNODE_H
