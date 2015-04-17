#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T> class Set
{
	vector <T> v;
public:
	Set(){}
	~Set(){}
	void add(T x)
	{
		auto place = lower_bound(v.begin(), v.end(), x);
		if (place == v.end() || *place != x)
			v.insert(place, x);
	}
	void remove(T x)
	{
		auto place = lower_bound(v.begin(), v.end(), x);
		if (place != v.end() && *place == x)
			v.erase(place);
	}
	bool empty()
	{
		return v.empty();
	}
	bool contains(T x)
	{
		return binary_search(v.begin(), v.end(), x);
	}
	void print()
	{
		for (auto x : v)
			cout << x << ' ';
	}
	const typename vector<T>::const_iterator s_begin() const
	{
		return v.cbegin();
	}
	const typename vector<T>::const_iterator s_end() const
	{
		return v.cend();
	}
};