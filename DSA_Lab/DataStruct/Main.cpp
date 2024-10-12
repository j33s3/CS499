#include <iostream>
#include <climits>
#include <cstdlib>

#include "include/LinkedList.hpp"
#include "include/HashTable.hpp"
#include "include/BinarySearchTree.hpp"
#include "include/Vector.hpp"

#include "include/Utility.hpp"


// This stored the string for the initial menu screen
std::string menu =  "Select a Datastructure\n"
                    "===================\n"
                    "* Change File - 1 *\n"
                    "* Vector      - 2 *\n"
                    "* Linked List - 3 *\n"
                    "* Hash Table  - 4 *\n"
                    "* BST         - 5 *\n"
                    "* exit        - 0 *\n"
                    "===================\n"
                    "Select a number: ";

// This stores the selection screen for choosing a data file
std::string fileSelect = "Select a Data File\n"
                         "======================\n"
                         "Monthly Sales 2016 - 1\n"
                         "Monthly Sales      - 2\n"
                         "======================\n"
                         "Select a File: ";








/**
 * This is the main function for the DataStruct program
 * The main function handles our initial object calls
 * It also handles selecting data files to work with.
 */
int main() {
    // Default File path
    std::string csvPath = "../data/eBid_Monthly_Sales_Dec_2016.csv";

    // Used to hold menu selection
    int dataStruct;

    do{
        // Prints the menu then clears the terminal
        Utility::clearTerm();
        std::cout << menu;
        std::cin >> dataStruct;
        Utility::clearTerm();

        switch(dataStruct) {
            // Change File
            case 1: {
                // Ask the user for data file
                int selection;
                cout << fileSelect;
                cin >> selection;

                //change the path
                switch(selection) {
                    case 1:
                        csvPath = "../data/eBid_Monthly_Sales_Dec_2016.csv";
                        break;
                    case 2:
                        csvPath = "../data/eBid_Monthly_Sales.csv";
                        break;
                }
                
                Utility::clearTerm();
                break;
            }
            // Vector
            case 2: {
                Vector vec;
                vec.runner(csvPath);
                break;
            }
            // LinkedList
            case 3: {
                LinkedList list;
                list.runner(csvPath);
                break;
            }
            //HashTable
            case 4: {
                HashTable table;
                table.runner(csvPath);
                break;
            }
            //BST
            case 5: {
                BinarySearchTree tree;
                tree.runner(csvPath);
                break;
            }
            //exit
            case 0: {
                break;
            }
            //Invalid input
            default: {
                std::cout << "Please enter a valid selection...";
                std::cin.get();
                break;
            }

        };

    } while(dataStruct != 0);

    std::cout << "exiting..." << endl;
    



    return 0;
}   
