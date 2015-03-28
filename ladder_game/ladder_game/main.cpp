#include <iostream>
#include <unordered_set>
#include <string>
#include <queue>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <clocale>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node
{
	string word;
	Node* parent;
	Node(string s, Node* p = nullptr)
	{
		word = s;
		parent = p;
	}
};



class Ladder
{
	unordered_set<string> dict;
	queue<Node*> nodes;
	string startWord;
	string finishWord;
public:
	Ladder(char* start, char* finish) : startWord(start), finishWord(finish)
	{
		ifstream f("nouns.txt");
		if (!f)
			throw runtime_error("File does not exist.");
		string s;
		while (getline(f, s))
		{
			if (s.size() == startWord.size())
				dict.insert(s);
		}
		cout << "Dictionary size: " << dict.size() << endl;
	}

	Node* pathSearching()// BFS (Broad-First Search)
	{
		
		if (dict.find(finishWord) == dict.end())
		{
			throw runtime_error("Нет слова в словаре: " + finishWord);
		}
		if (dict.find(startWord) == dict.end())
		{
			throw runtime_error("Нет слова в словаре: " + startWord);
		}
		dict.erase(dict.find(startWord));
		if (startWord == finishWord)
			return new Node(startWord);
		nodes.push(new Node(startWord));
		while (!nodes.empty())
		{
			Node* n = nodes.front();
			nodes.pop();

			for (auto neighbour : getNeighbours(n->word))
			{
				if (neighbour == finishWord)
					return new Node(neighbour, n);
				nodes.push(new Node(neighbour, n));
			}
		}
		return nullptr;
	}
private:
	vector<string> getNeighbours(const string& s)
	{
		vector<string> v;
		string temp = s;
		string letters = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
		for (int j = 0; j < temp.size(); j++)
		{
			for (int i = 0; i < letters.size(); i++)
			{
				if (s[j] == letters[i]) continue;
				temp[j] = letters[i];
				auto x = dict.find(temp);
				if (x != dict.end())
				{
					v.push_back(temp);
					dict.erase(x);
				}

			}
			temp = s;
		}
	//	cout << v.size() << endl;
		return v;
	}
};



int main(int argc, char* argv[])
{
	setlocale(0, "");
	if (argc != 3)
	{
		cout << "Мало аргументов." << endl;
		return 0;
	}
	if (string(argv[1]).size() != string(argv[2]).size())
	{
		cout << "Длины слов разные." << endl;
		return 0;
	}
	auto t0 = system_clock::now();
	try
	{
		Ladder ld(argv[1], argv[2]);
		Node* n = ld.pathSearching();
		auto t1 = system_clock::now();
		//auto t1 = system_clock::now();
		vector <string> v;
		if (n == nullptr)
			cout << "Нет лесенки." << endl;
		else
		{
			while (n != nullptr)
			{
				v.push_back(n->word);
				n = n->parent;
			}
		}

		cout << duration_cast<milliseconds>(t1 - t0).count() << endl;
		for (auto it = v.rbegin(); it != v.rend() - 1; it++)
			cout << *it << " -> ";
		cout << v[0] << endl;
	}
	catch (const runtime_error& ex)
	{
		cout << ex.what();
	}
	return 0;
}