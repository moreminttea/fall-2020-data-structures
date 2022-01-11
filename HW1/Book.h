// Mindy Mohr
// 917425752
// Book.h

#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>
#include <vector>

class Book
{
    private:
    protected:
    public:
        int isbn;
        std::string language;
        std::string type;
        Book(int isbn, std::string language, std::string type);

        std::vector<Book*> newBooks[100]; //list of new books
        std::vector<Book*> requestedBooks[100]; //list of requested books
};

#endif /* _BOOK_H_ */
