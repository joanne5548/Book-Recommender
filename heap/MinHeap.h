#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class MinHeap{
private:
    vector<int> heap;
    //can't contain the inputted books itself
    unordered_map<int, int> ratingScore;

public:
    MinHeap() {}
    MinHeap(unordered_map<int, int> _ratingScore);

    //is bookID going to be string?
    void insert(int bookID);
    int pop();
    int min();
    void print();
    int* returnBooks();

    //ratingScore contains the similarity score relative to user's favorite book
    //map of bookID (int), similarity score (int)
    //method of calculation: run through the list of user reviews
    //for every user that liked the inputted books,
    //++1 similarity score for all the other books the user liked
    //repeat this for every book inputted
    int* recommendBooks(int bookNum);
};

