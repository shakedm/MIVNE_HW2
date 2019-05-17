

#include <iostream>
#include "minHeap.h"
using std::cout;
int main(){
    minHeap my;
    int num=3;
    int array[num];
    array[0]=10;
    array[1]=5;
    array[2]=11;

    my.makeHeap(num,array);

    minHeap::Node* tmp= my.getGroupByIndex(1);
    std::cout<<"ID: " <<tmp->groupID << " index:" << tmp->index <<std::endl;
    tmp=my.getGroupByIndex(2);
    std::cout<<"ID: " <<tmp->groupID << " index:" << tmp->index <<std::endl;
    tmp=my.getGroupByIndex(3);
    std::cout<<"ID: " <<tmp->groupID << " index:" << tmp->index <<std::endl;
    my.insert(3);
    my.insert(13);
    my.insert(27);
    my.insert(0);
    my.insert(7);
    my.insert(67);
    my.DelMin();
    my.GetMin();
    my.insert(48);
    my.insert(100);
    my.insert(1201);
    my.insert(1211);
    my.DelMin();
    my.GetMin();
    my.RemoveNode(my.insert(20));
    cout<< my.getNumGroups()<< std::endl;

    for (int i = 1; i <my.getNumGroups()+1 ; ++i) {
        tmp=my.getGroupByIndex(i);

        std::cout << "ID: " << tmp->groupID << " index:" << tmp->index
                  << std::endl;
    }
    my.RemoveNode(my.getGroupByIndex(my.getNumGroups()));


    for (int j = 0; j <9 ; ++j) {
        my.DelMin();
    }

    int f=0;
    return 0;
}

