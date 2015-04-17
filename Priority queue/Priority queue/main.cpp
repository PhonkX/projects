#include <ctime>
#include "BinHeap.h"

int main()
{
	srand(time(NULL));
	vector<int> a;
	for (int i = 0; i < 5; ++i)
		a.push_back(rand() % 10);
	try
	{
		BinHeap bh(a);
		bh.print();
		cout << endl;
		while (!bh.empty())
			cout << bh.pop() << " ";
		cout << endl;
		BinHeap v;
		for (int i = 0; i < 5; ++i)
			v.push(rand() % 10);
		v.print();
		cout << endl;
		while (!v.empty())
			cout << v.pop() << " ";
	}
	catch (BinHeapIsEmpty)
	{
		cout << "Bin heap is empty!!! ololo" << endl;
	}
	return 0;
}