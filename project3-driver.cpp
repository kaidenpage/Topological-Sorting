#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "digraph.h"

const string INPUT_FILE("graph.txt");

int main()
{
	//Read in directed graph from file
	DigraphMatrix g(INPUT_FILE);

	try
	{
		//Perform topological sorting
		vector<int> sort = g.topologicalSort();

		//Print out vertices
		for (int v : sort)
			cout << v << ' ';
		cout << endl;
	}
	catch (exception& ex)
	{
		cout << "Cycle detected in directed graph" << endl;
	}
	system("pause");
	return 0;
}
