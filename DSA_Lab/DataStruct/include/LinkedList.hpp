#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>

#include "../include/Bid.hpp"

class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        Bid bid;
        Node *next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
    
    void loadBids(string csvPath, LinkedList *list);

    //Merge Sort
    Node* mergeSort(Node* node);
    Node* merge(Node* first, Node* second);
    Node* split(Node* node);

    //Heap Sort
    void heapify(Node** array, int n, int i);
    Node* heapSort(Node* node, int size);

    //Quick Sort
    Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd);
    Node* quickSort(Node* head, Node* end);
    Node* getTail(Node* cur);

    void runner(string path);
};

#endif //LINKEDLIST_HPP