#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <string>
#include <climits>

#include "../include/Bid.hpp"


class HashTable {

private:    
    const unsigned int DEFAULT_SIZE = 179;

    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node*> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    void loadBids(string csvPath, HashTable* hashTable);

    //Merge Sort
    void merge(Node** array, int left, int mid, int right);
    void mergeSort(Node** array, int left, int right);

    //Quick Sort
    int partition(Node** array, int low, int high);
    void quickSort(Node** array, int low, int high);

    //Heap Sort
    void heapify(Node** array, int n, int i);
    void heapSort(Node** array, int n);

    void sortAllBids(HashTable* bidTable, int selection);


    void runner(string path);
};

#endif //HASHTABLE_HPP