#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Bid.hpp"
#include <string>





namespace Utility {

    double strToDouble(std::string str, char ch);
    void displayBid(Bid bid);
    int menuSelection();
    void clearTerm();
}

#endif //UTILITY_HPP