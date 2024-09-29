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
#include <utility>
#include <vector>

#include "../include/HashTable.hpp"
#include "../include/CSVparser.hpp"
#include "../include/Utility.hpp"


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
    this->tableSize = size;
    nodes.resize(size);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
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
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {

    //Hash a key for entry
    unsigned key = hash(atoi(bid.bidId.c_str()));
    //Retrieve the index node
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
            Node* node = nodePtr;
            
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
                node = node->next;
            }
        }
    }
}


//============================================================================
// Merge-Sort Functions
//============================================================================
void HashTable::merge(Node** array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Node** leftArray = new Node*[n1];
    Node** rightArray = new Node*[n2];

    for (int i = 0; i < n1; i++) {
        leftArray[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if(leftArray[i]->bid.bidId < rightArray[j]->bid.bidId) {
            array[k++] = leftArray[i++];
        } else {
            array[k++] = rightArray[j++];
        }
    }

    while (i < n1) {
        array[k++] = leftArray[i++];
    }

    while (j < n2) {
        array[k++] = rightArray[j++];
    }

    delete[] leftArray;
    delete[] rightArray;

}

void HashTable::mergeSort(Node** array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}
//============================================================================
// Heap-Sort Functions
//============================================================================

void HashTable::heapify(Node** array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && array[left]->bid.bidId > array[largest]->bid.bidId) {
        largest = left;
    }
    
    if(right < n && array[right]->bid.bidId > array[largest]->bid.bidId) {
        largest = right;
    }

    if (largest != i) {
        swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

void HashTable::heapSort(Node** array, int n) {
    for(int i = n/2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    for(int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }

}
//============================================================================
// Quick-Sort Functions
//============================================================================
int HashTable::partition(Node** array, int low, int high) {
    Bid pivot = array[high]->bid;
    int i = (low - 1);

    for(int j = low; j < high; j++) {
        if(array[j]->bid.bidId < pivot.bidId) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return (i + 1);
}

void HashTable::quickSort(Node** array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

//============================================================================
// Sorting Runner
//============================================================================
void HashTable::sortAllBids(HashTable* bidTable, int selection) {
    for(auto& nodePtr : bidTable->nodes) {
        if(nodePtr != nullptr) {
            std::vector<Node*> nodeList;
            Node* node = nodePtr;



            while(node != nullptr) {
                nodeList.push_back(node);
                node = node->next;
            }

            switch(selection) {
                case 1:
                    mergeSort(nodeList.data(), 0, nodeList.size() - 1);
                    break;
                case 2:
                    heapSort(nodeList.data(), nodeList.size());
                    break;
                case 3:
                    quickSort(nodeList.data(), 0, nodeList.size() - 1);
                    break;
            }

            for(size_t i = 0; i < nodeList.size() - 1; i++) {
                nodeList[i]->next = nodeList[i + 1];
            }
            nodeList.back()->next = nullptr;
            bidTable->nodes[hash(atoi(nodeList[0]->bid.bidId.c_str()))] = nodeList[0];
        }


    }
}
         


// }

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // Hash the input number
    unsigned key = hash(atoi(bidId.c_str()));
    // Retrieve the index node
    Node* node = (nodes.at(key));


    //if key has data
    if(node != nullptr && node->key != UINT_MAX) {

        //if first element
        if(node->bid.bidId == bidId) {
            Node* temp = node;

            //set node to next value
            if(node->next == nullptr) {
                nodes[key] = new Node();
            } else {
                nodes[key] = node->next;
            }

            delete (temp);
            return;
        } 


        //if not first
        Node* prev = node;
        node = node->next;

        //while node pointer is not null
        while(node != nullptr) {
            // If found match
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
    Node* node = (nodes.at(key));

    // if entry found for the key
    if(node != nullptr && node->bid.bidId.compare(bidId) == 0) {

        return node->bid;
    }
    // if no entry found for the key
    if(node == nullptr || node->key == UINT_MAX) {
        return bid;
    }
    //while a node exists
    while(node != nullptr) {
        //if the bidId equals args
        if(node->bid.bidId.compare(bidId) == 0) {
            return node->bid;
        }
        node = node->next;
    }
    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void HashTable::loadBids(string csvPath, HashTable* hashTable) {
    std::cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        std::cout << c << " | ";
    }
    std::cout << "" << endl;

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


void HashTable::runner(std::string path) {

    //Declare variables
    clock_t ticks;
    HashTable* bidTable;
    Bid bid;
    int choice;

    bidTable = new HashTable();
    
    do {
        //Ask for use input
        choice = Utility::menuSelection();
        Utility::clearTerm();

        switch (choice) {
        //Load bids
        case 1:{
            
            // Initialize a timer
            ticks = clock();

            loadBids(path, bidTable);

            // Calculate elapsed time 
            ticks = clock() - ticks; 
            std::cout << "time: " << ticks << " clock ticks" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;
            cin.get();
            
            break;
            }
        //Print All
        case 2: {
            bidTable->PrintAll();
            break;
            }
        //Sort
        case 3: {
            //Ask to select an Algorithm
            int selection = Utility::sortingSelection();
            Utility::clearTerm();

            // Initialize a timer
            ticks = clock();
            sortAllBids(bidTable, selection);

            // Calculate elapsed time 
            ticks = clock() - ticks;
            std::cout << "time: " << ticks << " clock ticks" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;
            break;
        }
        //Find Bid
        case 4: {
            //Ask the user for a BidId
            std::string bidKey;
            std::cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            // Initialize a timer
            ticks = clock();

            bid = bidTable->Search(bidKey);

            // Print the bid
            if (!bid.bidId.empty()) {
                Utility::displayBid(bid);
            } else {
                std::cout << "Bid Id " << bidKey << " not found." << endl;
            }

            // Calculate elapsed time 
            ticks = clock() - ticks;
            std::cout << "time: " << ticks << " clock ticks" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;
            break;
            }
        //Remove Bid
        case 5:
            //Ask the user for BidId
            std::string bidKey;
            std::cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            bidTable->Remove(bidKey);
            break;
        }
        
    } while (choice != 0);

}