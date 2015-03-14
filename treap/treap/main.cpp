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
	TreapNode(int k)
	{
		key = k;
		priority = rand();
		left = right = NULL;
	}
};

class Treap
{

	TreapNode* root = NULL;
public:
	Treap(){}
	void insert(int k)
	{
		if (root == NULL)
		{
			root = new TreapNode(k);
			return;
		}
		if (search(k))
		{
			cout << "Node alreade exists." << endl;
			return;
		}
		TreapNode* l;
		TreapNode* r;
		split(root, k, l, r);
		merge(l, l, new TreapNode(k));
		merge(root, l, r);
	}
	bool search(int k)
	{
		TreapNode* current = root;
		while (current != NULL)
		{
			if (current->key == k)
				return true;
			if (current->key > k)
				current = current->left;
			else
				current = current->right;
		}
		return false;
	}
	void removeNode(int k)
	{
		/*if (root == NULL)
			return;
		TreapNode *l;
		TreapNode *r;

		split(root, k, l, r);
		TreapNode *temp = new TreapNode(k);
		split(l, k, l, temp);
		merge(root, l, r);*/
		remove1(root, k);
	}
	void show()
	{
		show1(root, 0);
	}
	bool empty()
	{
		if (root == NULL)
			return 1;
		else return 0;
	}
	int height()
	{
		return height1(root);
	}
private:
	int height1(TreapNode* p)
	{
		if (p == nullptr)
			return 0;
		else return max(height1(p->left), height1(p->right))+1;
	}
	void remove1(TreapNode* &p, int key)
	{
		if (p == nullptr)
			return;
		if (p->key == key)
			merge(p, p->left, p->right);
		else
			remove1(key < p->key ? p->left : p->right, key);
	}
	void show1(TreapNode *p, int k)
	{
		if (p == NULL) return;
		show1(p->left, k + 2);
		cout << string(k, ' ') << p->key << '(' << p->priority << ')' << endl;
		show1(p->right, k + 2);
	}
	static void split(TreapNode* t, int k, TreapNode* &t1, TreapNode* &t2)
	{
		if (t == NULL)
			t1 = t2 = NULL;
		else if (k > t->key)
		{
			split(t->right, k, t->right, t2);
			t1 = t;
		}
		else
		{
			split(t->left, k, t1, t->left);
			t2 = t;
		}
	}

	static void merge(TreapNode* &t, TreapNode* t1, TreapNode* t2)
	{
		if (t1 == NULL || t2 == NULL)
			if (t1 != NULL)
				t = t1;
			else
				t = t2;
		else if (t1->priority > t2->priority)
		{
			merge(t1->right, t1->right, t2);
			t = t1;
		}
		else
		{
			merge(t2->left, t1, t2->left);
			t = t2;
		}
	}
};

int main()
{
	Treap t;
	vector<int> v;
	for (int i = 0; i < 5; ++i)
	{
		v.push_back(rand());
		t.insert(v[i]);
		//cout << endl;
	}
	t.show();
	cout << t.height() << endl;
	int j = 0;
	cout << endl;
	cout << v[0] << endl;
	if (t.search(v[0]))
		cout << "Node exists" << endl;
	else cout << "Node doesn't exist" << endl;
	t.removeNode(v[0]);
	t.show();
	cout << v[0] << endl;
	if (t.search(v[0]))
		cout << "Node exists" << endl;
	else cout << "Node doesn't exist" << endl;
	cout << t.height() << endl;
	/*for(int i = 0; i < 5; ++i)
	{
		cout << "Removing node with priority " << v[i];
		t.removeNode(v[i]);
		cout << endl;
		t.show();
	}*/
	return 0;
}