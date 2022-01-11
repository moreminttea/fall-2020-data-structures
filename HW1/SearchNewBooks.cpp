// Mindy Mohr
// 917425752
// SearchNewBooks.cc

#include "SearchNewBooks.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <string>
#include <vector>
#include <chrono>

using namespace std;


/*
 * REFERENCED CITED SOURCES
 *
 *      for reading in file: CU Boulder Data Structures CSCI 2270 (2018) Data Structures Tutorial - 14 - How to Read in a Comma Separated .txt File in c++. https://youtu.be/_IzYGiuX8QM
 *      reading command line file arguments: (2015) how to pass command line argument to read txt file. https://stackoverflow.com/questions/30141000/c-how-to-pass-command-line-argument-to-read-txt-file/30141375
 *      searching for two equal vectors for linear and binary search: (2019) how to do a linear search of two vectors in c++. https://stackoverflow.com/questions/58337063/how-to-do-a-linear-search-of-two-vectors-in-c
 *      binary search and chrono time management: professor Frid's lecture and program 1 pdf
*/


//function that reads information from command line file and and stores into a vector
std::vector<std::string> readinDataset(const std::string& file)
{
    //reading in command line files
    std::ifstream filename;
    filename.open(file);

    if (!filename.is_open())
    {
        std::cerr << "cannot open file " << file << std::endl;
        exit(0); //quit program if cannot open either newBooks or requestedBooks files
    }

    //variables for reading file and storing information
    std::string line;
    std::string temp_isbn_str, language, type; //info to be read and stored
    std::vector<std::string> dataset; //info stored in this vector

    //while loop to read in lines of file and store into vector
    while (std::getline(filename, line))
    {
        stringstream ss(line); //break up words (split by commas) in line

        //get line information and store into vector
        std::getline(ss, temp_isbn_str, ',');
        std::getline(ss, language, ',');
        std::getline(ss, type, ',');
        dataset.push_back(line);
    }
    filename.close(); //close file
    return dataset;
}


//function that conducts linear search given two input vectors: newBooks and requestedBooks
int linearSearch (const std::vector<std::string> a, const std::vector<std::string> x)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < a.size(); i++) //search new books
    {
        for (unsigned int j = 0; j < x.size(); j++) //search requested books
        {
            if (a[i] == x[j]) //if books match
            {
                count++; //add count
            }
        }
    }
    return count;
}


//function that conducts binary search given two input vectors: newBooks and requestedBooks from 0 to newBooks size
int binarySearch (const std::vector<std::string>& a, const std::vector<std::string>& x)
{
    unsigned int count = 0;
    unsigned int i = 0, j = a.size(); //i = left, j = right
    while (i < j)
    {
        unsigned int m = (i + j)/2; //middle
        if (x[i] > a[m])
        {
            i = m + 1; //go right
        }
        else if (x[i] < a[m])
        {
            j = m; //go left
        }
        else //if books match
        {
            count++; //add count
        }
    }
    return count;
}


int main(int argc, char *argv[])
{
    //open command line argument files
    std::string newBooksFile(argv[1]);
    std::string requestedFile(argv[2]);
    std::ofstream foundFile; //creates found file from third argument in command line
    foundFile.open(argv[3]);

    //call readinDataset for newBooks and requestedBooks
    std::vector<std::string> newBooks = readinDataset(newBooksFile);
    std::vector<std::string> requestedBooks = readinDataset(requestedFile);

    std::cout << "Choice of search method ([l]inear, [b]inary)?\n";

    while (true)
    {
        //user input
        char choice;
        std::cin >> choice;

        //start timer
        //std::chrono::high_resolution_clock::time_point start;
        //start = std::chrono::high_resolution_clock::now();

        if (choice == 'l')
        {
            //start timer
            std::chrono::high_resolution_clock::time_point start;
            start = std::chrono::high_resolution_clock::now();

            //call linearSearch function
            int result = linearSearch(newBooks, requestedBooks);
            foundFile << result << "\n"; //write number of matched books to output file

            //end timer
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();

            std::cout << "CPU time: " << elapsed_us << " microseconds." << std::endl;

            break;
        }

        else if (choice == 'b')
        {
            //start timer -> include sorting
            std::chrono::high_resolution_clock::time_point start;
            start = std::chrono::high_resolution_clock::now();

            //sort book vectors
            std::sort(newBooks.begin(), newBooks.end());
            std::sort(requestedBooks.begin(), requestedBooks.end());

            //start timer -> don't include sorting
            //std::chrono::high_resolution_clock::time_point start;
            //start = std::chrono::high_resolution_clock::now();

            //call binarySearch function
            int result = binarySearch(newBooks, requestedBooks);
            foundFile << result << "\n"; //write number of matched books to output file

            // end timer
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();

            std::cout << "CPU time: " << elapsed_us << " microseconds." << std::endl;

            break;
        }

        else //if user inputs anything other than "l" or "b"
        {
            std::cout << "Incorrect choice\n";
        }
    }
    return 0;
}

