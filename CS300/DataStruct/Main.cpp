#include <iostream>
#include <climits>
#include <cstdlib>

#include "include/LinkedList.hpp"
#include "include/HashTable.hpp"
#include "include/BinarySearchTree.hpp"
#include "include/Vector.hpp"

#include "include/Utility.hpp"



std::string menu =  "Select a Datastructure\n"
                    "----------------------\n"
                    "* Change File - 1 *\n"
                    "* Vector      - 2 *\n"
                    "* Linked List - 3 *\n"
                    "* Hash Table  - 4 *\n"
                    "* BST         - 5 *\n"
                    "* exit        - 0 *\n"
                    "-------------------\n"
                    "Select a number: ";

std::string fileSelect = "Select a Data File\n"
                         "======================\n"
                         "Monthly Sales 2016 - 1\n"
                         "Monthly Sales      - 2\n"
                         "======================\n"
                         "Select a File: ";









int main() {

    // process command line arguments
    std::string csvPath = "../data/eBid_Monthly_Sales_Dec_2016.csv";


    int dataStruct;
    int algorithm;

    do{
        Utility::clearTerm();

        std::cout << menu;
        std::cin >> dataStruct;
        Utility::clearTerm();

        switch(dataStruct) { //ADD a BACK FUNCTION????
            case 1: {
                int selection;
                cout << fileSelect;
                cin >> selection;
                switch(selection) {
                    case 1:
                        csvPath = "../data/eBid_Monthly_Sales_Dec_2016.csv";
                        break;
                    case 2:
                        csvPath = "../data/eBid_Monthly_Sales.csv";
                        break;
                }
            }
            case 2: {
                Vector vec;
                vec.runner(csvPath);
                break;
            }
            case 3: {
                LinkedList list;
                list.runner(csvPath);
                break;
            }
            case 4: {
                HashTable table;
                table.runner(csvPath);
                break;
            }
            case 5: {
                BinarySearchTree tree;
                tree.runner(csvPath);
                break;
            }
            case 0: {
                break;
            }
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
