#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct TreapNode
{
	int key;
	int priority;
	TreapNode *left;
	TreapNode *right;
public:
	TreapNode(int k);
};

class Treap
{
	TreapNode *root = NULL;
public:
	Treap(){}
	void insert(int k);
	bool search(int k);
	void removeNode(int k);
	void show();
	bool empty();
	int height();
private:
	int height1(TreapNode* p);
	void remove1(TreapNode* &p, int key);
	void show1(TreapNode *p, int k);
	static void split(TreapNode* t, int k, TreapNode* &t1, TreapNode* &t2);
	static void merge(TreapNode* &t, TreapNode* t1, TreapNode* t2);
};