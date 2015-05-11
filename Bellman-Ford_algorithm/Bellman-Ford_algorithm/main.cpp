#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

struct Node
{
	vector <pair <int, double> > edges;
	int parent;
	int number;
	double distance;
	Node(int k)
	{
		number = k;
		parent = -1;
	}
};


class Graph
{
	vector<Node> nodes;
public:
	Graph(int N)
	{
		nodes.reserve(N);
		for (int i = 0; i < N; ++i)
			nodes.push_back(Node(i));
	}
	Graph(const string& path)
	{
		ifstream f(path);
		if (!f)
			throw runtime_error("File doesn't exist");
		int n, type;
		f >> n >> type; //type == 0 - not oriented graph, 1 - oriented
		nodes.reserve(n);
		for (int i = 0; i < n; ++i)
			nodes.push_back(Node(i));
		int i, j, w;
		while (!f.eof())
		{
			f >> i >> j >> w;
			bool edgeIsWritten = false;
			for (auto x : nodes[i].edges)
			{
				if (x.first == j)
				{
					edgeIsWritten = true;
					break;
				}
			}
			if (!edgeIsWritten)
			{
				nodes[i].edges.push_back(make_pair(j, w));
				if (type == 0)
					nodes[j].edges.push_back(make_pair(i, w));
			}
		}
	}
	bool Bellman_Ford_algorithm(int startNode)
	{
		bool smthChanged = false;
		for (int i = 0; i < nodes.size(); ++i)
		{
			nodes[i].distance = numeric_limits<double>::infinity();
		}
		nodes[startNode].distance = 0;
		for (int i = 1; i <= nodes.size(); ++i)
		{
			smthChanged = false;
			for (auto a : nodes)
			{
				for (auto b : a.edges)
				{
					if (a.distance != numeric_limits<double>::infinity() && a.distance + b.second < nodes[b.first].distance)
					{
						nodes[b.first].distance = a.distance + b.second;
						nodes[b.first].parent = a.number;
						smthChanged = true;
					}
				}
			}
			if (!smthChanged)
					break;
		}
		for (auto a : nodes)
		{
			for (auto b : a.edges)
			{
				if (a.distance != numeric_limits<double>::infinity() && a.distance + b.second < nodes[b.first].distance)
				{
					nodes[b.first].distance = a.distance + b.second;
					nodes[b.first].parent = a.number;
					smthChanged = true;
				}
			}
			if (smthChanged)
				return false;
		}
		return true;
	}
	void show()
	{
		if (Bellman_Ford_algorithm(0))
		{
			for (auto x : nodes)
			{
				if (x.distance < numeric_limits<double>::infinity())
				{
					cout << "Number: " << x.number << "; parent: " << x.parent << "; distance: " << x.distance << endl;
					cout << "Path:" << endl;
					cout << x.number;
					int current = x.parent;
					while (current != -1)
					{
						cout << "<-" << current;
						current = nodes[current].parent;
					}
				}
				cout << endl;
			}
			cout << endl;
		}
		else
			cout << "There is negative cycle." << endl;
	}
};

int main()
{
	Graph gh("graph.txt");
	gh.show();
	return 0;
}