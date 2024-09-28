//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : JYour name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "../include/BinarySearchTree.hpp"
#include "../include/CSVparser.hpp"
#include "../include/Utility.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================




//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    deleteAll(root);
}

/**
 * recursivly deletes the nodes in the tree
 *
 * @param node Current node in tree
 */
void BinarySearchTree::deleteAll(Node* node) {
    // once reaching the end of the tree
    if(node != nullptr) {
        //itterate throught the left and right links
        deleteAll(node->left);
        deleteAll(node->right);

        //delete the nodes
        delete node;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    preOrder(root);
}

/**
 * Inserts a bid into the tree
 *
 * @param bid Bid to be added
 */
void BinarySearchTree::Insert(Bid bid) {

    // if root equarl to null ptr
    if(root == nullptr) {
        // root is equal to new node bid
        root = new Node(bid);
    }
    //if root is occupied
    else{ 
        //create new node pointer
        Node* curNode = root;

        while (curNode != nullptr) {
            //if the incoming bid is smaller than the current
            if(bid.bidId.compare(curNode->bid.bidId) < 0) {
                if(curNode->left == nullptr) {
                    // add Node root and bid
                    curNode->left = new Node(bid);
                    curNode = nullptr;
                }
                else {
                    //itterate to next node
                    curNode = curNode->left;
                }
            }
            // if the incoming bid is larger than the current
            else {
                if(curNode->right == nullptr) {
                    // add Node root and bid
                    curNode->right = new Node(bid);
                    curNode = nullptr;
                }
                else {
                    //itterate to next node
                    curNode = curNode->right;
                }
            }
        }
    }
}

/**
 * Remove a bid from the tree
 *
 * @param bidId BidId for the bid to remove
 */
void BinarySearchTree::Remove(string bidId) {
    // remove node root bidID
    //calls the recursive function
    RemoveNode(root, bidId);
}

/**
 * Recursivly iterates and deletes a specified bidId
 *
 * @param node current node in iteration
 * @param bidId BidId to search for
 * @return Node, possible new root
 */
BinarySearchTree::Node* BinarySearchTree::RemoveNode(Node* node, string bidId) {
    // if the new node is null then end recursive pattern
    if (node == nullptr) {
        return nullptr;
    }
    //if the bidId to be deleted is smaller than the node's bidId, then traverse the left tree
    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = RemoveNode(node->left, bidId);
    }
    // If bidId to be deleted is greater than node's bidId, then traverse the right tree
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = RemoveNode(node->right, bidId);
    }
    // If bidId is same as node's bidId, then delete node
    else {

        // Node with no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node; // Delete node
            node = nullptr;
        }

        // Node with only left child
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node; // Temporary node to be deleted
            node = node->left; // Replace node with its left child
            delete temp; // Delete temporary node
        }

        // Node with only right child
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node; // Temporary node to be deleted
            node = node->right; // Replace node with its right child
            delete temp; // Delete temporary node
        }

        // Node with two children
        else {
            Node* temp = node->right; // Start with right child
            // Find leftmost node in right tree
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            // Replace bid of node to be deleted with temp bid
            node->bid = temp->bid;
            // Delete successor
            node->right = RemoveNode(node->right, temp->bid.bidId);
        }
    }
    // Return possible new root
    return node;
}

/**
 * Searches for a specified bid
 *
 * @param bidId BidId to search for
 * @return bid that searched for
 */
Bid BinarySearchTree::Search(string bidId) {
    // set current node equal to root
    Node* curNode = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (curNode != nullptr){
        // if match found, return current bid
        if(curNode->bid.bidId.compare(bidId) == 0) {
            return curNode->bid;
        }
        // if bid is smaller than current node then traverse left
        if(bidId.compare(curNode->bid.bidId) < 0) {
            curNode = curNode->left;
        } // else larger so traverse right
        else {
            curNode = curNode->right;
        }
    }

    //return un-initialized Bid
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // if node is larger then add to left
    if(bid.bidId.compare(node->bid.bidId) > 0) {
        // if no left node
        if(node->left == nullptr){
            // this node becomes left
            node->left = new Node(bid);
        }
        // else recurse down the left node
        else {
            addNode(node->left, bid);
        }
    }
    // else
    else{
        // if no right node
        if(node->right == nullptr){
        // this node becomes right
            node->right = new Node(bid);
        }
        //else
        else {
        // recurse down the left node
            addNode(node->right, bid);
        }
    }
}

/**
 * Recursively iterate and print elements in-order
 *
 * @param node is the current node in iteration
 */
void BinarySearchTree::inOrder(Node* node) {
      //if node is not equal to null ptr
      if(node != nullptr) {
        //inOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
        //InOder right
        inOrder(node->right);
      }
}

/**
 * Recursively iterate and print elements post-order
 *
 * @param node is the current node in iteration
 */
void BinarySearchTree::postOrder(Node* node) {
      //if node is not equal to null ptr
    if(node != nullptr){
      //postOrder left
      postOrder(node->left);
      //postOrder right
      postOrder(node->right);
      //output bidID, title, amount, fund
      cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
    }
}

/**
 * Recursively iterate and print elements pre-order
 *
 * @param node is the current node in iteration
 */
void BinarySearchTree::preOrder(Node* node) {
      //if node is not equal to null ptr
    if(node != nullptr) {
      //output bidID, title, amount, fund
    cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
      //postOrder left
      preOrder(node->left);
      //postOrder right  
      preOrder(node->right);
    }    
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
void BinarySearchTree::loadBids(string csvPath, BinarySearchTree* bst) {
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
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */

/**
 * The one and only main() method
 */
void BinarySearchTree::runner(std::string path) {

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    do {
        choice = Utility::menuSelection();

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(path, bst);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            cin.get();
            
            break;

        case 2:
            bst->InOrder();
            break;

        case 3: {
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            ticks = clock();

            bid = bst->Search(bidKey);

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
            bst->Remove(bidKey);
            break;
        }
    } while (choice != 9);

    std::cout << "Good bye." << endl;
}


/* TO-DO */

/*
* DOCUMENTATION
* 6. Excessive commenting
* 7. not enough commenting in given code.
*/