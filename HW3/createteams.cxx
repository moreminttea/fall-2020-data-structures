// Mindy Mohr
// 917425752
// createteams.cxx

#include <iostream> //for reading file
#include <fstream> //for reading file
#include <string> //for string ops
#include <iomanip> //for setw()
#include "json.hpp"

#include "priorityqueue.h"
#include "teamdata.h"

int main(int argc, char** argv)
{
    nlohmann::json sampleExample; //file json object
    std::ifstream infile(argv[1]); //read in file from command line
    infile >> sampleExample; //write infile into json
    std::string name = argv[1]; //get filename as string
    (TeamData(name)); //call TeamData function from teamdata.cpp

    return 0;
}
