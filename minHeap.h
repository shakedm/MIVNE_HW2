#ifndef MIVNE_WET2_MINHEAP_H
#define MIVNE_WET2_MINHEAP_H

#include <malloc.h>



class minHeap {
public:
    class Node {
    public:


        int index;
        int groupID;

        Node *left;
        Node *right;
        Node *dad;

        //constructor
        Node(int ID, int index) : index(index), groupID(ID), left(NULL), right(NULL), dad(NULL) {};
        //copy~c'tor
        Node(const Node &node) : index(node.index),groupID(node.groupID) {
            if (node.left != NULL) {
                this->left = new Node(*(node.left));
            }
            if (node.right != NULL) {
                this->right = new Node(*(node.right));
            }
            if (node.dad != NULL){
                this->dad = new Node(*(node.dad));
            }
        };
        //destructor
        ~Node() {
            delete (this->right);
            this->right = NULL;
            delete (this->left);
            this->left = NULL;
            this->dad = NULL;
        };
    };

private:
    Node* root; //head of tree
    int numOfGroups;

    void FillArray(Node** array, int index,Node* curr){
        if (index > numOfGroups)
            return;
        array[index-1]=curr;
        FillArray(array,2*index,curr->left);
        FillArray(array,2*index+1,curr->right);
    }

    Node* getGroupByIndex(int index){
        //makes bolean array that represent the binary of the index
        //then get to the node by going through the array
        if (index > numOfGroups)
            return NULL;
        if(index <= 0)
            return NULL;

        if (index==1)
            return root;
        int numOfBit=0;
        int tmp= index;
        while (tmp!= 0){
            numOfBit++;
            tmp/=2;
        }
        bool array[numOfBit];
        for (int i = numOfBit; i >0 ; --i) {
            if (index % 2 == 0){
                array[i-1]= false;
            }
            else{
                array[i-1]=true;
            }
            index= index/2;
        }
        Node* curr= root;
        for (int j= 1 ; j< numOfBit ; j++){
            if (array[j]){
                curr= curr->right;
            } else{
                curr= curr->left;
            }
        }
        return curr;

    }
    void SiftTree(Node* node){
        if (node == NULL)
            return;
        if(node->left==NULL && node->right==NULL )
            return;

        SiftTree(node->right);
        SiftTree(node->left);
        SiftDown(node);
    }
    static void switch_IsLeft(Node* n1, Node* d2){
        Node* tmp_right= d2->right;
        Node* tmp_dad= d2->dad;

        d2->left =n1->left;
        if(d2->left != NULL)
            d2->left->dad= d2;

        n1->left= d2;
        d2->dad=n1;
        n1->dad=tmp_dad;
        if(n1->dad != NULL){
            if(n1->dad->left == d2){
                n1->dad->left= n1;
            }else{
                n1->dad->right= n1;
            }
        }
        d2->right =n1->right;
        if(d2->right!= NULL){
            d2->right->dad= d2;
        }
        n1->right= tmp_right;
        if (n1->right != NULL){
            n1->right->dad =n1;
        }
        int tmp_index= d2->index;
        d2->index=n1->index;
        n1->index=tmp_index;
    }
    static void switch_IsRight(Node* n1, Node* d2){
        Node* tmp_left= d2->left;
        Node* tmp_dad = d2->dad;

        d2->right = n1->right;
        if(d2->right != NULL)
            d2->right->dad=d2;

        n1->right= d2;
        d2->dad= n1;
        n1->dad= tmp_dad;
        if(n1->dad != NULL){
            if(n1->dad->left == d2){
                n1->dad->left= n1;
            }else{
                n1->dad->right= n1;
            }
        }

        d2->left = n1->left;
        if(d2->left != NULL)
            d2->left->dad= d2;

        n1->left = tmp_left;
        if (n1->left != NULL)
            n1->left->dad = n1;

        int tmp_index= d2->index;
        d2->index=n1->index;
        n1->index=tmp_index;
    }

