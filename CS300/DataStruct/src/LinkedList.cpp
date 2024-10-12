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
        temp = current; 
        current = current->next;
        delete temp;
    }
}

//============================================================================
// Merge-Sort Functions
//============================================================================

//https://www.geeksforgeeks.org/merge-sort-for-linked-list/

/**
 * @brief splits the linked list into two halves
 * It returns the start of the second half
 * 
 * @param node 
 * @return LinkedList::Node* 
 */
LinkedList::Node* LinkedList::split(Node* node) {
    // Initialize two pointers: fast moves two steps and slow, one step
    Node* fast = node;
    Node* slow = node;

    //itterate through the array and split the list
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        if(fast != nullptr) {
            slow = slow->next;
        }
    }
    //Splits the list by breaking it at the midpoint
    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;

}

/**
 * @brief Merges two sorted linked lists
 * 
 * @param first 
 * @param second 
 * @return LinkedList::Node* 
 */
LinkedList::Node* LinkedList::merge(Node* first, Node* second) {
    //Base case: 
    if(first == nullptr) return second;
    if(second == nullptr) return first;

    //Compare the bidIds of both first annd second nodes
    if(first->bid.bidId < second->bid.bidId) {
        
        first->next = merge(first->next, second);
        return first;
    }
    else {

        second->next = merge(first, second->next);
        return second;
        
    }
}

/**
 * @brief This is the main function for the mergeSort algorithm
 * 
 * @param node 
 * @return LinkedList::Node* 
 */
LinkedList::Node* LinkedList::mergeSort(Node* node) {
    //Base case: if either nod eis null
    if(node == nullptr || node->next == nullptr) {
        return node;
    }

    //split the list into halves
    Node* second = split(node);

    //recursively sort the first and second halves
    node = mergeSort(node);
    second = mergeSort(second);

    //Merge two sorted arrays together
    return merge(node, second);
}

//============================================================================
// Heap-Sort Functions
//============================================================================

//https://www.geeksforgeeks.org/heap-sort-for-linked-list/

