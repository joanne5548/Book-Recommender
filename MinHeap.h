#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class MinHeap{
private:
    vector<int> heap;
    unordered_map<int, int> ratingScore;

    void insert(int bookID);
    int pop();
    int min();
    void print();
    vector<int> returnBooks();

public:
    MinHeap() {}
    MinHeap(unordered_map<int, int> _ratingScore);
    MinHeap(vector<int> userInput,
            unordered_map<int, vector<int>> reviews);

    vector<int> recommendBooks(int bookNum);
};

