// Mindy Mohr
// 917425752
// buildheap.cxx

#include <iostream> //for reading file
#include <fstream> //for reading file
#include <string> //for string ops
#include <iomanip> //for setw()
#include "json.hpp"

#include "priorityqueue.h"

int main(int argc, char** argv)
{
    nlohmann::json sampleExample; //original json object
    std::ifstream infile(argv[1]); //read in file from command line
    infile >> sampleExample; //write infile into json
    nlohmann::json jsonObject; //new json object
    
    int heap_size = 0; //tracking size of heap with each operation
    size_t max = sampleExample["metadata"]["maxHeapSize"]; //max size of heap
    PriorityQueue heap(max); //create priority queue heap of max size
    
    for (int i = 1; i <= 200; i++) //for loop to read and execute operation commands from json
    {
        std::string operation_num; //to read json operation command
        if (i <= 9)
        {
            operation_num = "Op00" + std::to_string(i); //to read "Op001" ... "Op009"
        }
        else if (i > 9 && i <= 99)
        {
            operation_num = "Op0" + std::to_string(i); //to read "Op010" ... "Op099"
        }
        else
        {
            operation_num = "Op" + std::to_string(i); //to read "Op100" ... "Op200"
        }
        
        if (sampleExample[operation_num]["operation"] == "insert") //if json command reads "insert"
        {
            int k = sampleExample[operation_num]["key"]; //get key from json
            heap.insert(k); //call insert() function from priorityqueue.cpp
            ++heap_size; //increment size of heap with each insertion
        }
        
        if (sampleExample[operation_num]["operation"] == "removeMin") //if json command reads "removeMin"
        {
             heap.removeMin(); //call removeMin() function from priorityqueue.cpp
             --heap_size; //decrement size of heap with each removal
        }
    }
    
    std::cout << std::setw(2) << heap.JSON() << std::endl; //printing heap results using JSON() function from priorityqueue.cpp
    
    //metadata of json object
    jsonObject["metadata"]["maxHeapSize"] = sampleExample["metadata"]["maxHeapSize"];
    jsonObject["metadata"]["max_size"] = sampleExample["metadata"]["maxHeapSize"];
    jsonObject["metadata"]["numOperations"] = sampleExample["metadata"]["numOperations"]; 
    jsonObject["metadata"]["size"] = heap_size;
    
    std::cout << std::setw(2) << jsonObject << std::endl; //printing metadata info from json
    
    return 0; //return
}
