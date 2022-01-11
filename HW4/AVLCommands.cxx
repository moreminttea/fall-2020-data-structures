// Mindy Mohr
// 917425752
// AVLCommands.cxx

#include <iostream> //for reading file
#include <fstream> //for reading file
#include <string> //for string ops
#include <iomanip> //for setw()
#include "json.hpp"
#include "AVL.h"

int main(int argc, char** argv)
{
    nlohmann::json sampleExample; //original json object
    std::ifstream infile(argv[1]); //read in file from command line
    infile >> sampleExample; //write infile into json
    nlohmann::json jsonObject; //new json object
    
    AVL avl; //create avl tree
    
    for (int i = 1; i <= 1000; i++) //for loop to read and execute operation commands from json
    {
        std::string operation_num; //to read json operation command
        if (i <= 9)
        {
            if (sampleExample["metadata"]["numOps"] == 10)
            {
                operation_num = "0" + std::to_string(i); //to read "01" ... "09"
            }
            else
            {
                operation_num = "000" + std::to_string(i); //to read "Op0001" ... "Op0009"
            }
        }
        
        else if (i > 9 && i <= 99)
        {
            if (sampleExample["metadata"]["numOps"] == 10)
            {
                operation_num = std::to_string(i); //to read "10"
            }
            else
            {
                operation_num = "00" + std::to_string(i); //to read "0011" ... "0099"
            }
        }
        
        else if (i > 99 && i <= 999)
        {
            operation_num = "0" + std::to_string(i); //to read "0100" ... "0999"
        }
        
        else
        {
            operation_num = std::to_string(i); //to read "1000" ...
        }
        
        if (sampleExample[operation_num]["operation"] == "Insert") //if json command reads "insert"
        {
            int node = sampleExample[operation_num]["key"]; //get key from json
            avl.Insert(node); //call insert() function from AVL.cpp
        }
    }
    std::cout << std::setw(2) << nlohmann::json::parse(avl.JSON()) << std::endl; //print parsed JSON results by calling JSON() function from AVL.cpp
    
    return 0;
}
