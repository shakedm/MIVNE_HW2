#ifndef MIVNE_WET2_DYNAMICHASH_H
#define MIVNE_WET2_DYNAMICHASH_H

#include "SPlay_Tree.h"
#include "Group.h"

class dynamicHash {
private:
    SPlay_Tree<Group>* table;
    int tableSize;
    int currentSize;

    static  const  int INIT_SIZE = 2;

    int HashFunction(int key){
        return key % tableSize;
    }

//dogo true = increase the size , dogo false means he goes home decrease the size
    void resize(bool dogo) {
        //TODO make resize to increase or decrease size of the array.
        int newSize = dogo ? 2 * tableSize : tableSize / 2;
        SPlay_Tree<Group> *oldTable = table;
        SPlay_Tree<Group> *newTable = new SPlay_Tree<Group>[newSize];
        int oldSize = tableSize;

        this->tableSize = newSize;
        this->table = newTable;
        rehash(oldTable,oldSize,newTable, newSize);
        delete[] oldTable;
    }

    void rehash(SPlay_Tree<Group>* oldTable,int oldSize , SPlay_Tree<Group>* newTable,
                int newSize){

        for (int i = 0; i < oldSize ; ++i) {
            while(!oldTable[i].isempty()){
                Group curr(oldTable[i].getMax());

                int new_loc = HashFunction(curr.GetID());

                newTable[new_loc].Insert(curr);
                oldTable[i].Delete(curr);
            }
        }
    }


public:
  //~ctor
    dynamicHash():table( new SPlay_Tree<Group>[INIT_SIZE]), tableSize(INIT_SIZE),
          currentSize(0) {};


    ~dynamicHash(){
        delete[](table);
    }

    //inserts new group by the tree func. O(log(n))
    void insert(int groupID){

        this->currentSize++;
        if(currentSize == tableSize){
            resize(true);
        }
        int key = HashFunction(groupID);
        Group toAdd(groupID, NULL);
        table[key].Insert(toAdd);

    }

    //returns pointer to the group that was found by tree function O(log(n))
    Group* find(int ID){
        if (ID< 0)
            return NULL;
        int key= HashFunction(ID);
        Group find(ID, NULL);
        return table[key].Get(find);
    }

    //removes a group from the table, resizes it if the table too big O(n) on resize
    void remove(int ID){
        if(find(ID)== NULL)
            return;
        this->currentSize--;
        Group toRemove(ID, NULL);
        table[HashFunction(ID)].Delete(toRemove);


        if (currentSize <= tableSize/4)
            resize(false);

    }

};


#endif //MIVNE_WET2_DYNAMICHASH_H
