

#include "dynamicHash.h"

int main(){

dynamicHash hushhash;
    Group* group;
    hushhash.insert(2);
    hushhash.insert(3);
    hushhash.insert(6);
    hushhash.insert(8);
    hushhash.insert(209);
    hushhash.insert(35);
    group =hushhash.find(35);
    std::cout<<group->GetID() << std::endl;



    return 0;
}

