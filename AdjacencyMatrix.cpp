#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix() {
    indexCounter = 0;

    for(int i = 0; i < 10000; i++) {
        for(int j = 0; j < 10000; j++) {
            matrix[i][j] = 0;
        }
    }
}

void AdjacencyMatrix::InsertEdge(int firstBookID, int secondBookID) {
    if(firstBookID == secondBookID)
        return;

    if(indexMatcher.count(firstBookID) == 0) {
        indexMatcher.emplace(firstBookID, indexCounter);
        reverseIndexMatcher.emplace(indexCounter, firstBookID);
        indexCounter++;
    }
    if(indexMatcher.count(secondBookID) == 0) {
        indexMatcher.emplace(secondBookID, indexCounter);
        reverseIndexMatcher.emplace(indexCounter, secondBookID);
        indexCounter++;
    }

    matrix[indexMatcher[firstBookID]][indexMatcher[secondBookID]]++;
    matrix[indexMatcher[secondBookID]][indexMatcher[firstBookID]]++;
}

void AdjacencyMatrix::InsertEdgeList(unordered_map<int, vector<int>>& reviews)
{
    for (auto iter = reviews.begin(); iter != reviews.end(); ++iter){
        for (int i = 0; i < iter->second.size(); i++) {
            for (int j = i + 1; j < iter->second.size(); j++) {
                InsertEdge(iter->second[i], iter->second[j]);
            }
        }
    }
}

int AdjacencyMatrix::GetWeight(int firstBookID, int secondBookID) {
    return matrix[indexMatcher[firstBookID]][indexMatcher[secondBookID]];
}
    
void AdjacencyMatrix::GetAdjacentNodes(int bookID, vector<int> userInput, unordered_map<int, int>& allNodes) {
    for(int i = 0; i < 10000; i++) {
        //Check if current book is one of user input, don't update similarity score if it is
        if(find(userInput.begin(), userInput.end(), reverseIndexMatcher[i]) == userInput.end() 
                                                 && matrix[indexMatcher[bookID]][i] != 0) {
            if (allNodes.count(reverseIndexMatcher[i]) == 0)
                allNodes.emplace(reverseIndexMatcher[i], matrix[indexMatcher[bookID]][i]);
            else
                allNodes[reverseIndexMatcher[i]] += matrix[indexMatcher[bookID]][i];
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
