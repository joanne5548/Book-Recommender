#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;

class AdjacencyMatrix {
    int matrix[10000][10000];
    unordered_map<int, int> indexMatcher;
    unordered_map<int, int> reverseIndexMatcher;
    int indexCounter;
public:
    AdjacencyMatrix();
    void InsertEdge(int firstISBN, int secondISBN);
    int GetWeight(int firstISBN, int secondISBN);
    void GetAdjacentNodes(int isbn, unordered_map<int, int>& allNodes);
    void PrintMatrix();
};