#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class AdjacencyMatrix {
    int matrix[10000][10000];
    unordered_map<int, int> indexMatcher;
    unordered_map<int, int> reverseIndexMatcher;
    int indexCounter;
public:
    AdjacencyMatrix();
    void InsertEdge(int firstBookID, int secondBookID);
    void InsertEdgeList(unordered_map<int, vector<int>>& reviews);
    int GetWeight(int firstBookID, int secondBookID);
    void GetAdjacentNodes(int bookID, vector<int> userInput, unordered_map<int, int>& allNodes);
    void PrintMatrix();
};
