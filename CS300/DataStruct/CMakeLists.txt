# Minimum CMake Version
cmake_minimum_required(VERSION 3.10)

# Project Name
project(DataStruct)

# Set c++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting Environment Variables
set(MONTHLY_SALES "/home/Retr0/Code/CS499/CS300/DataStruct/data/eBid_Monthly_Sales.csv")
set(MONTHLY_SALES_2016 "/home/Retr0/Code/CS499/CS300/DataStruct/data/eBid_Monthly_Sales_Dec_2016.csv")

# Add Source Files
set(SOURCES
    Main.cpp
    src/LinkedList.cpp
    src/HashTable.cpp
    src/BinarySearchTree.cpp
    src/CSVparser.cpp
    src/Utility.cpp
)


# Adding Definitions
add_definitions(-DCSV_FILE_PATH1="${MONTHLY_SALES}")
add_definitions(-DCSV_FILE_PATH2="${MONTHLY_SALES_2016}")

# Create the Executable
add_executable(Main.exe ${SOURCES})