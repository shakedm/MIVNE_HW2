#ifndef RANKED_SPLAY_TREE_H
#define RANKED_SPLAY_TREE_H

//#include "GrandArena.h"
#include <iostream>
#include <malloc.h>
#include "LvlNode.h"


/*
 * This enum is used in the Find function to determite from where the root went
 * If it went Left or Right. will help Find_aux to identify if to ouse
 * LL or LR (in case of LEFT), or RR or RL (in case of RIGHT).
 */
//enum RLocation {RIGHT, LEFT};

class Ranked_Tree { //serves as a permanent head for the tree
    enum Location {RIGHT, LEFT};
    friend class LvlNode;
private:
    class Node { //Nodes themselves in the root.
    public:
        LvlNode info; //The data it holds.

        //this is the nodes information.
        int right_childs;
        int left_childs;
        int right_score;
        int left_score;

        Node *left; //left child
        Node *right; //right child
        //constructors
        Node(LvlNode data) : info(data), right_childs(0), left_childs(0),
                             right_score(0), left_score(0),
                             left(NULL), right(NULL){};

        Node(const Node &node) : info(node.info) {
            if (node.left != NULL) {
                this->left = new Node(*(node.left));
            }
            else{
                this->left = NULL;
            }
            if (node.right != NULL) {
                this->right = new Node(*(node.right));
            }
            else{
                this->right = NULL;
            }
            this->right_childs = node.right_childs;
            this->left_childs = node.left_childs;
            this->right_score = node.right_score;
            this->left_score = node.left_score;

        };

        //destructor destroys recursive all the node to the rest it connected.
        ~Node() {
            delete (this->right);
            this->right = NULL;
            delete (this->left);
            this->left = NULL;
        }
    };

    Node *root; //head of the tree.
    int count;

    /*
     * The next functions are ZigZags that we've learnt in class, I've decided
     * to name them LL,LR,RR,RL,L,R because I kept on getting confused while
     * writing the code between Zig and Zag.
     */
    //LL
    static void LLsplay(Node *origin, Node *cur_node) {
        Node *X = cur_node->left;
        Node *B = X->right;
        origin->left = X;
        X->right = cur_node;
        cur_node->left = B;

        //keep the rank up soldier! LL

        cur_node->left_childs = X->right_childs;
        cur_node->left_score = X->right_score;

        X->right_childs += cur_node->right_childs + 1;
        X->right_score += cur_node->right_score+cur_node->info.getScore();
    }

    //LR
    static void LRsplay(Node *origin, Node *cur_node) {
        Node *X = cur_node->right;
        Node *B = X->left;
        origin->left = X;
        X->left = cur_node;
        cur_node->right = B;

        //keep the rank up soldier! LR

        cur_node->right_childs = X->left_childs;
        cur_node->right_score = X->left_score;

        X->left_childs += cur_node->right_childs + 1;
        X->left_score += cur_node->right_score+cur_node->info.getScore();
    }

    //RL
    static void RLsplay(Node *origin, Node *cur_node) {
        Node *X = cur_node->left;
        Node *B = X->right;
        origin->right = X;
        X->right = cur_node;
        cur_node->left = B;

        //keep the rank up soldier! RL

        cur_node->left_childs = X->right_childs;
        cur_node->left_score = X->right_score;

        X->right_childs += cur_node->right_childs + 1;
        X->right_score += cur_node->right_score+cur_node->info.getScore();
    }

    //RR
    static void RRsplay(Node *origin, Node *cur_node) {
        Node *X = cur_node->right;
        Node *B = X->left;
        origin->right = X;
        X->left = cur_node;
        cur_node->right = B;

        //keep the rank up soldier! LR

        cur_node->right_childs = X->left_childs;
        cur_node->right_score = X->left_score;

        X->left_childs += cur_node->right_childs + 1;
        X->left_score += cur_node->right_score+cur_node->info.getScore();
    }

    //L - used by the root of the tree.
    void Lsplay() {
        Node *org_root = this->root;
        if (org_root->left == NULL) {
            return;
        }
        Node *X = org_root->left;
        Node *B = X->right;
        this->root = X;
        X->right = org_root;
        org_root->left = B;

        //keep the rank up soldier! LR

        org_root->left_childs = X->right_childs;
        org_root->left_score = X->right_score;

        X->right_childs += org_root->right_childs + 1;
        X->right_score += org_root->right_score + org_root->info.getScore();

    }

