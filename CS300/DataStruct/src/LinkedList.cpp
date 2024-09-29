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

LinkedList::Node* LinkedList::split(Node* node) {
    Node* fast = node;
    Node* slow = node;

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        if(fast != nullptr) {
            slow = slow->next;
        }
    }
    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;

}

LinkedList::Node* LinkedList::merge(Node* first, Node* second) {
    if(first == nullptr) return second;
    if(second == nullptr) return first;

    if(first->bid.bidId < second->bid.bidId) {
        
        first->next = merge(first->next, second);
        return first;
    }
    else {

        second->next = merge(first, second->next);
        return second;
        
    }
}

LinkedList::Node* LinkedList::mergeSort(Node* node) {
    if(node == nullptr || node->next == nullptr) {
        return node;
    }

    Node* second = split(node);

    node = mergeSort(node);
    second = mergeSort(second);

    return merge(node, second);
}

//============================================================================
// Heap-Sort Functions
//============================================================================

//https://www.geeksforgeeks.org/heap-sort-for-linked-list/

void LinkedList::heapify(Node** array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && array[left]->bid.bidId > array[largest]->bid.bidId) largest = left;
    if(right < n && array[right]->bid.bidId > array[largest]->bid.bidId) largest = right;

    if(largest != i) {
        swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

LinkedList::Node* LinkedList::heapSort(Node* node, int size) {
    if (!node) return nullptr;

    int n = size;
    Node** array = new Node*[n];

    Node* curr = node;
    for(int i = 0; i < n; i++) {
        array[i] = curr;
        curr = curr->next;
    }

    for(int i = n / 2 - 1; i >= 0; i--) heapify(array, n, i);

    for(int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }

    node = array[0];
    Node* sortedCurr = node;
    for (int i = 1; i < n; i++) {
        sortedCurr->next = array[i];
        sortedCurr = sortedCurr->next;
    }
    sortedCurr->next = nullptr;

    Node* newHead = array[0];

    delete[] array;

    return newHead;
}

//============================================================================
// Quick-Sort Functions
//============================================================================

    LinkedList::Node* LinkedList::partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
        Node* pivot = end;
        Node* prev = nullptr, *curr = head, *tail = pivot;

        while (curr != pivot) {
            if(curr->bid.bidId < pivot->bid.bidId) {
                if(*newHead == nullptr) {
                    *newHead = curr;
                }
                prev = curr;
                curr = curr->next;
            } else {
                if(prev) prev->next = curr->next;
                Node* tmp = curr->next;
                curr->next = nullptr;
                tail->next = curr;
                tail = curr;
                curr = tmp;
            }
        }

        if (*newHead == nullptr) *newHead = pivot;
        *newEnd = tail;

        return pivot;

    }


    LinkedList::Node* LinkedList::quickSort(Node* head, Node* end) {
        if(!head || head == end) return head;

        Node* newHead = nullptr, *newEnd = nullptr;
        Node* pivot = partition(head, end, &newHead, &newEnd);

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

    LinkedList::Node* LinkedList::getTail(Node* cur) {
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
