#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <fstream>
#include <stack>
using namespace std;

class DigraphMatrix
{
private:
	// Dynamic Array of int to represent the graph as an adjacency matrix
	int **graphAdjacencyMatrix;
	// numVertices holds number of vertices of the graph (n)
	// numEdges holds number of edges of the graph (m)
	int numVertices, numEdges;
public:
	/*
	parameter constructor of DigraphMatrix class it takes the name of input file
	read it and store it's data into graphAdjacencyMatrix
	*/
	DigraphMatrix(const string& filename);
	/*
	this function aplay Topological sort for a directed acyclic graph
	if int is acyclic graph but if it is cyclic graph it throw Exception
	*/
	vector<int> topologicalSort() const;
	/*
	this function check if all vertices are discovered or not
	if all discoverd it return true
	otherwise it return false
	*/
	bool isAllVerticesDiscoveredOrNot(bool *)const;

	/*
	this function traverse over all graph vertices and return 
	the lowest un discovered vertix ID
	it return lowest un discovered vertix Id if all vertices are discovered
	it return -1
	*/
	int lowestUndiscoveredVetrixId(bool*) const;

	/*
	this function return lowest neighnor of specific ID
	it return lowest neighnor un discovered for gien ID
	if all neighbors are discovered it return -1
	*/
	int getLowestUndiscoveredNeighbor(int, bool*)const;

};
#endif