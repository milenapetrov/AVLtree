//
// Created by Milena Petrovic on 9/24/22.
//
#include <iostream>
#include <vector>
using namespace std;

#ifndef AVL_TREE_H
#define AVL_TREE_H

class Tree {
private:
    struct Node{
        long int ID;
        int height;
        string student;
        Node* left;
        Node* right;
        Node(){
            ID = 0;
            student = "";
            left = nullptr;
            right = nullptr;
            height = 0;
        };
        Node(long int ID, string name){
            student = name;
            this->ID = ID;
            left = nullptr;
            right = nullptr;
            height = 1;
        };
    };
    Node* root = nullptr;
    void destroy(Tree::Node* root);
    Tree::Node* HelpInsert(Node* root, long int id, string name);
    static long int getHeight(Node* root);
    static int Height(Node* root);
    int HelpBalance(Node* root);
    void HelpInorder(Node* root, vector<Tree::Node*>& ret);
    void HelpPreorder(Node* root, vector<Tree::Node*>& ret);
    void HelpPostorder(Node* root, vector<Tree::Node*>& ret);
    vector<Tree::Node*> inorder();
    vector<Tree::Node*> preorder();
    vector<Tree::Node*> postorder();
    Tree::Node* rotateRight(Node* node);
    Tree::Node* rotateLeft(Node* node);
    Tree::Node* rotateRL(Node* node);
    Tree::Node* rotateLR(Node* node);
    Tree::Node* deleteNode(long int id, Tree::Node* &root, bool &success);
public:
    Tree(){
        this->root = nullptr;
    };
    ~Tree();
    void printInorder();
    void printPreorder();
    void printPostorder();
    void insert(basic_string<char, char_traits<char>, allocator<char>> id, string &name);
    string searchID(long int id, bool &success);
    void searchName(string name, bool &success);
    void search(string inp);
    void remove(string &id);
    void removeInorder(long int N);
    void printLvl();


};


#endif //AVL_TREE_H
