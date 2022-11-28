# FishAgainstEducation


For Sam's Adjacency Matrix:


AdjacencyMatrix():

The constructor. It takes no parameters, just makes an empty 10000x10000 graph.


void InsertEdge(int firstISBN, int secondISBN):

Just takes two intergers and places them onto the map.


int GetWeight(int firstISBN, int secondISBN):

Returns the weight between two books.


void GetAdjacentNodes(int isbn, unordered_map<int, int>& allNodes):

Mutates a given unordered map to return all of the adjacent books (with the key being the ISBN) and the value as the weight of the edge.
