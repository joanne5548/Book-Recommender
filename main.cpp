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
                 std::unordered_map<int, long>& bookMapper, AdjacencyMatrix* matrix,
                 const std::string& file);

int main() {

    // Key: bookID; Value: isbn
    std::unordered_map<int, long> bookMapper;

    // Key: isbn; Value: Book object that stores info
    std::unordered_map<long, Book> books;
    readBooks(books, bookMapper, "../data/books.csv");

    // Set up Adjacency Matrix
    AdjacencyMatrix* matrix = new AdjacencyMatrix();

    // Key: User id; Value: Vector of Liked Books (Books rated 4 and up)
    std::unordered_map<int, std::vector<int>> reviews;

    // Create matrix as each value becomes available
    readReviews(reviews, bookMapper, matrix, "../data/ratings_trunicated.csv");

    cout << "Welcome to Book Recommender!" << endl;
    cout << "First, enter ISBN of your favorite books." << endl;
    cout << "If you are done, enter \"done\"." << endl;

// Reads in ISBNs.
    string input;
    int inputNum;
    vector<long> isbns;

    while(input.compare("done") != 0) {
        bool isADigit = true;
        cin >> input;
        for(int k = 0; k < input.size(); k++) {
            if(!isdigit(input.at(k))) {
                isADigit = false;
            }
        }

        if(isADigit) {
            inputNum = stol(input);
            isbns.push_back(inputNum);
        }
    }

// When done is entered, asks user for how many books they would like to see.
    cout << endl << "Thank you!" << endl;
    cout << "Now, tell us how many books you would like us to recommend." << endl;

    int numOfBooks;
    cin >> numOfBooks;

    cout << endl << "Thanks! Picking books for you ..." << endl;

//Calculate the whole thing with matrix and heap

    cout << "Recommended books are:" << endl;

//display the result

    cout << endl << "Thank you for using Fish Against Education Book Recommender!" << endl;

    for (int j = 0; j < 2; ++j)
    {
        for (int i = 0; i < 70; ++i)
            cout << "*";
        cout << endl;
    }

    //contains bookID of user's favorite books
    //edit this to see different result
    //currently has Hunger Game (ID: 1) and Harry Potter (ID: 2)
    //std::vector<int> userInput = {1, 2};
    //MinHeap heap(userInput, reviews);

    //Just need to edit this function to display book title instead of ID's
    //currently recommends 3 books
    //heap.recommendBooks(3);

    delete matrix;
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
                 std::unordered_map<int, long>& bookMapper,
                 AdjacencyMatrix* matrix, const std::string& file) {

    std::ifstream in(file, std::ifstream::in);

    if (in.is_open()) {

        std::string line;
        getline(in, line);  // Remove headers from file

        while (getline(in, line)) {

            std::istringstream iss(line);

            std::string tempUser;
            getline(iss, tempUser, ',');
            int userID = std::stoi(tempUser);

            std::string tempBook;
            getline(iss, tempBook, ',');
            int bookID = std::stoi(tempBook);

            std::string rating;
            getline(iss, rating);

            // Don't process reviews on books with no isbn
            if (bookMapper.count(bookID) != 1)
                continue;

            // Filtering out ratings lower than 4
            if (std::stoi(rating) == 5)
                reviews[userID].push_back(bookID);
            else
                continue;

            // Insert into adj. matrix
            // Don't insert if there is only one book in the vector
            int vectSize = reviews[userID].size();
            if (vectSize == 1)
                continue;

            for (int i = 0; i < vectSize - 1; i++) {
                matrix->InsertEdge(reviews[userID].at(vectSize - 1), reviews[userID].at(i));
            }
        }

        in.close();
    }
}
