#include "floyd_warshall.h"

Graph::Graph(int N)
{
	nodes.reserve(N);
	for (int i = 0; i < N; ++i)
		nodes.push_back(Node(i));
}
Graph::Graph(const string& path)
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
void Graph::Floyd_Warshall()
{
	int n = nodes.size();
	distance.resize(n);
	next.resize(n);
	for (int i = 0; i < n; ++i)
	{
		distance[i].resize(n);
		next[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				distance[i][j] = 0;
			else
				distance[i][j] = numeric_limits<double>::infinity();


			next[i][j] = -1;
		}
	}
	for (auto v : nodes)
	{
		for (auto e : v.edges)
		{
			distance[v.number][e.first] = e.second;
			next[v.number][e.first] = e.first;
		}
	}

	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (sum(distance[i][k], distance[k][j]) < distance[i][j])
				{
					distance[i][j] = distance[i][k] + distance[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
}
void Graph::show()
{
	int n = nodes.size();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (distance[i][j] == numeric_limits<double>::infinity())
				cout << setw(5) << "-";
			else cout << setw(5) << distance[i][j];
			//cout << " ";
		}
		cout << endl;
		cout << endl;
	}
	cout << endl;
	cout << endl;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			path(i, j);
			cout << endl;
		}
	}
}
double Graph::sum(double a, double b)
{
	if (a == numeric_limits<double>::infinity())
		return a;
	else
	{
		if (b == numeric_limits<double>::infinity())
			return b;
		else return a + b;
	}
}
void Graph::path(int i, int j)
{
	if (next[i][j] == -1)
	{
		cout << "No path.";
		return;
	}
	while (i != j)
	{
		cout << i << "<-";
		i = next[i][j];
	}
	cout << j;
}