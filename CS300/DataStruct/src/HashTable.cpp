//============================================================================
// Name        : HashTable.cpp
// Author      : John Watson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansnode-style
//============================================================================
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include <unordered_set>

#include "../include/HashTable.hpp"
#include "../include/CSVparser.hpp"
#include "../include/Utility.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// forward declarations
double strToDouble(string str, char ch);


//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */

/**
 * Default constructor
 */
HashTable::HashTable() {
    nodes.resize(tableSize);
    // Initalize node structure by resizing tableSize
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // assigns the tablesize to the argument value
    this->tableSize = size;
    // Resizes the vector length
    nodes.resize(size);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // erase nodes beginning
    nodes.erase(nodes.begin());

}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // return key tableSize
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {

    // Create the key for the bid by converting ascii to integer
    unsigned key = hash(atoi(bid.bidId.c_str()));
    // retrieve node using key
    Node* node = (nodes.at(key));
    // if no entry found for the key
    if(node == nullptr) {
        // assign this node to the key position
        Node* newNode = new Node(bid, key);
        nodes.at(key) = newNode; 

    }
    // else if node is not used
    else if(node->key == UINT_MAX) {
        // assing old node key to key, set old bid to bid and old node next to null pointer
        node->key = key;
        node->bid = bid;
        node->next = nullptr;
    }
    // else find the next open node
    else{
        while(node->next != nullptr) {
            //Itterates untill next node is empty
            node = node->next;
        }
        // add new newNode to end
        node->next = new Node(bid, key);
    }
    
            
}


void HashTable::PrintAll() {
    std::unordered_set<unsigned int> printedKeys;  // To track printed keys

    // Iterate through the nodes
    for (const auto& nodePtr : nodes) {
        if (nodePtr != nullptr) {
            Node* node = nodePtr;  // Dereference the pointer to get the actual Node
            
            // Traverse the linked list starting from the current node
            while (node != nullptr) {
                // Print the node's details if the key is valid
                if (node->key != UINT_MAX) {
                    // Print the key only if it hasn't been printed before
                    if (printedKeys.find(node->key) == printedKeys.end()) {
                        std::cout << "Key " << node->key << ": " << node->bid.bidId << " | " << node->bid.title << " | "
                                  << node->bid.amount << " | " << node->bid.fund << std::endl;

                        printedKeys.insert(node->key);  // Mark this key as printed
                    } else {
                        // For subsequent nodes with the same key, print the details without repeating the key
                        std::cout << "\t " << node->bid.bidId << " | " << node->bid.title << " | "
                                  << node->bid.amount << " | " << node->bid.fund << std::endl;
                    }
                }
                // Move to the next node in the linked list
                node = node->next;
            }
        }
    }
}

/**
 * Print all bids
 */
// void HashTable::PrintAll() {
//     // for node begin to end iterate
//     for (auto i = nodes.begin(); i < nodes.end(); i++) {
//         if(*i != nullptr){
//             Node* node = *i;
//             //  if key not equal to UINT_MAX;
//             if(node->key != UINT_MAX) {
//                 // output key, bidID, title, amount and fund
//                 cout << "Key " << node->key << ": " << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
//             }
//             // node is equal to next item
//             Node* nextNode = node->next;
//             // while node not equal to nullptr
//             while(nextNode != nullptr) {
//                 // output key, bidID, title, amount and fund
//                 cout << "    " << node->key << ": " << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
//                 // node is equal to next node
//                 nextNode = nextNode->next;
//             }
//         }
//     }
         


// }

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // set key equal to hash atoi bidID cstring
    unsigned key = hash(atoi(bidId.c_str()));
    //creates new node pointer to the key location
    Node* node = (nodes.at(key));


    //if key has data
    if(node != nullptr && node->key != UINT_MAX) {

        std::cout << "HEAD: " << node->bid.bidId << std::endl;
        //if first element
        if(node->bid.bidId == bidId) {
            //create temp pointer for current node
            Node* temp = node;
            //set node to next value
            if(node->next == nullptr) {
                nodes[key] = new Node();
            } else {
                nodes[key] = node->next;
            }
            //unallocate the memory held in temp
            delete (temp);
            return;
        } 
        //if not first

        
        //create previous node pointer
        Node* prev = node;
        //set the node pointer to the next node
        node = node->next;
        //while node pointer is not null
        while(node != nullptr) {
            //if node's bid id is same as args
            if(node->bid.bidId == bidId) {
                //unlink node pointer
                if(node->next == nullptr) {
                    prev->next = new Node();
                } else {
                    prev->next = node->next;
                }
                //unallocate memory held by node
                delete node;
                return;
            }
            //otherwise increment both the previous and node pointers
            prev = node;
            if(node->next == nullptr) {
                return;
            } else {
                node = node->next;
            }
        }
        
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;


    // create the key for the given bid
    unsigned key = hash(atoi(bidId.c_str()));
    // if entry found for the key
    Node* node = (nodes.at(key));
    if(node != nullptr && node->bid.bidId.compare(bidId) == 0) {
         //return node bid
        return node->bid;
    }
    // if no entry found for the key
    if(node == nullptr || node->key == UINT_MAX) {
      // return bid
        return bid;
    }
    //while a node exists
    while(node != nullptr) {
        //if the bidId equals args
        if(node->bid.bidId.compare(bidId) == 0) {
            //return the node
            return node->bid;
        }
        //else iterate through list
        node = node->next;
    }



    // while node not equal to nullptr
        // if the current node matches, return it
        //node is equal to next node

    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void HashTable::loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = Utility::strToDouble(file[i][4], '$');


            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}


/**
 * The one and only main() method
 */
void HashTable::runner(std::string path) {

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();
    
    int choice;
    do {
        choice = Utility::menuSelection();

        switch (choice) {

        case 1:{
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(path, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            cin.get();
            
            break;
            }
        case 2: {
            bidTable->PrintAll();
            break;
            }

        case 3: {

            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                Utility::displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
            }
        case 4:
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;
            bidTable->Remove(bidKey);
            break;
        }
    } while (choice != 9);

    cout << "Good bye." << endl;

}


/* TO-DO */

/*
* 4. seperates the clock from main function
* DEFENSIVE PROGRAMMING
* 12. desctructor only removes head
*/