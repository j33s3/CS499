#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include "Bid.hpp"

class Vector {
    public:

    // For Merge Sorting
    void merge(std::vector<Bid>& arr, int left, int mid, int right);
    void mergeSort(std::vector<Bid>& arr, int left, int right);

    // For Heap Sorting
    void heapify(std::vector<Bid>& arr, int n, int i);
    void heapSort(std::vector<Bid>& arr);

    // For Quick Sorting
    int partition(std::vector<Bid>& arr, int low, int high);
    void quickSort(std::vector<Bid>& arr, int low, int high);

    //Basic opertional functions
    vector<Bid> loadBids(std::string path);
    void runner(std::string path);
};

#endif //VECTOR_HPP