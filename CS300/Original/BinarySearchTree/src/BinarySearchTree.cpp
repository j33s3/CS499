//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : JYour name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* RemoveNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);

    void deleteAll(Node* node); //Added
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
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
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root
    preOrder(root);
}

/**
 * Inserts a bid into the tree
 *
 * @param bid Bid to be added
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (5) Implement inserting a bid into the tree

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
    // FIXME (6) Implement removing a bid from the tree
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
Node* BinarySearchTree::RemoveNode(Node* node, string bidId) {
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
    // FIXME (7) Implement searching the tree for a bid
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
    // FIXME (8) Implement inserting a bid into the tree
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
      // FixMe (9): Pre order root
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
      // FixMe (10): Pre order root
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
      // FixMe (11): Pre order root
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
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
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
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

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
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end()); // Remove the specified character from the string
    return atof(str.c_str()); // Convert the modified string to a double
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);
            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