    //R - used by the root of the tree.
    void Rsplay() {
        Node *org_root = this->root;
        if (org_root->right == NULL) {
            return;
        }
        Node *X = org_root->right;
        Node *B = X->left;
        this->root = X;
        X->left = org_root;
        org_root->right = B;

        //keep the rank up soldier! LR

        org_root->right_childs = X->left_childs;
        org_root->right_score = X->left_score;

        X->left_childs += org_root->left_childs + 1;
        X->left_score += org_root->left_score + org_root->info.getScore();
    }

    /*
     * A recursive function to find the wanted Node and Splay (using LL, RR,
     * LR, RL) up. O(logn) because it will call itself as many times as the
     * height of the said tree. n being the number of nodes in the tree.
     */
    static void
    Find_aux(LvlNode key, Node *cur_node, Node *origin, Location parent) {
        if (cur_node == NULL) {
            return;
        }
        if (cur_node->info == key) {
            return;
        }
        LvlNode cur_info = cur_node->info;
        if (cur_info > key) { //going to the left side of the tree

            if (cur_node->left == NULL) {
                return;
            }

            Find_aux(key, cur_node->left, cur_node, LEFT);

            if (parent == RIGHT) {
                RLsplay(origin, cur_node);
                //RL
            } else if (parent == LEFT) {
                LLsplay(origin, cur_node);
                //LL
            }
        } else if (cur_info < key) { //Going to the right side of the tree

            if (cur_node->right == NULL) {
                return;
            }
            Find_aux(key, cur_node->right, cur_node, RIGHT);
            if (parent == RIGHT) {
                RRsplay(origin, cur_node);
                //RR
            } else if (parent == LEFT) {
                LRsplay(origin, cur_node);
                //LR
            }
        }
    }

    /*
     * Find function as describes in the PDF sheets of splay.pdf.
     * It checks all the needed information about the tree and if it's in need
     * of going deep (empty tree, only one node in the tree).
     * L or R the needed node.
     * O(logn) because of the recursion that it calls, while n stands for
     * the number of nodes in the tree.
     * Returns the wanted Node of the tree.
     */
    Node *Find(LvlNode key) {
        if (root == NULL) { //checks for empty tree
            return NULL;
        }
        if (root->right == NULL &&
            root->left == NULL) {//checks for one node only
            return this->root;
        }
        LvlNode cur_info = root->info;

        if (cur_info == key) { //information located in the root situation
            return root;
        }
        Node *root = this->root;
        if (cur_info > key) { //Going Left in the tree
            Find_aux(key, root->left, root, LEFT);
            this->Lsplay();
        } else if (cur_info < key) { //Going right in the tree
            Find_aux(key, root->right, root, RIGHT);
            this->Rsplay();
        }
        return this->root;
    }

    /*
     * As described in the PDF, find the min of the tree, O(Log(n)).
     * Then splays it up using the Find function.
     */
    Node *FindMin() {
        if (root == NULL) {
            return NULL;
        }
        Node *node = root;
        while (node->left != NULL) {
            node = node->left;
        }
        return Find(node->info);
    }

    /*
     * As described in the PDF, find hte max of the tree, O(log(n)).
     * then splays it up using the find function.
     */
    Node *FindMax() {
        if (root == NULL) {
            return NULL;
        }
        Node *node = root;
        while (node->right != NULL) {
            node = node->right;
        }
        return Find(node->info);
    }

    /*
     * As described in the PDF, given two trees, it combines them into
     * the main tree (this), when calling Join all the previous tree is lost.
     * and the lesser and bigger tree are getting absorbed by that tree.
     * O(logn) because of the searching for the min or max of the trees
     * to put them back together.
     */
    void Join(Ranked_Tree &lesser, Ranked_Tree &bigger) {

        if (lesser.root == NULL) {
            bigger.FindMin();
            this->root = bigger.root;
            bigger.root = NULL;
            if (this->root != NULL) {
                this->root->left = NULL;

            }

        } else {
            lesser.FindMax();
            this->root = lesser.root;

            lesser.root = NULL;

            if (this->root != NULL) {
                this->root->right = bigger.root;
                bigger.root = NULL;

                if(this->root->right) {
                    this->root->right_score = this->root->right->right_score +
                                              this->root->right->left_score +
                                              this->root->right->info.getScore();
                    this->root->right_childs = this->root->right->right_childs +
                                               this->root->right->left_childs + 1;
                }
            }
        }
    }

