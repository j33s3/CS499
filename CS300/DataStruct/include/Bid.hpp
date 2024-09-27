#ifndef BID_HPP
#define BID_HPP

#include <string>
using namespace std;

struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};



#endif //BID_HPP