    //in case d2 is the dad of n1 calling the above function by switching d2 ,n1
    //in function call
    static void switch_IsDad(Node* n1, Node* d2){
        if(n1->right==d2){
            switch_IsRight(d2,n1);
            return;
        } else{
            switch_IsLeft(d2,n1);
            return;
        }
    }
    //O(1) all is pointer game
    static void switch_nodes(Node* n1 , Node* d2){
        if(d2->left==n1 ) {
            switch_IsLeft(n1, d2);
            return;
        }
        if(d2->right==n1){
            switch_IsRight(n1,d2);
            return;
        }
        if(d2->dad==n1){
            switch_IsDad(n1,d2);
            return;
        }
        Node* tmp_right= d2->right; //saving the sons of d2
        Node* tmp_left = d2->left;
        Node* tmp_dad = d2->dad;
        if(n1->dad != NULL){
            if(n1->dad->right == n1){ //n1 is the right son
                n1->dad->right= d2; // updating the father of n1 to save d2

            }
            else{
                //n1 is left son

                n1->dad->left = d2;
            }
        }
        d2->right=n1->right; //updating the sons of d2
        if(d2->right!= NULL)
            d2->right->dad= d2;//changing the sons father if needed


        d2->left=n1->left;
        if(d2->left != NULL)
            d2->left->dad = d2;

        if(d2->dad != NULL){
            if(d2->dad->right == d2){ //updating the father of d2 to save n1
                d2->dad->right = n1;
            }
            else{
                d2->dad->left = n1;
            }
        }
        n1->right=tmp_right;
        if(n1->right!= NULL)
            n1->right->dad = n1;

        n1->left=tmp_left;
        if(n1->left != NULL)
            n1->left->dad = n1;

        d2->dad = n1->dad;
        n1->dad = tmp_dad;

        //update the indexes
        int tmp_index = n1->index;
        n1->index = d2->index;
        d2->index = tmp_index;

    }

    /*!
     * go to the dad as long as it is not NULL (root) and compare with son
     * switches if needed and called on dad
     * O(h) h being the height of the heap
     * @param node the node that is now checking for
     */
    void  SiftUp(Node* node){
        if(node->dad== NULL){
            root=node;
            return;
        }
        if(node->dad->groupID > node->groupID){
            switch_nodes(node->dad, node);
            SiftUp(node);
        }
    }

/*!
 * O(h) h being the height of the node
 * starts from root and checks for any comparison available with the sons
 * as long as they are not NULL
 * @param node
 */
    void SiftDown(Node* node){
        if(node== NULL)
            return;
        //case leaf
        Node* tmp_root = NULL;
        bool switchRoot=false;
        if(node->left == NULL && node->right==NULL)
            return;

        if(node->right !=NULL ) {
            if (node->left == NULL) {
                //case only one right son
                if (node->right->groupID < node->groupID) {
                    if (node == root) {
                        tmp_root = node->right;
                        switchRoot = true;
                    }
                    switch_nodes(node->right, node);
                    if (switchRoot)
                        root = tmp_root;
                    SiftDown(node);
                }
            }
                //case two sons
            else {
                if (node->right->groupID < node->groupID || node->left->groupID
                                                            < node->groupID) {
                    if (node->right->groupID < node->left->groupID) {
                        if (node == root) {
                            tmp_root = node->right;
                            switchRoot = true;
                        }
                        switch_nodes(node->right, node);
                        if (switchRoot)
                            root = tmp_root;
                        SiftDown(node);
                    } else {
                        if (node == root) {
                            tmp_root = node->left;
                            switchRoot = true;
                        }

                        switch_nodes(node->left, node);
                        if (switchRoot)
                            root = tmp_root;
                        SiftDown(node);
                    }
                }
            }

        } else {
            //case left son only
            if (node->left->groupID < node->groupID) {
                if (node == root) {
                    tmp_root = node->left;
                    switchRoot = true;
                }
                switch_nodes(node->left, node);
                if (switchRoot)
                    root = tmp_root;
                SiftDown(node);
            }
        }
    }
    /*!
     * finds the group number in O(log(index)) index being the num of groups in heap
     * @param index the group that we are searching for
     * @return NULL in case of illegal index, the Node of the group in other case
     */

