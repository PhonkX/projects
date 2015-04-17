#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int> s;
	s.insert(1);
	for (auto x : s)
		cout << x << endl;
	return 0;
}