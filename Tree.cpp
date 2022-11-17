//
// Created by Milena Petrovic on 9/24/22.
//
#include <iostream>
#include "Tree.h"
#include <vector>
#include <regex>
using namespace std;

//helper function for AVL Tree destructor
void Tree::destroy(Tree::Node* root){
    if(root == nullptr) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}
//destructor
Tree::~Tree(){
    destroy(this->root);
}

//recursively checks where to insert new node, once inserted, updates height, checks for balance, and rotates where unbalanced
Tree::Node* Tree::HelpInsert(Tree::Node* root,long int id, string name){
    if(root == nullptr) {
        cout << "successful" << endl;
        root = new Node(id, name);
        return root;
    }
    else if(id < root->ID){
        root->left = HelpInsert(root->left, id, name);
    }
    else if(id > root->ID){
        root->right = HelpInsert(root->right, id, name);
    }
    else if(id == root->ID){
        cout << "unsuccessful" << endl;
        return root;
    }
    if(HelpBalance(root) == -2){
        if(HelpBalance(root->right) == 1){  //RL unbalance && root->ID < root->right->ID >0
            root = rotateRL(root);
        }else if (HelpBalance(root->right) == -1){
            root = rotateLeft(root);    //RR unbalance
        }
    }else if(HelpBalance(root) == 2){
        if(HelpBalance(root->left) == -1){ //&& root->ID > root->left->ID <0
            root = rotateLR(root);      //LR unbalance
        }else if (HelpBalance(root->left) == 1){
            root = rotateRight(root);   //LL unbalance
        }
    }
    /*else if(id != root->ID) {
        if(id < root->ID) {
            root->left = HelpInsert(root->left, id, name);
        }else if (id > root->ID){
            root->right = HelpInsert(root->right, id, name);
        }

        //checks balance factor
        if(HelpBalance(root) == -2){
            if(HelpBalance(root->right) == 1){  //RL unbalance && root->ID < root->right->ID >0
                root = rotateRL(root);
            }else if (HelpBalance(root->right) == -1){
                root = rotateLeft(root);    //RR unbalance
            }
        }else if(HelpBalance(root) == 2){
            if(HelpBalance(root->left) == -1){ //&& root->ID > root->left->ID <0
                root = rotateLR(root);      //LR unbalance
            }else if (HelpBalance(root->left) == 1){
                root = rotateRight(root);   //LL unbalance
            }
        }
    }else{
        cout << "unsuccessful" << endl;
    }*/
    return root;
}

//next three functions order list of names in a reference to a vector recursively
void Tree::HelpInorder(Tree::Node* root, vector<Tree::Node*>& ret){
    if(root == nullptr){
        return;
    }else{
        HelpInorder(root->left,ret);
        ret.push_back(root);
        HelpInorder(root->right, ret);
    }
}

void Tree::HelpPreorder(Tree::Node *root, vector<Tree::Node*>& ret) {
    if(root == nullptr) {
        return;
    }else {
        ret.push_back(root);
        HelpPreorder(root->left, ret);
        HelpPreorder(root->right, ret);
    }
}

void Tree::HelpPostorder(Tree::Node *root, vector<Tree::Node*>& ret) {
    if(root == nullptr){
        return;
    }else{
        HelpPostorder(root->left, ret);
        HelpPostorder(root->right, ret);
        ret.push_back(root);
    }
}

//regex and HelpInsert used to return whether object was inserted successfully
void Tree::insert(basic_string<char, char_traits<char>, allocator<char>> id, string &name) {
    //using regex to parse input and check validity
    auto stringCheck = regex("[a-zA-Z ]+");  //for checking whether is string and/or space, differentiates capitalization
    auto digCheck = regex("[0-9]{8}");       //for checking whether is a digit and whether digit is 8 characters

    if(!regex_match(name, stringCheck)){
        cout << "unsuccessful" << endl;
        return;
    }
    if(!regex_match(id, digCheck)){
        cout << "unsuccessful" << endl;
        return;
    }
    this->root = HelpInsert(this->root, stoi(id), name);
}

//next 3 functions return vector for test.cpp & for printing iterations
vector<Tree::Node*> Tree::inorder(){
    vector<Tree::Node*> ret;
    HelpInorder(this->root, ret);
    return ret;
}

vector<Tree::Node*> Tree::preorder() {
    vector<Tree::Node*> ret;
    HelpPreorder(this->root, ret);
    return ret;
}

vector<Tree::Node*> Tree::postorder() {
    vector<Tree::Node*> ret;
    HelpPostorder(this->root, ret);
    return ret;
}

//printing
void Tree::printInorder(){
    vector<Tree::Node*> in = inorder();
    int cnt = 0;
    for(auto i: in) {
        cout << i->student;
        cnt++;
        if(cnt != in.size()){
            cout << ", ";
        }
    }
    cout << endl;
};

