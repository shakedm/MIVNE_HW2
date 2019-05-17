#include "GrandArena.h"
#include <stdlib.h>

using namespace std;

int main(){

    int array[6];
    array[0] = 50;
    array[1] = 23;
    array[2] = 92;
    array[3] = 12;
    array[4] = 92;
    array[5] = 80;
    GrandArena arena(6, array);

    /*
     * GroupExist test
     */
    if(arena.groupExist(50)){
        cout << "test 01 Passed" << endl;
    }
    if(arena.groupExist(23)){
        cout << "test 02 Passed" << endl;
    }
    if(arena.groupExist(92)){
        cout << "test 03 Passed" << endl;
    }
    if(!arena.groupExist(1)){
        cout << "test 04 Passed" << endl;
    }
    if(!arena.groupExist(5)){
        cout << "test 05 Passed" << endl;
    }
    if(!arena.groupExist(1005)){
        cout << "test 06 Passed" << endl;
    }

    /*
     * GladiatorExist test
     */
    if(!arena.gladExist(1)){
        cout << "test 07 Passed" << endl;
    }

    /*
     * Input new gladiators in the system
     */

    arena.addGladiator(1, 100, 50);
    arena.addGladiator(10, 1000, 50);

    arena.addGladiator(2, 200, 23);
    arena.addGladiator(6, 600, 23);
    arena.addGladiator(7, 700, 23);

    arena.addGladiator(3, 300, 12);
    arena.addGladiator(5, 500, 12);

    arena.addGladiator(8, 800, 50);

    arena.addGladiator(9, 900, 92);
    arena.addGladiator(4, 400, 92);

    if(arena.gladExist(1)){
        cout << "test 08 Passed" << endl;
    }

    if(!arena.isEnoughGlads(11, 50)){
        cout << "test 09 Passed" << endl;
    }

    if(arena.isEnoughGlads(2, 92)){
        cout << "test 10 Passed" << endl;
    }

    arena.Fight(23, 12, 2, 2);
}

