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
    void InsertEdge(long firstISBN, long secondISBN);
    int GetWeight(long firstISBN, long secondISBN);
    void GetAdjacentNodes(long isbn, unordered_map<long, long>& allNodes);
    void PrintMatrix();
};