    Node* makeHeap_aux(int index,int n, int* GroupsID){
        if (n<=0)
            return NULL;
        if (index > n)
            return NULL;
        Node* curr = new Node(GroupsID[index-1],index);
        curr->left = makeHeap_aux(2*index,n,GroupsID);
        curr->right = makeHeap_aux(2*index+1,n,GroupsID);
        if(curr->left != NULL)
            curr->left->dad= curr;
        if(curr->right != NULL)
            curr->right->dad = curr;

        return curr;

    }

public:


    minHeap(int n , int* Ids){
        this->numOfGroups = 0;
        this->root = NULL;
        makeHeap(n,Ids);
    }
    minHeap() : root(NULL), numOfGroups(0){};
    //constructors


    //copy ~ctor
    minHeap(const minHeap& origin) {
        if (origin.root == NULL){
            this->root = NULL;
            this->numOfGroups=0;
        }
        else {
            this->root = new Node(*origin.root);
            this->numOfGroups = origin.numOfGroups;
        }
    }
    //destructor
    ~minHeap(){
        delete this->root;
        this->root= NULL;
    }
    //returns the groupID, could return Node
    int GetMin(){
        return this->root->groupID;
    }


    //
    Node** makeHeap(int n, int* GroupsID){
        this->root = makeHeap_aux(1,n,GroupsID);
        SiftTree(root);
        this->numOfGroups = n;
        Node** array = new Node*[n];
        FillArray(array,1,root);
        return array;
    }


    //inserts a new group to the tree using siftup to correct it
    Node* insert(int GroupID){
        if(root== NULL){
            root= new Node(GroupID,1);
            this->numOfGroups++;
            return root;
        }
        Node* added= new Node(GroupID,numOfGroups+1);
        this->numOfGroups++;
        int father = numOfGroups/2;
        Node* papa = getGroupByIndex(father);
        added->dad=papa;
        if(papa->left== NULL){
            papa->left = added;
            SiftUp(added);
        }
        else{
            papa->right = added;
            SiftUp(added);
        }
        return added;

    }
    /*!
     * uses getGroupByIndex to find the last leaf, O(log(n))
     * then switching it with root deleting the leaf and fixing the heap by SiftDown
     */
    void DelMin(){
        Node* leaf= getGroupByIndex(numOfGroups);
        if (leaf == root){
            delete root;
            root= NULL;
            numOfGroups--;
            return;
        }

        Node* papa = leaf->dad;
        if(papa != root) {
            switch_nodes(leaf, root);

            if (root == papa->right)
                papa->right = NULL;
            else
                papa->left = NULL;

        }
        else{
            switch_nodes(leaf,root);
            if(papa== leaf->left)
                leaf->left= NULL;
            else
                leaf->right=NULL;
        }
        delete root;
        this->root=leaf;
        SiftDown(root);
        numOfGroups--;

    }
    void RemoveNode(Node* node){
        Node* leaf = getGroupByIndex(numOfGroups);
        if (numOfGroups== 1){
            delete node;
            root= NULL;
            numOfGroups--;
            return;
        }
        if(node==root){
            DelMin();
            return;
        }

        if(node!= leaf) {
            Node *papa = leaf->dad;
            switch_nodes(leaf, node);
            if (papa==node)
                papa=node->dad;

            if(papa != NULL) {
                if (node == papa->right)
                    papa->right = NULL;
                else
                    papa->left = NULL;
                node->dad = NULL;
            }
            if (papa->right!=NULL && papa->left == NULL) {
                papa->left = papa->right;
                papa->right = NULL;
            }
            delete node;


            SiftDown(leaf);
        } else{
            Node *papa = leaf->dad;
            if (leaf == papa->right)
                papa->right = NULL;
            else
                papa->left = NULL;
            leaf->dad = NULL;

            delete leaf;
        }
        numOfGroups--;

    }
    int getNumGroups(){
        return numOfGroups;
    }
};




#endif //MIVNE_WET2_MINHEAP_H
