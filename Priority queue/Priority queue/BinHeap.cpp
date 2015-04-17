#include "BinHeap.h"

BinHeap::BinHeap()
{
	v.push_back(0);
}

BinHeap::BinHeap(const vector<int>& a)
{
	v.push_back(0);
	for (int i = 1; i < a.size(); ++i)
		v.push_back(a[i - 1]);
	heapify();
}
void BinHeap::push(int x)
{
	v.push_back(x);
	swim(v.size() - 1);
}
int BinHeap::pop()
{
	if (v.empty())
		throw BinHeapIsEmpty();
	int n = v.size() - 1;
	swap(v[1], v[n]);
	int x = v[n];
	v.pop_back();
	sink(1);
	return x;
}
bool BinHeap::empty()
{
	return (v.size() == 1);
}
void BinHeap::print()
{
	for (auto x : v)
		cout << x << " ";
}

void BinHeap::swim(int n)
{
	while (v[n / 2] < v[n] && n > 1)
	{
		swap(v[n / 2], v[n]);
		n = n / 2;
	}
}
void BinHeap::sink(int n)
{
	int max_el = n;
	while (n <= v.size() / 2)
	{
		if (2 * n + 1 < v.size() && v[2 * n + 1] > v[2 * n])
		{
			if (v[2 * n + 1] > v[n])
				max_el = 2 * n + 1;
		}
		else
		{
			if (2 * n < v.size() && v[2 * n] > v[n])
				max_el = 2 * n;
			else max_el = n;
		}
		if (max_el == n)
			return;
		swap(v[max_el], v[n]);
		n = max_el;
	}
}
void BinHeap::heapify()
{
	int n = v.size() - 1;
	for (int i = v.size() / 2; i >= 1; --i)
	{
		sink(i);
	}
}