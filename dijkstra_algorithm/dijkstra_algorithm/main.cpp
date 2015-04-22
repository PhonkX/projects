#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

enum Colors
{
	white, grey, black
};

struct Node
{
	vector <pair <int, double> > edges;
	int parent;
	int color;
	int number;
	double distance;
	Node(int k)
	{
		number = k;
		color = white;
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
	void Dijkstra(int startNumber)
	{
		for (int i = 0; i < nodes.size(); ++i)
		{
			nodes[i].distance = numeric_limits<double>::infinity();
		}
		nodes[startNumber].distance = 0;
		Node current = nodes[startNumber];
		while (true)
		{
			int curPosition = minDistNode();
			if (curPosition == -1)
				break;
			current = nodes[curPosition];
			for (auto x : current.edges)
			{
				if (current.distance + x.second < nodes[x.first].distance)
				{
					nodes[x.first].distance = current.distance + x.second;
					nodes[x.first].parent = current.number;
				}
			}
			nodes[current.number].color = black;
		}
		show();
	}
	void show()
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
private:
	int minDistNode()
	{
		double minD = numeric_limits<double>::infinity();
		int minV = -1;
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (nodes[i].color == white)
			{
				if (nodes[i].distance < minD)
				{
					minD = nodes[i].distance;
					minV = i;
				}
			}
		}
		return minV;
	}
};

int main()
{
	Graph gh("graph.txt");
	gh.Dijkstra(0);
	return 0;
}