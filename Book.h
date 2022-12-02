#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

struct Book {

    int bookID;
    int year; // Negative years exist in the data set
    std::string author;
    std::string title;
    std::string cover;

    Book();
    Book(int bookID, int year, std::string author, std::string title,
         std::string cover);

};

Book::Book() {
    bookID = 0;
    year = 0;
    std::string author = "";
    std::string title = "";
    std::string cover = "";
}

Book::Book(int bookID, int year, std::string author, std::string title,
           std::string cover) {
    this->bookID = bookID;
    this->year = year;
    this->author = author;
    this->title = title;
    this->cover = cover;
}

