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

    // Initializes our left index, right index and combined index
    int lIndex = 0, rIndex = 0, combIndex = left;
    //While neither indexes have reached the end of a sub array
    while(lIndex < n1 && rIndex < n2) {

        //if the current value in left arr is less than right copy it to array
        if(leftArr[lIndex].bidId <= rightArr[rIndex].bidId) {
            arr[combIndex] = leftArr[lIndex];
            lIndex++;
        } else {
            arr[combIndex] = rightArr[rIndex];
            rIndex++;
        }
        combIndex++;
    }

    //Copy any remaining elements from leftArr[] 
    while(lIndex < n1) {
        arr[combIndex] = leftArr[lIndex];
        lIndex++;
        combIndex++;
    }

    //Copy and remaining elements from rightArr[]
    while(rIndex < n2) {
        arr[combIndex] = rightArr[rIndex];
        rIndex++;
        combIndex++;
    }
}

/**
 * @brief Main function for implementing merge sort on arr
 * 
 * @param arr
 * @param left 
 * @param right 
 */
void Vector::mergeSort(std::vector<Bid>& arr, int left, int right) {
    // base case, left index is greater than or equal to right return
    if (left >= right) {
        return;
    }

    //calculate the midpoint
    int mid = left + (right - left) / 2;
    // sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    //merge the two halves
    merge(arr, left, mid, right);
}


//============================================================================
// Heap-Sort Functions
//============================================================================
void Vector::heapify(std::vector<Bid>& arr, int n, int i) {
    //initializes largest as the current root
    int largest = i;
    //initializes index of left and right
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //checks if leftexists and if the bidId is greater than largest
    if (left < n && arr[left].bidId > arr[largest].bidId) {
        largest = left;
    }

    //checks if right exists and if the bidId is greater than left
    if (right < n && arr[right].bidId > arr[left].bidId) {
        largest = right;
    }

    //if largest is not the root node than swap it 
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/**
 * @brief Main function to perform heapSort
 * 
 * @param arr 
 */
void Vector::heapSort(std::vector<Bid>& arr) {
    int n = arr.size();

    // Build the max heap by moving from the largest to the end of the vector
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n , i);
    }

    // Move the current root to the end of the vector
    for(int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


//============================================================================
// Quick-Sort Functions
//==========================================================================

/**
 * @brief it takes the last element as its pivot 
 * and places all elements smaller to the left and larger to the right.
 * 
 * @param arr 
 * @param low 
 * @param high 
 * @return int 
 */
int Vector::partition(std::vector<Bid>& arr, int low, int high) {
    //choose the pivot
    string pivot = arr[high].bidId;
    int i = low - 1;

    //Traverse the array from low to high
    for(int j = low; j < high; j++) {
        //if the bidId is less than pivot than swap it
        if (arr[j].bidId < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

/**
 * @brief Used to divide quicksort by partitioning then sorting
 * 
 * @param arr 
 * @param low 
 * @param high 
 */
void Vector::quickSort(std::vector<Bid>& arr, int low, int high) {
    //Base Case if there at least two items
    if (low < high) {
            //partition the array
            int pi = partition(arr, low, high);
            //apply quick sort to the left and right partitions
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