void LinkedList::heapify(Node** array, int n, int i) {
    //Initializes largest as the current root
    int largest = i;
    //Initializes index of left and right
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //Checks if left exists and if the bidId is greater than largest
    if(left < n && array[left]->bid.bidId > array[largest]->bid.bidId) largest = left;
    //Checks if right exists and if the bidId is greater than largest
    if(right < n && array[right]->bid.bidId > array[largest]->bid.bidId) largest = right;

    //if largest is not the root node than swap it
    if(largest != i) {
        swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

LinkedList::Node* LinkedList::heapSort(Node* node, int size) {
    //if the linked list is empty return nullptr
    if (!node) return nullptr;
        
    //creates a new array of pointers to stor linked list nodes
    int n = size;
    Node** array = new Node*[n];

    //copy nodes into array
    Node* curr = node;
    for(int i = 0; i < n; i++) {
        array[i] = curr;
        curr = curr->next;
    }

    //build max heap by calling heapify
    for(int i = n / 2 - 1; i >= 0; i--) heapify(array, n, i);

    //extract elements from the heap
    for(int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }

    //Rebuild the linked list from the sorted array
    node = array[0];
    Node* sortedCurr = node;
    for (int i = 1; i < n; i++) {
        sortedCurr->next = array[i];
        sortedCurr = sortedCurr->next;
    }
    sortedCurr->next = nullptr;

    //store the address to the new head and return
    Node* newHead = array[0];

    delete[] array;

    return newHead;
}

//============================================================================
// Quick-Sort Functions
//============================================================================
    /**
     * @brief It takes the last element as it pivot
     * and places all elements smaller to the left and larger to the right
     * 
     * @param head 
     * @param end 
     * @param newHead 
     * @param newEnd 
     * @return LinkedList::Node* 
     */
    LinkedList::Node* LinkedList::partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
        //Choose the pivot
        Node* pivot = end;
        Node* prev = nullptr, *curr = head, *tail = pivot;

        // Traverse the list from the head to pivot
        while (curr != pivot) {
            //if the current is smaller than pivot
            if(curr->bid.bidId < pivot->bid.bidId) {
                //set current to newHead
                if(*newHead == nullptr) {
                    *newHead = curr;
                }
                prev = curr;
                curr = curr->next;
            } else {
                //If greater than pivot moves it to the end of the list
                if(prev) prev->next = curr->next;
                Node* tmp = curr->next;
                curr->next = nullptr;
                tail->next = curr;
                tail = curr;
                curr = tmp;
            }
        }

        //newHead is not set, the pivot is the smallest
        if (*newHead == nullptr) *newHead = pivot;
        *newEnd = tail;

        return pivot;

    }

    /**
     * @brief recursively sorts the array
     * 
     * @param head 
     * @param end 
     * @return LinkedList::Node* 
     */
    LinkedList::Node* LinkedList::quickSort(Node* head, Node* end) {
        //Base Case, if the list is empty
        if(!head || head == end) return head;

        // initialize the new head and new end
        Node* newHead = nullptr, *newEnd = nullptr;

        //initialize the pivot as a partition
        Node* pivot = partition(head, end, &newHead, &newEnd);

        //if the new head is not the pivot then sort the left partition
        if (newHead != pivot) {
            Node* tmp = newHead;
            while (tmp->next != pivot) tmp = tmp->next;
            tmp->next = nullptr;

            newHead = quickSort(newHead, tmp);

            tmp = getTail(newHead);
            tmp->next = pivot;
        }
        
        pivot->next = quickSort(pivot->next, newEnd);
        
        return newHead;
    }

    /**
     * @brief Utility function for finding tail
     * 
     * @param cur 
     * @return LinkedList::Node* 
     */
    LinkedList::Node* LinkedList::getTail(Node* cur) {
        //Iterates to the end and returns tail node.
        while(cur != nullptr && cur->next != nullptr) {
            cur = cur->next;
        }
        return cur;
    }

//============================================================================
// LinkedList Base Functions
//============================================================================

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    Node* curNode = head;

    int i = 1;
    //Iterate through the List and print details
    while(curNode != nullptr) {
        std::cout << i << ": " << curNode->bid.bidId << ", " << curNode->bid.title << ", " << curNode->bid.amount << ", " << curNode->bid.fund << endl;
        curNode = curNode->next;
        i++;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
        
        // special case to remove head node
        if(head->bid.bidId == bidId){
            //Store the node in temp
            //Then set the head to the next node before deleting the unused pointer.
            Node* temp = head;
            head = head->next;
            delete(temp);
            size--;
            return;
        }

        // Removes nodes in the middle list
        Node* curNode = head;
        Node* prevNode = nullptr;
        //Iterate till reaching the end of list
        while (curNode != nullptr) {
            // Set the previous node to point to the node after target
            // Then delete the target
            if(curNode->bid.bidId == bidId) {
                //if the end of the list
                if(curNode->next == nullptr) {
                    if(prevNode != nullptr) {
                        prevNode->next = nullptr;
                    }
                    delete curNode;
                //if between the list
                } else {
                    Node* temp = curNode;
                    prevNode->next = curNode->next;
                    delete temp;
                }
                size--;
                return;
            }
            //iterate
            prevNode = curNode;
            curNode = curNode->next;
        }

        return;
        
        

}


/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    Bid bid;
    Node* curNode = head;

    // keep searching until end
    while(curNode != nullptr) {
        // if the current node matches, return it
        if(curNode->bid.bidId == bidId) {
            bid = curNode->bid;
            return bid;
        }
            // else current node is equal to next node
            curNode = curNode->next;
        
    }
    return bid;
 
     
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void LinkedList::loadBids(string csvPath, LinkedList *list) {
    std::cout << "Loading CSV file " << csvPath << endl;

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

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Appends a bid the end of the LinkedList
 * @param Bid bid
 */
void LinkedList::Append(Bid bid) {
    Node* newNode = new Node(bid);

    //if there is nothing at the head...
    if(head == nullptr) {
        // new node becomes the head and the tail
        head = newNode;
        tail = newNode;
    } else { 
        // make current tail node point to the new node
        tail->next = newNode;
            // and tail becomes the new node
        tail = newNode;
    }

    size++;
}


/**
 * This is the runner function for the LinkedList class
 * It manages user input/selection.
 * Also tests time complexities.
 * @param Strin File Path
 */
void LinkedList::runner(std::string path) {
    // Variable Declaration
    clock_t ticks;
    LinkedList bidList;
    Bid bid;
    int choice;

    do {
        choice = Utility::menuSelection();
        Utility::clearTerm();

        switch (choice) {
        //Load Bids
        case 1: {
            //Initalizes the clock
            ticks = clock();

            loadBids(path, &bidList);


            std::cout << bidList.Size() << " bids read" << endl;

            //Save Time Complexity
            ticks = clock() - ticks;
            std::cout << "time: " << ticks << " milliseconds" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            break;
            }
        //Print All
        case 2: {
            bidList.PrintList();

            break;
        }
        //Sort
        case 3: {
            //Ask the user to select an Algorithm
            int selection = Utility::sortingSelection();
            Utility::clearTerm();

            //Initalizes the clock
            ticks = clock();

            switch(selection) {
                //Merge Sort
                case 1:
                    bidList.head = mergeSort(bidList.head);
                    bidList.tail = getTail(bidList.tail);
                    break;
                //Heap Sort
                case 2:
                    bidList.head = heapSort(bidList.head, bidList.Size());
                    bidList.tail = getTail(bidList.head);
                    break;
                //Quick Sort
                case 3:
                    bidList.head = quickSort(bidList.head, bidList.tail);
                    bidList.tail = getTail(bidList.head);
                    break;
            }

            //Save Time Complexity
            ticks = clock() - ticks;
            std::cout << "time: " << ticks << " milliseconds" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            break;
        }
        //Find Bid
        case 4: {
            //Ask user for BidId
            std::string bidKey;
            std::cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            //Initalizes the clock
            ticks = clock();

            bid = bidList.Search(bidKey);
            

            // Print bid
            if (!bid.bidId.empty()) {
                Utility::displayBid(bid);
            } else {
            	std::cout << "Bid Id " << bidKey << " not found." << endl;
            }

            //Save Time Complexity
            ticks = clock() - ticks;
            std::cout << "time: " << ticks << " clock ticks" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            break;
            }
        //Remove Bid
        case 5:
            //Ask user for BidId
            std::string bidKey;
            std::cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            bidList.Remove(bidKey);

            break;
        }

    } while (choice != 0);
}
