#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Book.h"
#include "AdjacencyMatrix.h"
#include "MinHeap.h"

void readBooks(std::unordered_map<long, Book>& books,
               std::unordered_map<int, long>& bookMapper, const std::string& file);

void readReviews(std::unordered_map<int, std::vector<int>>& reviews,
                 const std::string& file);

int main() {

    // Key: bookID; Value: isbn
    std::unordered_map<int, long> bookMapper;

    // Key: isbn; Value: Book object that stores info
    std::unordered_map<long, Book> books;
    readBooks(books, bookMapper, "../data/books.csv");

    // Key: User id; Value: Vector of Liked Books (Books rated 4 and up)
    std::unordered_map<int, std::vector<int>> reviews;
    readReviews(reviews, "../data/ratings.csv");

    // Set up Adjacency Matrix
    AdjacencyMatrix* matrix = new AdjacencyMatrix();
    for (auto& review : reviews) {
        for (int i = 0; i < review.second.size(); i++) {
            for (int j = i + 1; j < review.second.size(); j++) {
                matrix->InsertEdge(bookMapper[review.second.at(i)],
                                   bookMapper[review.second.at(j)]);
            }
        }
    }
    //matrix->PrintMatrix();

    /*
    int numOfBooks = 0;
    std::cout << "Number of books to enter:" << std::endl;
    std::cin >> numOfBooks;

    long isbn;
    std::vector<int> userInput;
    std::cout << "Please enter the isbn of your favorite books:" << std::endl;
    for (int i = 0; i <numOfBooks; i++) {

        std::cin >> isbn;
        // If isbn exists and is valid
        if (books.count(isbn) == 1) {
            userInput.push_back(isbn);
            std::cout << "ISBN FOUND!" << std::endl;
        }
        else {
            std::cout << "ISBN NOT FOUND!" << std::endl;
        }
    }


    */


    //contains bookID of user's favorite books
    //edit this to see different result
    //currently has Hunger Game (ID: 1) and Harry Potter (ID: 2)
    //std::vector<int> userInput = {439023483, 2};
    //MinHeap heap(userInput, reviews);

    //Just need to edit this function to display book title instead of ID's
    //currently recommends 3 books
    //heap.recommendBooks(3);

    return 0;
}

void readBooks(std::unordered_map<long, Book>& books,
               std::unordered_map<int, long>& bookMapper, const std::string& file) {

    std::ifstream in(file, std::ifstream::in);

    if (in.is_open()) {

        std::string line;
        getline(in, line);  // Removes headers from file

        while (getline(in, line)) {

            std::istringstream iss(line);
            std::string discard;

            std::string bookID;
            getline(iss, bookID, ',');

            // Discard next 4 values
            for (int i = 0; i < 4; i++)
                getline(iss, discard, ',');

            std::string isbn;
            getline(iss, isbn, ',');

            // Discard next value
            getline(iss, discard, ',');

            // Checking for commas with quotes (",")
            std::string author;
            if (iss.peek() == '\"') {
                iss.get();  // Discards quote to access author
                getline(iss, author, '\"');
                iss.get();  // Discards next comma to prevent errors
            }
            else
                getline(iss, author, ',');

            std::string year;
            getline(iss, year, ',');

            // Discard next value; check for comma with quotes (",")
            if (iss.peek() == '\"') {
                iss.get();  // Discards quote to access value

                // Check for nested quotes in title
                if (iss.peek() != '\"') {
                    getline(iss, discard, '\"');
                    iss.get();  // Discards next comma to prevent errors
                }
                else {
                    getline(iss, discard, ',');
                }
            }
            else
                getline(iss, discard, ',');

            // Checking for commas with quotes (",")
            std::string title;
            if (iss.peek() == '\"') {
                iss.get();  // Discards quote to access title
                getline(iss, title, '\"');
                iss.get();  // Discards next comma to prevent errors
            }
            else
                getline(iss, title, ',');

            // Discard next 10 values
            for (int i = 0; i < 10; i++)
                getline(iss, discard, ',');

            std::string cover;
            getline(iss, cover, ',');

            // Discard last value
            getline(iss, discard);

            // Check isbn and year; skip if there is no isbn
            if (isbn == "")
                continue;

            if (year == "")
                year = "0";

            Book toAdd(std::stoi(bookID), std::stoi(year), author, title, cover);
            books[std::stol(isbn)] = toAdd;
            bookMapper[std::stoi(bookID)] = std::stol(isbn);
        }

        in.close();
    }
}

void readReviews(std::unordered_map<int, std::vector<int>>& reviews,
                 const std::string& file) {

    std::ifstream in(file, std::ifstream::in);

    if (in.is_open()) {

        std::string line;
        getline(in, line);  // Remove headers from file

        while (getline(in, line)) {

            std::istringstream iss(line);

            std::string userID;
            getline(iss, userID, ',');

            std::string bookID;
            getline(iss, bookID, ',');

            std::string rating;
            getline(iss, rating);

            // Filtering out ratings lower than 4
            if (std::stoi(rating) > 3) {
                reviews[std::stoi(userID)].push_back(std::stoi(bookID));
            }
        }

        in.close();
    }
}
