#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <queue>

using namespace std;

class FileNotExists : public exception
{
	FileNotExists() : exception(){}
};

enum Colors
{
	white, grey, black
};

class Node
{
public:
	int n;
	int p = -1;
	vector<int> edges;
	int color;
	Node(int k)
	{
		n = k;
		color = white;
	}
};

class Graph
{
	vector<Node> nodes;
	vector<Node> sorted;
public:
	Graph(int N)
	{
		nodes.reserve(N);
		for (int i = 0; i < N; ++i)
			nodes.push_back(i);
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
			nodes.push_back(i);
		int i, j;
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
	void show()
	{
		for (auto x : nodes)
		{
			cout << x.n << ": " << x.color << "   :";
			for (auto i : x.edges)
				cout << i << ": " << nodes[i].color << "," << nodes[i].p << "   ";
			cout << endl;
		}
	}
	void DFS()
	{
		sorted.clear();
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (nodes[i].color == white)
				DFS1(i);
			else if (nodes[i].color == grey)
			{
				cout << "There is cycle." << endl;
				return;
			}
		}
	}
	void showSorted()
	{
		DFS1(0);
		for (auto x = sorted.rbegin(); x != sorted.rend(); ++x)
			cout << x->n << " " << endl;
		cout << endl;
	}
	void BFS()
	{

		for (int i = 0; i < nodes.size(); ++i)
		{
			if (nodes[i].color == white)
				BFS1(i);
		}
	}
	void showPathes()
	{
		for (auto x : nodes)
		{
			int cur = x.n;
			cout << cur;
			while (cur != -1)
			{
				
				cur = nodes[cur].p;cout << "<-" << cur;
			}
			cout << endl;
		}
	}
private:
	void DFS1(int i)
	{
		static bool f = false;
		if (f)
		{
			cout << "There is cycle." << endl;
			return;
		}
		nodes[i].color = grey;
		for (auto x : nodes[i].edges)
		{
			if (nodes[x].color == white)
				DFS1(x);
			else if (nodes[x].color == grey)
				f = true;
		}

		nodes[i].color = black;
		sorted.push_back(nodes[i]);
	}
	void BFS1(int i)
	{
		queue<int> q;
		nodes[i].color = black;
		q.push(i);
		while (!q.empty())
		{
			int j = q.front();
			q.pop();
			for (auto k : nodes[j].edges)
			{
				if (nodes[k].color == white)
				{
					nodes[k].color = black;
					nodes[k].p = j;
					q.push(k);
				}
			}
		}
	}
};

int main()
{
	/*string path;
	cout << "Enter file path:" << endl;
	cin >> path;
	cout << path << endl;*/
	string path = "C:\\Ololo\\graph.txt";
	try
	{
		Graph gr(path);
		gr.show();
		//	gr.DFS();
		//	gr.show();
		//	gr.showSorted();
		gr.BFS();
		gr.show();
		gr.showPathes();
	}
	catch (const runtime_error& ex)
	{
		cout << "File doen't exist" << endl;
	}
	return 0;
}