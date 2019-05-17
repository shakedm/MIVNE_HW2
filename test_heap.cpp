
#include "assert.h"
#include "minHeap.h"
#include <ostream>



int main(){
    int array[12];
    int num=12;
    int ID=1;

    for (int i = 0; i <num ; ++i) {
        array[i]= ID++;
        if (i%2==0)
            ID+=3;
    }
    minHeap mi;
    array[0]=2l;
    array[1]=38;
    array[2]=47;
    array[3]=24;
    array[4]=45;
    array[5]=42;
    array[6]=14;

    minHeap nein;
    nein.makeHeap(num,array);
    for (int k = 0; k <num ; ++k) {
        std::cout<< nein.GetMin() << std::endl;
        nein.DelMin();
    }
    minHeap::Node** work= mi.makeHeap(num,array);
    for (int l = 0; l <num ; ++l) {
        std::cout<<work[l]->index<<std::endl;
        std::cout<< "ID: " << work[l]->groupID<< std::endl;
    }
    delete[](work);
    mi.DelMin();
    num=mi.getNumGroups();
    for (int j = 0; j <num ; ++j) {
        //std::cout<< mi.GetMin() << std::endl;
        mi.DelMin();
    }
    mi.insert(2);
    mi.insert(4);
    mi.insert(7);
    mi.insert(1);
    mi.insert(9);
    mi.insert(10);
    mi.insert(20);
    mi.insert(18);
    mi.insert(15);
    mi.insert(12);

    mi.insert(13);

    num=mi.getNumGroups();
    for (int j = 0; j <num ; ++j) {
        std::cout<< mi.GetMin() << std::endl;
        mi.DelMin();
    }
    mi.insert(1);
    return 0;
}

