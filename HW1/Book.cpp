// Mindy Mohr
// 917425752
// Book.cpp

#include "Book.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

std::string line;

//int argc, char *argv[]

int main()
{
    //reading in files
    ifstream newBooks("newbooks.dat");
    if (newBooks.is_open())
    {
       std::cout << "open\n";
       return -1;
    }
    if (!newBooks.is_open())
    {
        std::cout << "file could not open\n" << endl;
        return 0;
    }
    

    std::string language;
    std::string type;
    std::string isbn_temp_str;
    int isbn;

    while (std::getline(newBooks, line))
    {
        stringstream ss(line);
        getline(ss, isbn_temp_str, ',');
        isbn = stoi(isbn_temp_str); //convert from str to int
        std::getline(ss, language, ',');
        //stringstream(line) >> language;
        std::getline(ss, type, ',');
        //newBook = Book(isbn, language, type);
        //newBook.push_back(Book);
        std::cout << isbn << language << type << endl;
    }

    newBooks.close();
                    
 };
