#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node;

struct Edge
{
	char c;
	Node* next;
	Edge(char letter, Node* p)
	{
		c = letter;
		next = p;
	}
};

struct Node
{
	vector < Edge* > edges;
	int number;
	Node(int i)
	{
		number = i;
	}
	Edge* searchEdge(char c)
	{
		for (auto e : edges)
		{
			if (e->c == c)
			{
				return e;
			}
		}
		return nullptr;
	}
	Node* newNode(char c, Node* p)
	{
		Edge* e = new Edge(c, p);
		edges.push_back(e);
		return e->next;
	}
};

struct Trie
{
	Node* root;
	vector <string> eng;
	Trie()
	{
		root = new Node(-1);
	}
	void insert(string rusWord, string engWord)
	{
		Node* current = root;
		for (unsigned int i = 0; i < rusWord.size(); ++i)
		{
			Edge* e = current->searchEdge(rusWord[i]);
			if (e == nullptr)
			{
				for (unsigned int j = i; j < rusWord.size(); ++j)
				{
					current = current->newNode(rusWord[j], new Node(-1));
				}
				break;
			}
			else current = e->next;
		}
		if (current->number == -1)
		{
			eng.push_back(engWord);
			current->number = eng.size() - 1;
		}
		else
			eng[current->number] = engWord;
	}

	string search(string rusWord)
	{
		Node* current = root;
		string engWord = "";
		bool letterExists = false;
		for (unsigned int i = 0; i < rusWord.size(); ++i)
		{
			Edge* e = current->searchEdge(rusWord[i]);
			if (e == nullptr)
				return engWord;
			else current = e->next;
			current = e->next;
		}
		if (current->number != -1)
			engWord = eng[current->number];
		return engWord;
	}
};

int main()
{
	Trie tr;
	tr.insert("который", "which");
	tr.insert("кот", "cat");
	tr.insert("коза", "goat");
	tr.insert("скот", "cattle");
	tr.insert("скотина", "beast");
	tr.insert("который", "that");
	cout << tr.search("который") << endl;
	return 0;
};