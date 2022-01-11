// Mindy Mohr
// 917425752
// timealgorithms.cxx

//./timealgorithms Example1.json
//cat Example1.json.csv

#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"
#include "mergesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "myvector.hpp"

using namespace std;


nlohmann::json checkSortedIndex(const nlohmann::json& sampleExample, int n)
{
    //MyVector<int> array;
    nlohmann::json jsonObject;
    for (int i = 0; i < n - 3; ++i)
    {
        jsonObject.push_back(sampleExample[i]);
    }
    return jsonObject;
}


int main(int argc, char** argv)
{
    //read in json
    nlohmann::json sampleExample;
    ifstream infile(argv[1]); //read in file from command line
    infile >> sampleExample;
    std::string filename = argv[1];
    
    auto quick_array = MyVector<int>();
    //std::vector<int> merge_array;
    //std::vector<int> quick_array;
    
    nlohmann::json jsonObject;
    for (int i = 1; i <= 9; ++i)
    {
        //insertion_array = checkSortedIndex(sampleExample["Sample0"+std::to_string(i)], sizeof(sampleExample["Sample0"+std::to_string(i)]));
        //merge_array = checkSortedIndex(sampleExample["Sample0"+std::to_string(i)], sizeof(sampleExample["Sample0"+std::to_string(i)]));
        //quick_array = checkSortedIndex(sampleExample["Sample0"+std::to_string(i)], sizeof(sampleExample["Sample0"+std::to_string(i)]));
        
        quick_array.push_back(sampleExample["Sample0"+std::to_string(i)]);
        
        std::cout << "Before\n";
        for (auto const& e : quick_array)
        {
            std::cout << e << ' ';
        }
        
        int mem_access = 0;
        
        std::cout << "[M3] Memory access: " << mem_access << '\n';
        QuickSort(&quick_array, mem_access);
        std::cout << "[M3] Memory access: " << mem_access << '\n';
        
        std::cout << "After\n";
        for (auto const& e : quick_array)
        {
            std::cout << e << ' ';
            
        }
        //printf("%d,%d\n", i, quick_mem_access);
    }
    
    
    //std::vector<int>* array = readinDataset(sampleExample);
    
    std::ofstream outfile;
    outfile.open(filename+".csv");
    outfile << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess\n";
    
    //nlohmann::json jsonObject;
    for (int j = 1; j <= 9; ++j)
    {
        //int InsertionSortMemaccess = InsertionSort(sampleExample, 0);
        outfile << "Sample0"+std::to_string(j)+"\n";
    }
    outfile << "Sample10\n";

    //printf("%d\n", quick_mem_access);
 
    return 0;
}
