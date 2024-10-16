#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "../include/Bid.hpp"



class BinarySearchTree {
    private:
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

        Node* root;

        void addNode(Node* node, Bid bid);
        void inOrder(Node* node);
        void postOrder(Node* node);
        void preOrder(Node* node);
        Node* RemoveNode(Node* node, string bidId);

        std::string menu =  "Please select an option:\n"
                            "========================\n"
                            "* Load Bids        - 1 *\n"
                            "* Display All Bids - 2 *\n"
                            "* Find Bid         - 3 *\n"
                            "* Remove Bid       - 4 *\n"
                            "* Exit             - 0 *\n"
                            "========================\n"
                            "Enter a number: ";

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
        void loadBids(string csvPath, BinarySearchTree* bst);
        void runner(string path);
};

#endif //BINARYSEARCHTREE_HPP