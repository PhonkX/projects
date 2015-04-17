#include "treap.h"

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