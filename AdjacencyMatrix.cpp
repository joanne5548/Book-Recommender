#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix() {
    indexCounter = 0;

    for(int i = 0; i < 10000; i++) {
        for(int j = 0; j < 10000; j++) {
            matrix[i][j] = 0;
        }
    }
}

void AdjacencyMatrix::InsertEdge(long firstISBN, long secondISBN) {
    if(firstISBN == secondISBN)
        return;

    if(indexMatcher.count(firstISBN) == 0) {
        indexMatcher.emplace(firstISBN, indexCounter);
        reverseIndexMatcher.emplace(indexCounter, firstISBN);
        indexCounter++;
    }
    if(indexMatcher.count(secondISBN) == 0) {
        indexMatcher.emplace(secondISBN, indexCounter);
        reverseIndexMatcher.emplace(indexCounter, secondISBN);
        indexCounter++;
    }

    matrix[indexMatcher[firstISBN]][indexMatcher[secondISBN]]++;
    matrix[indexMatcher[secondISBN]][indexMatcher[firstISBN]]++;
}

int AdjacencyMatrix::GetWeight(long firstISBN, long secondISBN) {
    return matrix[indexMatcher[firstISBN]][indexMatcher[secondISBN]];
    
void AdjacencyMatrix::GetAdjacentNodes(long isbn, unordered_map<long, long>& allNodes) {
    for(int i = 0; i < 10000; i++) {
        if(matrix[indexMatcher[isbn]][i] != 0) {
            if (allNodes.count(reverseIndexMatcher[i]) == 0)
                allNodes.emplace(reverseIndexMatcher[i], matrix[indexMatcher[isbn]][i]);
            else
                allNodes[reverseIndexMatcher[i]] += matrix[indexMatcher[isbn]][i];
        }
    }
}

void AdjacencyMatrix::PrintMatrix() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
