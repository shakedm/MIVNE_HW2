
#include "Ranked_Tree.h"
#include <stdlib.h>

using namespace std;

static void inputGlad(Ranked_Tree& tree,LinkedList<Gladiator>& list, int ID, int score){
    Gladiator Glad_Input(ID, score);
    LvlNode Node_Input(list.Insert(Glad_Input));
    tree.Insert(Node_Input);
}

int main(){
    Ranked_Tree tree;
    LinkedList<Gladiator> list;

    if(tree.isempty()){
        cout << "test 00 Passed" << endl;
    }
    //1 element
    inputGlad(tree, list, 1, 10);
    if(tree.getCount() == 1){
        cout << "Test 01 Passed" << endl;
    }
    if(tree.getScore(1) == 10){
        cout << "test 02 Passed" << endl;
    }
    if(!tree.isempty()){
        cout << "test 03 Passed" << endl;
    }

    //2 elements
    inputGlad(tree, list, 8, 80);
    if(tree.getCount() == 2){
        cout << "test 04 Passed" << endl;
    }
    if(tree.getScore(2) == 90){
        cout << "test 05 Passed" << endl;
    }
    if(tree.getScore(1) == 80) {
        cout << "test 06 Passed" << endl;
    }

    //adding shitload of elements
    inputGlad(tree, list, 9, 90);
    inputGlad(tree, list, 2, 20);
    inputGlad(tree, list, 4, 40);
    inputGlad(tree, list, 6, 60);
    inputGlad(tree, list, 7, 70);
    inputGlad(tree, list, 3, 30);
    inputGlad(tree, list, 10, 100);
    inputGlad(tree, list, 5, 50);
    if(tree.getCount() == 10){
        cout << "test 07 Passed" << endl;
    }
    if(tree.getScore(1) == 100){
        cout << "test 08 Passed" << endl;
    }
    if(tree.getScore(2) == 190){
        cout << "test 10 Passed" << endl;
    }
    if(tree.getScore(3) == 270){
        cout << "test 11 Passed" << endl;
    }
    if(tree.getScore(4) == 340){
        cout << "test 12 Passed" << endl;
    }
    if(tree.getScore(5) == 400){
        cout << "test 13 Passed" << endl;
    }
    if(tree.getScore(6) == 450){
        cout << "test 14 Passed" << endl;
    }
    if(tree.getScore(7) == 490){
        cout << "test 15 Passed" << endl;
    }
    if(tree.getScore(8) == 520){
        cout << "test 16 Passed" << endl;
    }
    if(tree.getScore(9) == 540){
        cout << "test 17 Passed" << endl;
    }
    if(tree.getScore(10) == 550){
        cout << "test 18 Passed" << endl;
    }
}