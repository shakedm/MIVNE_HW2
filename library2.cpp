#include "library2.h"
#include "GrandArena.h"

static bool inputCheck(int n, int *trainingGroupsIDS){
    if(n < 2){
        return false;
    }
    for(int i = 0; i < n; i++){
        if(trainingGroupsIDS < 0){
            return false;
        }
    }
    return true;
};

void* init(int n, int *trainingGroupsIDs){
    if(!inputCheck(n, trainingGroupsIDs)){
    return NULL;
    }
    GrandArena* arena = new GrandArena(n, trainingGroupsIDs);
    return (void*)(arena);
}

StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if(!DS || trainingGroupID < 0){
        return INVALID_INPUT;
    }
    GrandArena* arena = (GrandArena*)(DS);

     if(arena->groupExist(trainingGroupID)){
     return FAILURE;
     }
    //TODO: Allocation_Error
     arena->addGroup(trainingGroupID);
    return SUCCESS;
}

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if(!DS || trainingGroup<0 || score<0 || gladiatorID<0){
        return INVALID_INPUT;
    }
    GrandArena* arena = (GrandArena*)(DS);
    if(!arena->groupExist(trainingGroup)){
        return FAILURE;
    }
    if(arena->gladExist(gladiatorID)){
        return FAILURE;
    }
    //TODO: allocation error
    arena->addGladiator(gladiatorID,score,trainingGroup);
    return SUCCESS;
}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1, int k2){
    if(!DS || k1<=0 || k2<=0 || trainingGroup1<0 || trainingGroup2<0){
        return INVALID_INPUT;
    }
    if(trainingGroup1 == trainingGroup2){
        return FAILURE;
    }
    GrandArena* arena = (GrandArena*)(DS);
    if(!arena->groupExist(trainingGroup1) || !arena->groupExist(trainingGroup2)){
        return FAILURE;
    }
    if(arena->isLost(trainingGroup1) || arena->isLost(trainingGroup2)){
        return FAILURE;
    }
    if(!arena->isEnoughGlads(k1, trainingGroup1) || !arena->isEnoughGlads(k2, trainingGroup2)){
        return FAILURE;
    }
    //TODO: allocation error
    arena->Fight(trainingGroup1, trainingGroup2, k1, k2);
    return SUCCESS;
    }

StatusType getMinTrainingGroup(void *DS, int *trainingGroup){
    if(!DS || !trainingGroup){
        return INVALID_INPUT;
    }
    GrandArena* arena = (GrandArena*)(DS);
    //TODO: allocation error
    *trainingGroup = arena->getMin();
    return SUCCESS;
}

void quit(void** DS){
    delete (GrandArena*)(*DS);
    *DS=NULL;
}