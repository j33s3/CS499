#include <iostream>
#include <vector>

#include "../include/Utility.hpp"
#include "../include/CSVparser.hpp"
#include "../include/Vector.hpp"


vector<Bid> Vector::loadBids(std::string path) {
    cout << "Loading Data from " << path << endl;

    vector<Bid> bids;

    csv::Parser file = csv::Parser(path);

    try {
        for (int i = 0; i < file.rowCount(); i++) {
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = Utility::strToDouble(file[i][4], '$');

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
void Vector::merge(std::vector<Bid>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Bid> leftArr(n1);
    std::vector<Bid> rightArr(n2);

    for(int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for(int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(leftArr[i].bidId <= rightArr[j].bidId) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
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











void Vector::runner(std::string path) {

    // process command line arguments
    clock_t ticks;

    vector<Bid> bids;

    int choice;

    do {
        choice = Utility::menuSelection();

        switch (choice) {
        case 1: {
            ticks = clock();

            bids = loadBids(path);

            cout << bids.size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
            }
        case 2: {
            for(int i = 0; i < bids.size(); i++) {
                Utility::displayBid(bids[i]);
            }
            cout << endl;

            break;
        }
        case 3: {
            int selection = Utility::sortingSelection();

            switch(selection) {
                case 1:
                    mergeSort(bids, 0, bids.size() - 1);
                    break;
                case 2:
                    heapSort(bids);
                    break;
                case 3:
                    quickSort(bids, 0, bids.size() - 1);
                    break;
            }
            
            break;
        }
        case 4: {
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

            ticks = clock();

            bool bidFound;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            for(int i = 0; i < bids.size(); i++) {
                if(bids[i].bidId == bidKey) {
                    bidFound = true; 
                    std::cout << "Bid was found! " << std::endl;
                    Utility::displayBid(bids[i]);
                }
            }
            if(!bidFound) {
                std::cout << "Unable to find bid" << std::endl;
            }


            cout << "time: " << ticks << " clock ticks" << std::endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;

            break;
            }
        case 5:
            std::string bidKey;
            cout << "Enter Bid Key: ";
            std::cin >> bidKey;

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


    std::cout << "Good bye." << std::endl;
}