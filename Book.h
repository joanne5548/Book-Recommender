#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

struct Book {

    unsigned long long isbn;
    int year; // Negative years exist in the data set
    std::string author;
    std::string title;
    std::string cover;

    Book();
    Book(unsigned long long isbn, int year, std::string author, std::string title,
         std::string cover);

};

Book::Book() {
    isbn = 0;
    year = 0;
    std::string author = "";
    std::string title = "";
    std::string cover = "";
}

Book::Book(unsigned long long isbn, int year, std::string author, std::string title,
           std::string cover) {
    this->isbn = isbn;
    this->year = year;
    this->author = author;
    this->title = title;
    this->cover = cover;
}

