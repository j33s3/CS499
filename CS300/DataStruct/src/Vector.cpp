#include <iostream>
#include <vector>

#include "../include/Utility.hpp"
#include "../include/CSVparser.hpp"
#include "../include/Vector.hpp"

/**
 * Handles loading bids into the Vector data Structure
 * @param string, filepath 
 */
vector<Bid> Vector::loadBids(std::string path) {
    cout << "Loading Data from " << path << endl;

    vector<Bid> bids;

    csv::Parser file = csv::Parser(path);

    try {
        //Iterate through the contents of the file and add it to bid
        for (int i = 0; i < file.rowCount(); i++) {
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = Utility::strToDouble(file[i][4], '$');

            //Push the bid to the back of the vector
            bids.push_back(bid);

        }
    } catch(csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

//============================================================================
// Merge-Sort Functions
//============================================================================

/**
 * This merges two subarrays into a single array
 * The left array = arr[left..mid]
 * The right array = arr[mid + 1..right]
 */
void Vector::merge(std::vector<Bid>& arr, int left, int mid, int right) {
    //Calculates the size of both array
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //Declares the sub arrays
    std::vector<Bid> leftArr(n1);
    std::vector<Bid> rightArr(n2);

    //Fill the left array
    for(int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    //Fill the right array
    for(int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }


    int lIndex = 0, rIndex = 0, combIndex = left;
    while(lIndex < n1 && rIndex < n2) {
        if(leftArr[lIndex].bidId <= rightArr[rIndex].bidId) {
            arr[combIndex] = leftArr[lIndex];
            lIndex++;
        } else {
            arr[combIndex] = rightArr[rIndex];
            rIndex++;
        }
        combIndex++;
    }

    while(lIndex < n1) {
        arr[combIndex] = leftArr[lIndex];
        lIndex++;
        combIndex++;
    }

    while(rIndex < n2) {
        arr[combIndex] = rightArr[rIndex];
        rIndex++;
        combIndex++;
    }
}

void Vector::mergeSort(std::vector<Bid>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


//============================================================================
// Heap-Sort Functions
//============================================================================
void Vector::heapify(std::vector<Bid>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].bidId > arr[largest].bidId) {
        largest = left;
    }

    if (right < n && arr[right].bidId > arr[left].bidId) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void Vector::heapSort(std::vector<Bid>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n , i);
    }

    for(int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


//============================================================================
// Quick-Sort Functions
//==========================================================================
int Vector::partition(std::vector<Bid>& arr, int low, int high) {
    string pivot = arr[high].bidId;
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if (arr[j].bidId < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Vector::quickSort(std::vector<Bid>& arr, int low, int high) {
    if (low < high) {
            int pi = partition(arr, low, high);

            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
    }
}










/**
 * This function is used for running the vector class
 * It handles the menu selection as well as complexity tracking
 */
void Vector::runner(std::string path) {
    // Declare variables
    clock_t ticks;
    vector<Bid> bids;
    int choice;


    do {
        choice = Utility::menuSelection();
        Utility::clearTerm();

        switch (choice) {
        //Load data
        case 1: {
            //Initialize clock
            ticks = clock();

            bids = loadBids(path);

            cout << bids.size() << " bids read" << endl;

            //Save time complexity
            ticks = clock() - ticks;
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            break;
            }
        //Print All
        case 2: {
            //iterate through all indexes and print the bidId
            for(int i = 0; i < bids.size(); i++) {
                Utility::displayBid(bids[i]);
            }
            cout << endl;

            break;
        }
        //Sort
        case 3: {
            //Select sorting algorithm
            int selection = Utility::sortingSelection();
            Utility::clearTerm();

            //Initialize clock
            ticks = clock();
            switch(selection) {
                //Merge Sort
                case 1: 
                    mergeSort(bids, 0, bids.size() - 1);
                    break;
                //Heap Sort
                case 2:
                    heapSort(bids);
                    break;
                //Quick Sort
                case 3:
                    quickSort(bids, 0, bids.size() - 1);
                    break;
            }

            //Save time complexity
            ticks = clock() - ticks;
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;
            
            break;
        }
        //Find Bid
        case 4: {
            //Ask user to enter a bidKey
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            //Initialize clock
            ticks = clock();

            //will be set to true if the bid is found.
            bool bidFound = false;

            //Iterate through vector and display bid if found
            for(int i = 0; i < bids.size(); i++) {
                if(bids[i].bidId == bidKey) {
                    bidFound = true; 
                    std::cout << "Bid was found! " << std::endl;
                    Utility::displayBid(bids[i]);
                }
            }
            //If bid is not found notify the user
            if(!bidFound) {
                std::cout << "Unable to find bid" << std::endl;
            }

            //Save Time complexity
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << std::endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl << std::endl;

            break;
            }
        //Remove Bid
        case 5:
            //Ask the user for a bidId
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            //Iterate through the vector and remove index if match is found.
            vector<Bid>::iterator iterator = bids.begin();
            while(iterator != bids.end()) {
                if(iterator->bidId == bidKey) {
                    iterator = bids.erase(iterator);
                    break;
                } else {
                    ++iterator;
                }
            }
            break;
        }

    
    } while (choice != 0);
}