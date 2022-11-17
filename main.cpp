#include <iostream>
#include <regex>
#include <vector>

#include "Tree.h"
using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/


int main(){ //make more variables to store values that can later output to screen
    Tree AVL;
    long int id;
    string name, ID;


    string line;

    int n = 0;
    string command;

    cin >> n;

    while(n > 0){
        n--;
        cin >> command;
        if(command == "printInorder"){
            AVL.printInorder();
            //continue;
        }
        if(command == "printPostorder"){
            AVL.printPostorder();
            //continue;
        }
        if(command == "printPreorder"){
            AVL.printPreorder();
            //continue;
        }
        if(command == "printLevelCount"){
            AVL.printLvl();
            //continue;
        }
        if(command == "insert"){
            getline(cin, line);
            name = line.substr(2, line.find_last_of('"')-2);  //disregards "'s and space
            ID = line.substr(line.find_last_of('"')+2);
            AVL.insert(ID, name);
            //continue;
        }
        if(command == "search"){
            getline(cin, line);
            line.erase(0,1);  //rid of space
            AVL.search(line);
            //continue;
        }
        if(command == "remove"){
            getline(cin, line);
            line.erase(0,1);  //bye space
            AVL.remove(line);
            //continue;
        }
        if(command == "removeInorder"){
            cin >> id;
            AVL.removeInorder(id);
        }
    }



	return 0;
}

