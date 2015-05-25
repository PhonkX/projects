//Approximative method
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node
{
	vector <int > edges;
	int color;
	int number;
	Node(int k)
	{
		number = k;
		color = -1;
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
			f >> i >> j;
			bool edgeIsWritten = false;
			for (auto x : nodes[i].edges)
			{
				if (x == j)
				{
					edgeIsWritten = true;
					break;
				}
			}
			if (!edgeIsWritten)
			{
				nodes[i].edges.push_back(j);
				if (type == 0)
					nodes[j].edges.push_back(i);
			}
		}
	}
	void colorizing()
	{
		vector<Node> sortNodes(nodes);
		sort(sortNodes.begin(), sortNodes.end(), [&](Node &x, Node &y) {return y.edges.size() < x.edges.size(); });
	/*	for (auto x : nodes)
			cout << x.number << " ";*/
		int curColor = 1;
		int paintCount = 0;
		while (true)
		{
			paintCount = 0;
			for (auto &v : sortNodes)
			{
				if (v.color == -1)
				{
					bool isSameColor = false;
					for (auto e : v.edges)
					{ 
						if (nodes[e].color == curColor)
							isSameColor = true;
					}
					if (!isSameColor)
					{
						v.color = curColor;
						nodes[v.number].color = curColor;
						paintCount++;
					}
				}
			}
			if (!paintCount)
				break;
			curColor++;
		}
		cout << curColor-1 << endl;
	}
	void show()
	{
		for (auto v : nodes)
			cout << v.number << ": " << v.color << endl;

	}

	
};

int main()
{
	Graph gr("graph.txt");
	gr.colorizing();
	gr.show();
	return 0;
}