    /*
     * As described in the pdf, takes a tree and splits it into two trees.
     * "this" tree is getting emptied as it moves all it's elements to the
     * other two trees.
     * O(1) because it takes only 4 commands to finish this function.
     */
    void Split(LvlNode pivot, Ranked_Tree &lesser, Ranked_Tree &bigger) {
        this->Find(pivot); //works.
        lesser.root = this->root;

        //set the lesser tree properly.
        this->root->right_score = 0;
        this->root->right_childs = 0;

        bigger.root = this->root->right;
        this->root->right = NULL;
        this->root = NULL; //this func turns this tree into an empty tree.
    }

public:
    Ranked_Tree() : root(NULL), count(0) {}; //constructor
    Ranked_Tree(const Ranked_Tree &origin) { //copy const of the tree.
        if (origin.root == NULL) {
            this->root = NULL;
        } else {
            this->root = new Node(*(origin.root));
        }
        this->count = origin.count;
    }

    ~Ranked_Tree() { //destructor, sets the root to NULL after taking out all the
        //Nodes out.
        delete this->root;
        this->root = NULL;
    }

    /*
     * using the Find function to find the needed Node then gives out
     * info inside the node as a pointer, (logn)
     */
    LvlNode *Get(LvlNode &key) {
        if (Find(key) == NULL) {
            return NULL;
        }
        return &this->Find(key)->info;
    }

    /*
     * checks if the tree is empty
     */
    bool isempty() {
        if (this->root == NULL) {
            return true;
        } else {
            return false;
        }
    }

    /*
     * Using findMin to give out the data in the min node.
     */
    LvlNode &getMin() {
        return this->FindMin()->info;
    }

    /*
     * Using findMax to give out the data in the max node.
     */
    LvlNode &getMax() {
        return this->FindMax()->info;
    }

    /*
     * As describes in the PDF:
     * Inserts a new element to the tree, splits the trees around that node
     * logn, makes that T value into a node and put it as a root.
     * Then goes on as joining the trees back together.
     */
    void Insert(LvlNode& value) {

        count++; //increase counts of the elements in the tree.

        if (this->root == NULL) {
            this->root = new Node(value);
            return;
        }
        Ranked_Tree lesser;
        Ranked_Tree bigger;

        this->Split(value, lesser, bigger);
        this->Join(lesser, bigger);

        Node *save = this->root;
        this->root = new Node(value);
        if (value > save->info) {
            this->root->left = save;
            this->root->right = save->right;
            save->right = NULL;

            save->right_childs = 0;
            save->right_score = 0;

        } else {
            this->root->right = save;
            this->root->left = save->left;
            save->left = NULL;

            save->left_childs = 0;
            save->left_score = 0;
        }

        if(this->root->right){
            this->root->right_score = this->root->right->right_score +
                                        this->root->right->left_score +
                                        this->root->right->info.getScore();
            this->root->right_childs = this->root->right->right_childs +
                                      this->root->right->left_childs + 1;
        }
        if(this->root->left){
            this->root->left_score = this->root->left->right_score +
                                      this->root->left->left_score +
                                      this->root->left->info.getScore();
            this->root->left_childs = this->root->left->right_childs +
                                       this->root->left->left_childs + 1;
        }

    }

    //the one that actually calculates all the shit yo

    int getScore_aux(Node* node, int num){
        Node* cur_node = node;
        if(node == NULL){
            return 0;
        }
        int node_glads = cur_node->right_childs + 1;

        if(node_glads == num){
            return (cur_node->right_score) + cur_node->info.getScore();
        }
            //go left
        else if(node_glads < num){
            return node->info.getScore() + node->right_score +
                    getScore_aux(cur_node->left, num - node_glads);
        }

            //go right
        else if(node_glads > num){
            return getScore_aux(cur_node->right, num);
        }
        //shouldn't reach here.
        return 0;
    }

    int getScore(int num){
        return getScore_aux(this->root, num);
    }

    int getCount(){
        return this->count;
    }

};
#endif //RANKED_SPLAY_TREE_H