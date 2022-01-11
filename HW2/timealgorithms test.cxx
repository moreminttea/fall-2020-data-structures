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

std::vector<int> checkSortedIndex(const nlohmann::json& sampleExample, int n)
{
    std::vector<int> num;
    for (int i = 0; i < n - 3; ++i)
    {
        num.push_back(i);
    }
    return num;
}

/*
int main(int argc, char** argv)
{
    //read in json
    nlohmann::json sampleExample;
    ifstream infile(argv[1]); //read in file from command line
    infile >> sampleExample;
    std::string filename = argv[1];
    
    std::vector<int> insertion_array;
    std::vector<int> merge_array;
    std::vector<int> quick_array;
    
    nlohmann::json jsonObject;
    for (int i = 1; i <= 9; ++i)
    {
        insertion_array = checkSortedIndex(sampleExample["Sample0"+std::to_string(i)], sizeof(sampleExample["Sample0"+std::to_string(i)]));
        merge_array = checkSortedIndex(sampleExample["Sample0"+std::to_string(i)], sizeof(sampleExample["Sample0"+std::to_string(i)]));
        quick_array = checkSortedIndex(sampleExample["Sample0"+std::to_string(i)], sizeof(sampleExample["Sample0"+std::to_string(i)]));
        
        int quick_mem_access = 0;
        QuickSort(&quick_array, quick_mem_access);
        printf("%d,%d\n", i, quick_mem_access);
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
*/

int main(int argc, char* argv[])
{
    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if (file.is_open())
    {
        file >> jsonObject;
    }
    else
    {
        std::cout << "Invalid Argument" << std::endl;
    }
    clock_t mergeTime, quickTime, insertTime;
    extern int insertMemAccesses, insertCompare, mergeMemAccesses, mergeCompare, quickCompare, quickMemAccesses;
//    std::cout << jsonObject;
//    nlohmann::json jsonOutput;

    std::cout << "Sample,InsertSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess\n";

    int arraysize = jsonObject["metadata"]["arraySize"];
    int numsamples = jsonObject["metadata"]["numSamples"];

    for (int i = 0; i <= numsamples; i++)
    {
        std::string sample;
        if (i < 9)
        {
            sample = "Sample0" + std::to_string(i+1);
        }
        else
        {
            sample = "Sample" + std::to_string(i+1);
        }
        //std::vector<int> insertion;
        auto merge_array = MyVector<int>();
        auto insertion_array = MyVector<int>();
        auto quick_array = MyVector<int>();

        for(int j = 0; j <= 9; ++j)
        {
            //insertion = checkSortedIndex(jsonObject[sample], sizeof(jsonObject[sample]));
            //merge_array = checkSortedIndex(jsonObject[sample], sizeof(jsonObject[sample]));
            quick_array.push_back(jsonObject[sample][j]);
            merge_array.push_back(jsonObject[sample][j]);
            insertion_array.push_back(jsonObject[sample][j]);
            //quick_array = checkSortedIndex(jsonObject[sample], sizeof(jsonObject[sample]));
        }

        
        int insert_mem_access = 0;
        int insert_compare = 0;
        insertTime = clock();
        InsertionSort(&insertion_array, insert_mem_access, insert_compare);
        std::cout << "[I] Memory access: " << insert_mem_access << '\n';
        std::cout << "[I] Compare: " << insert_compare << '\n';
        insertTime = clock() - insertTime;

        insertTime = ((unsigned long)insertTime)/CLOCKS_PER_SEC;
         
        int merge_mem_access = 0;
        int merge_compare = 0;
        mergeTime = clock();
        MergeSort(&merge_array, merge_mem_access, merge_compare);
        std::cout << "[M] Memory access: " << merge_mem_access << '\n';
        std::cout << "[M] Compare: " << merge_compare << '\n';
        mergeTime = clock() - mergeTime;

        mergeTime = ((unsigned long)mergeTime)/CLOCKS_PER_SEC;

        //std::cout << "Before\n";
        //for (auto const& e : quick_array)
        //{
        //    std::cout << e << ' ';
        //}
        //std::cout << '\n';
        
        int quick_mem_access = 0;
        int quick_compare = 0;
        quickTime = clock();
        QuickSort(&quick_array, quick_mem_access, quick_compare);
        std::cout << "[Q] Memory access: " << quick_mem_access << '\n';
        std::cout << "[Q] Compare: " << quick_compare << '\n';
        quickTime = clock() - quickTime;
        
        
        /*
        std::cout << "After\n";
        for (auto const& e : quick_array)
        {
            std::cout << e << ' ';
            
        }
        std::cout << '\n';

        quickTime = ((unsigned long)quickTime)/CLOCKS_PER_SEC;
*/
        std::cout<<sample<<","<<"\n";
        //printf("%d\n", quickMemAccesses);
        //printf("%.6lu,%d,%d,%.6lu,%d,%d,%.6lu,%d,%d\n",insertTime,insertCompare,insertMemAccesses,mergeTime,mergeCompare,mergeMemAccesses,quickTime,quickCompare,quickMemAccesses);


        //insertCompare = 0;
        //insertMemAccesses = 0;
        //mergeCompare = 0;
        //mergeMemAccesses = 0;
        //quickCompare = 0;
        //quickMemAccesses = 0;
    }
  return 0;
}
