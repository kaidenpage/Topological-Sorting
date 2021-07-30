#include "digraph.h"

DigraphMatrix::DigraphMatrix(const string& filename){
	// create object of  ifstream for given file name
	ifstream fileStream(filename);
	// ensure that given file is opened successfully
	// if not display error message and exit the program
	if (!fileStream.is_open()){
		cout << "Can not open " << filename<<" or file not exist" << endl;
		exit(1);
	}
	// read given file Data
	// first line contains number of vertices and edges of the graph (n and m)
	// read number of vertices (n)
	fileStream >> this->numVertices;
	// read number of edges (m)
	fileStream >> this->numEdges;
	// create dynamic Array of int to represent the graph as an adjacency matrix 
	this->graphAdjacencyMatrix = new int*[this->numVertices];
	for (int i = 0; i < this->numVertices; i++){
		this->graphAdjacencyMatrix[i] = new int[this->numVertices];
	}
	// initialize Graph Adjacency Matrix with 0
	for (int i = 0; i < this->numVertices; i++){
		for (int j = 0; j < this->numVertices; j++)
			this->graphAdjacencyMatrix[i][j] = 0;
	}
	int v1, v2;
	// read graph edges from given file
	for (int i = 0; i < this->numEdges; i++){
		// get v1
		fileStream >> v1;
		// get v2
		fileStream >> v2;
		// set graphAdjacencyMatrix[v1][v2] to 1
		// if v1 and v2 are not valid indeces for graphAdjacencyMatrix
		// print error message and exit the program
		if (v1 < 0 || v1 >= this->numVertices || v2 < 0 || v2 >= this->numVertices){
			cout << "Illegal Values for [ v1: " << v1 << ", v2:  " << v2 <<" ] \n";
			exit(1);
		}
		this->graphAdjacencyMatrix[v1][v2] = 1;
	}
	// close given file
	fileStream.close();
}


vector<int> DigraphMatrix::topologicalSort() const{
	// store vertix neighbors in stack
	stack<int> stackOfNeighbors;
	// dynamic boolean matrix for discovered vertices
	bool *discoveredVetrices = new bool[this->numVertices];
	// init all graph vertices as not discovered yet
	for (int i = 0; i < this->numVertices; i++)
		discoveredVetrices[i] = false;
	// vector to hold sorted vertices
	vector<int> sortVertices;
	// hold lowest undiscoverd id
	int lowestUndiscoverdId;
	// hold lowest Undiscoverd neighbor for loswet vertix id
	int lowestUndiscoverdNeighbor;
	// while there is vertix need to be discovered
	while (true){
		// exit loop if all graph vetrices are discoverd
		if (this->isAllVerticesDiscoveredOrNot(discoveredVetrices))
			break;
		// if stack of neighbors is empty then get lowest
		// undiscoverd id from graph vertices
		// if not then get top id in stack of neighbors ( lowest neighbor id)
		if (stackOfNeighbors.empty()){
			lowestUndiscoverdId = this->lowestUndiscoveredVetrixId(discoveredVetrices);
			// if returned id is -1 this means all vertices are discoverded
			// in this case continue for next iteration to break the loop
			if (lowestUndiscoverdId == -1)
				continue;
			// else push this Id into stack Of Neighbors 
			stackOfNeighbors.push(lowestUndiscoverdId);
		}
		else{
			lowestUndiscoverdId = stackOfNeighbors.top();
		}
		// set current vertix as discoverd
		discoveredVetrices[lowestUndiscoverdId] = true;
		// get lowest Neighbor of lowestUndiscoverdId
		// if returnedvalue is -1
		// this means this id has no neighbors needed to discovered so add it
		// to sorted vertices  vector
		// and remove it from stack Of Neighbors 
		lowestUndiscoverdNeighbor = this->getLowestUndiscoveredNeighbor(lowestUndiscoverdId, discoveredVetrices);
		if (lowestUndiscoverdNeighbor == -1){
			sortVertices.push_back(lowestUndiscoverdId);
			stackOfNeighbors.pop();
		}
		else{
			// push it into stack Of Neighbors
			stackOfNeighbors.push(lowestUndiscoverdNeighbor);
		}

	}
	// reverse  sort Vertices vector
	vector<int> sort;
	for (int i = sortVertices.size()-1; i >= 0; i--){
		sort.push_back(sortVertices[i]);
	}
	//reverse(sortVertices.begin(), sortVertices.end());
	// check if the graph is cyclic or not
	// if it cyclic then throw exception
	if (sort.size() != this->numVertices){
		throw std::exception();
	}
	// if the graph is a cyclic graph then return vector of sorted vertices
	return sort;
}


/*
this function return lowest neighnor of specific ID
it return lowest neighnor un discovered for gien ID
if all neighbors are discovered it return -1
*/
int DigraphMatrix::getLowestUndiscoveredNeighbor(int lowestUndiscoverdId, bool* discoveredVetrices)const{
	int i = 0;
	while(i < this->numVertices){
		if (this->graphAdjacencyMatrix[lowestUndiscoverdId][i] == 1 && discoveredVetrices[i] == false)
			return i;
		i++;
	}
	return -1;
}

/*
this function check if all vertices are discovered or not
if all discoverd it return true
otherwise it return false
*/
bool DigraphMatrix::isAllVerticesDiscoveredOrNot(bool *discoveredVetrices)const{
	int i = 0;
	while(i < this->numVertices){
		if (discoveredVetrices[i] == false)
			return false;
		i++;
	}

	return true;
}

/*
this function traverse over all graph vertices and return
the lowest un discovered vertix ID
it return lowest un discovered vertix Id if all vertices are discovered
it return -1
*/
int DigraphMatrix::lowestUndiscoveredVetrixId(bool * discoveredVetrices) const{
	int i = 0;
	while(i < this->numVertices){
		if (discoveredVetrices[i] == false)
			return i;
		i++;
	}
	return -1;
}


