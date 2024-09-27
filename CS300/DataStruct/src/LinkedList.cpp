//============================================================================
// Name        : LinkedList.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <cstdlib>
#include <iostream>
#include <time.h>

#include "../include/LinkedList.hpp"
#include "../include/CSVparser.hpp"
#include "../include/Utility.hpp"

using namespace std;
//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold bid information


//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */


/**
 * Default constructor
 */
LinkedList::LinkedList() {
    //set head and tail equal to null
    head = nullptr;
    tail = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    //Create new node
    Node* newNode = new Node(bid);
    //if there is nothing at the head...
    if(head == nullptr) {
        // new node becomes the head and the tail
        head = newNode;
        tail = newNode;
    } else { //else 
        // make current tail node point to the new node
        tail->next = newNode;
            // and tail becomes the new node
        tail = newNode;
    }
    //increase size count
    size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // Create new node
    Node* newNode = new Node(bid);
    //if the list is empty
    if(head == nullptr) {
        // new node becomes the head and the tail
        head = newNode;
        tail = newNode;
    } else { // if there is already something at the head...
        // new node points to current head as its next node
        newNode->next = head;
        // head now becomes the new node
        head = newNode;
    }
    //increase size count
    size++;

}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {

    // start at the head
    Node* curNode = head;

    // while loop over each node looking for a match
    while(curNode != nullptr) {
        //output current bidID, title, amount and fund
        cout << curNode->bid.bidId << ", " << curNode->bid.title << ", " << curNode->bid.amount << ", " << curNode->bid.fund << endl;
        //set current equal to next
        curNode = curNode->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // special case if matching node is the head
        if(head->bid.bidId ==  "bidId") {
            // create temp node object
            Node* temp = head;
            // make head point to the next node in the list
            head = head->next;
            // now free up memory held by temp
            delete temp;
            //decrease size count
            size--;
            //return
            return;
        }
        
        
        

    // start at the head
    Node* curNode = head;
    // while loop over each node looking for a match
    while(curNode != nullptr){
        // if the next node bidID is equal to the current bidID
        if(curNode->next->bid.bidId == bidId) {
            // hold onto the next node temporaril
            Node* temp = curNode->next;
            // make current node point beyond the next node
            curNode->next = curNode->next->next;
            // now free up memory held by temp
            delete temp;
            // decrease size count
            size--;
            //return
            return;
        }
        //if not found continue to next element
        curNode = curNode->next;
        
    }
    //return
    return;
}


/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {

    //sets the default bid
    Bid bid;

    // start at the head of the list
    Node* curNode = head;
    // keep searching until end reached with while loop (next != nullptr
    while(curNode != nullptr) {
        // if the current node matches, return it
        if(curNode->bid.bidId == bidId) {
            //return bid
            bid = curNode->bid;
            return bid;
        }
            // else current node is equal to next node
            curNode = curNode->next;
        
    }
    //return empty bid
    return bid;
 
     
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================


/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = Utility::strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void LinkedList::loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = Utility::strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}


void LinkedList::runner(std::string path) {

    // process command line arguments
    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice;

    do {
        choice = Utility::menuSelection();

        switch (choice) {
        case 1: {
            ticks = clock();

            loadBids(path, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
            }
        case 2: {
            bidList.PrintList();

            break;
        }
        case 3: {
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            ticks = clock();

            bid = bidList.Search(bidKey);

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
            bidList.Remove(bidKey);

            break;
        }

    
    } while (choice != 9);


    cout << "Good bye." << endl;
}


/* TO-DO */

/* 1. line 351 Allow for variable bid id input
 * 2. deleting item crashes program
 * 7. main function put clock into seperate function
 * DOCUMENTATION
 * 8. Comments are too much
 * 9. Not enough comments in given code.
 * VARIABLES
 * 10. Main function argument names
 * 11. Line 290 casting to double does not use try-catch
 * LOOPS AND BRANCHES
 * 12. Main does not contain default
 * DEFENSIVE PROGRAMMING
 * 13. Desctructor does not delete head, forever contains a memory address
 */
