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

    // if root equal to null ptr
    if(root == nullptr) {
        root = new Node(bid);
    }
    //if root is occupied
    else{ 
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
            delete node;
            node = nullptr;
        }

        // Node with only left child
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }

        // Node with only right child
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
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
    else{
        // if no right node
        if(node->right == nullptr){
        // this node becomes right
            node->right = new Node(bid);
        }
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
        inOrder(node->left);
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
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
      postOrder(node->left);
      postOrder(node->right);
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
    cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
      preOrder(node->left);
      preOrder(node->right);
    }    
}


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
 * This is the runner function for the BST class
 * It is in charge of handling user input/selection
 * It also calculates time complexities
 * @param string file path
 */
void BinarySearchTree::runner(std::string path) {

    //Declare Variables
    clock_t ticks;
    BinarySearchTree* bst;
    Bid bid;
    int choice = 0;

    bst = new BinarySearchTree();

    do {
        //Ask the user for input
        choice = Utility::menuSelection();
        Utility::clearTerm();

        switch (choice) {
        //Load Bids
        case 1:
            
            // Initialize a timer
            ticks = clock();

            loadBids(path, bst);

            // Calculate elapsed time
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;
            cin.get();
            
            break;
        //Print All
        case 2:
            bst->InOrder();
            break;
        //Find Bid
        case 3: {
            //Ask user for BidId
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            // Initialize a timer
            ticks = clock();

            bid = bst->Search(bidKey);

            //Prints the bid
            if (!bid.bidId.empty()) {
                Utility::displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            // Calculate elapsed time
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            break;
            }
        //Remove Bid
        case 4:
            //Ask the user for BidId
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            bst->Remove(bidKey);
            
            break;
        }
    } while (choice != 0);
}