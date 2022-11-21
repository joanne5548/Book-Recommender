#include <iostream>
#include <unordered_map>
using namespace std;

class AdjacencyMatrix {
    int matrix[10000][10000];
    unordered_map<int, int> indexMatcher;
    int indexCounter;
public:
    AdjacencyMatrix();
    void InsertEdge(int firstISBN, int secondISBN);
};