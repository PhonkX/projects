#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class BinHeapIsEmpty : public exception
{
public:
	BinHeapIsEmpty(){}
};
class BinHeap
{
	vector<int> v;
public:
	BinHeap();
	
	BinHeap(const vector<int>& a);
	void push(int x);
	int pop();
	bool empty();
	void print();
private:
	void swim(int n);
	void sink(int n);
	void heapify();
};