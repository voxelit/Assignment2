/*
    Name: Kaitlyn Corpuz, 5006553690, CS 302 - 1004, Assignment #2
    Description: This program practices rotations with AVL Trees
    Input: defined in main
    Output: data in tree
*/

#include <iostream>
#include "AVL.h"
using namespace std;

int main()
{
    //variables
    AVLTree tree;
    char selection;
    int data = 0;
    
    do
    {
        //print menu
        cout << "AVL Tree Builder\n";
        cout << "*****************\n";
        cout << "[I]nsert node\n";
        cout << "[D]elete node\n";
        cout << "[E]nd program\n";

        //prompt user
        cout << "\nPlease choose an operation: ";
        cin >> selection;

        switch(selection)
        {
            case 'i':
            case 'I':
                cout << "Enter a number to insert into the tree: ";
                cin >> data;
                tree.insertNode(data);
                tree.callPrint();
                cout << endl << endl;
                break;
            case 'd':
            case 'D':
                cout << "Enter a number to remove into the tree: ";
                cin >> data;
                tree.removeNode(data);
                tree.callPrint();
                cout << endl << endl;
                break;
            case 'e':
            case 'E':
                tree.callPrint();
                cout << endl << endl;
                break;
            default:
                cout << "Invalid selection. Please try again";
                cout << endl << endl;
                break;
        }

    } while (selection != 'e' && selection != 'E');
    

    return 0;
}