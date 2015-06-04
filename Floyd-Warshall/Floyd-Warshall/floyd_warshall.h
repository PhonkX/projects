#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Node
{
	vector <pair <int, double> > edges;
	int parent;
	int number;
	double distance;
	Node(int k) : number(k), parent(-1) {}
};


class Graph
{
	vector<Node> nodes;
	vector<vector<double> > distance;
	vector<vector<int> > next;
public:
	Graph(int N);
	Graph(const string& path);
	void Floyd_Warshall();
	void show();
private:
	double sum(double a, double b);
	void path(int i, int j);
};