void Tree::printPreorder(){
    vector<Tree::Node*> pin = preorder();
    int cnt = 0;
    for(auto i: pin){
        cout << i->student;
        cnt++;
        if(cnt != pin.size()){
            cout << ", ";
        }
    }
    cout << endl;
}

void Tree::printPostorder(){
    vector<Tree::Node*> in = postorder();
    int cnt = 0;
    for(auto i: in){
        cout << i->student;
        cnt++;
        if(cnt != in.size()){
            cout << ", ";
        }
    }
    cout << endl;
}

void Tree::printLvl() {
    cout << getHeight(this->root) << endl;
}

//height and balancing
long int Tree::getHeight(Tree::Node *root) {
    if(root == nullptr)
        return 0;
    return root->height;
}

int Tree::Height(Tree::Node* root){
    if(root == nullptr){
        return 0;
    }
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int Tree::HelpBalance(Tree::Node *root){
    if(root == nullptr)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

//rotations
Tree::Node *Tree::rotateRight(Tree::Node *node) {
    Node* lChild = node->left;
    node->left = lChild->right;
    lChild->right = node;
    root->height = Height(root);   //updates height in ll & RL & LR
    return lChild;
}

Tree::Node *Tree::rotateLeft(Tree::Node *node) {
    Node* rChild = node->right;
    node->right = rChild->left;
    rChild->left = node;
    root->height = Height(root);    //updates height in RR & RL & LR
    return rChild;
}

Tree::Node *Tree::rotateRL(Tree::Node *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Tree::Node *Tree::rotateLR(Tree::Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

//searching
string Tree::searchID(long int id, bool &success) {
    vector<Tree::Node*> IDs = inorder();    //list referenced
    for(auto i: IDs){
        if(i->ID == id){
            success = true;
            return i->student;    //returns name at ID
        }
    }
    return "";
}

//void return for cases where the same name applies to more than one ID
void Tree::searchName(string name, bool &success) {
    vector<Tree::Node*> names = preorder();
    vector<long int> ret;
    for(auto i: names){
        if(i->student == name){
            success = true;
            ret.push_back(i->ID);
        }
    }
    for(long int i : ret){
        cout << i << endl;     //prints ID/ID's
    }
}

void Tree::search(string inp){
    bool success = false;
    auto stringCheck = regex("[a-zA-Z \"]+");  //checks for capitalization, spaces, and quotes
    auto digCheck = regex("[0-9]{8}");

    if(regex_match(inp, stringCheck)){
        inp = inp.substr(1, inp.length()-2);   //w/o quotation
        searchName(inp,success);
    }
    if(regex_match(inp, digCheck)){
        cout << searchID(stoi(inp), success) << endl;
    }

    if(!success) {
        cout << "unsuccessful" << endl;
    }
}

//removals
void Tree::remove(string &id) {
    bool success = false;
    auto digCheck = regex("[0-9]{8}");

    if(regex_match(id, digCheck)){
        deleteNode(stoi(id), this->root, success);
    }
    if(!success){
        cout << "unsuccessful" << endl;
    }else{
        cout << "successful" << endl;
    }
}

//takes in a position of the list and removes node at that position if it exists
void Tree::removeInorder(long int N) {
    vector<Tree::Node*> in = inorder();
    Node* curr;
    string inp;
    if(N >= in.size()){
        cout << "unsuccessful" << endl;
        return;
    }
    for(int i = 0; i < in.size();i++){
        if(i == N){
            curr = in.at(N);
            inp = to_string(curr->ID);
            remove(inp);
        }
    }
}

//finds node to be deleted, deletes node, and updates success boolean
 Tree::Node* Tree::deleteNode(long int id, Tree::Node* &root, bool &success){
    Node* temp = nullptr;  //to be deleted
    if(root == nullptr){
        return nullptr;
    }
    if(id == root->ID){
        success = true;
        if(root->right != nullptr){   //right child exists
            //prioritizing find inorder successor
            temp = root->right;
            while(temp->left){
                temp = temp->left;
            }
            //change values in node
            root->ID = temp->ID;
            root->student = temp->student;
            root->right = deleteNode(temp->ID, root->right, success);
        }else if(root->left != nullptr){
            //left child exists, replace
            root = root->left;
            root->left = nullptr;
            return root;
            //return root->left;
        }else{
            root->left = nullptr;
            root->right = nullptr;
            root = nullptr;
            return nullptr;
        }
    //recursive calls to find node
    }else if(id < root->ID){
        root->left = deleteNode(id, root->left, success);
    }else if(id > root->ID){
        root->right = deleteNode(id, root->right, success);
    }
    //updates height
    root->height = Height(root);
    return root;
}







