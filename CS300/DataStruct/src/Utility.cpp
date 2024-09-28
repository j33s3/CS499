#include "../include/Utility.hpp"
#include <algorithm>
#include <iostream>
#include <cstdlib>

namespace Utility {
    
    double strToDouble(std::string str, char ch) {
        str.erase(remove(str.begin(), str.end(), ch), str.end());
        return atof(str.c_str()); // Convert the modified string to a double
    }
    
    void displayBid(Bid bid) {
        std::cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
                << bid.fund << std::endl;
        return;
    }

    int menuSelection() {
        int input;
        do {
            cout << "Please select an option:\n"
                    "------------------------\n"
                    "* Load Bids        - 1 *\n"
                    "* Display All Bids - 2 *\n"
                    "* Sort Data        - 3 *\n"
                    "* Find Bid         - 4 *\n"
                    "* Remove Bid       - 5 *\n"
                    "* Exit             - 0 *\n"
                    "------------------------\n"
                    "Enter a number: ";
            std::cin >> input;

            if(input >= 0 && input <= 5) {
                break;
            }
            std::cout << "Please enter a Valid Number...";
            std::cin.get();
            
        } while(true);
        return input;
    }

    int sortingSelection() {
        int input;
        do {
            std::cout << "Select an Algorithm\n"
                         "-------------------\n"
                         "* Merge Sort - 1 *\n"
                         "* Heap Sort  - 2 *\n"
                         "* Quick Sort - 3 *\n"
                         "------------------\n"
                         "Select an option: ";
            std::cin >> input;

            if(input >=1 || input <=3) {
                break;
            }
            std::cout << "Please enter a Valid Number...";
            std::cin.get();    
        } while (true);

        return input;
    }




    void clearTerm() {
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}

    
}