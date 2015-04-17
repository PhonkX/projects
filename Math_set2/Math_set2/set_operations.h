#include "set.h"
using namespace std;

template <typename T> Set<T> s_union(const Set<T>& s1, const Set<T>& s2)
{
	Set<T> s;
	auto p1 = s1.s_begin();
	auto p2 = s2.s_begin();
	//while (p1 != s1.s_end() && p2 != s2.s_end())
	while (true)
	{
		if (p1 == s1.s_end())
		{
			while (p2 != s2.s_end())
				s.add(*p2++);
			break;
		}
		if (p2 == s2.s_end())
		{
			while (p1 != s1.s_end())
				s.add(*p1++);
			break;
		}
		if (*p1 > *p2)
		{
			s.add(*p2);
			p2++;
		}
		else if (*p1 < *p2)
		{
			s.add(*p1);
			p1++;
		}
		else if (*p1 == *p2)
		{
			s.add(*p1);
			p1++;
			p2++;
		}
	}

	return s;
}

template <typename T> Set<T> s_intersection(const Set<T>& s1, const Set<T>& s2)
{
	Set<T> s;
	auto p1 = s1.s_begin();
	auto p2 = s2.s_begin();
	while (p1 != s1.s_end() && p2 != s2.s_end())
	{
		if (*p1 > *p2)
		{
			p2++;
			//break;
		}
		else if (*p1 < *p2)
		{
			p1++;
			//break;
		}
		else if (*p1 == *p2)
		{
			s.add(*p1);
			p1++;
			p2++;
			//break;
		}
	}
	return s;
}

template<typename T> Set<T> s_difference(const Set<T>& s1, const Set<T>& s2)
{
	Set<T> s;
	auto p1 = s1.s_begin();
	auto p2 = s2.s_begin();
	//while (p1 != s1.s_end() && p2 != s2.s_end())
	while (p1 != s1.s_end())
	{
		if (p2 == s2.s_end())
		{
			while (p1 != s1.s_end())
				s.add(*p1++);
			break;
		}
		if (*p1 > *p2)
		{
			p2++;
		}
		else if (*p1 < *p2)
		{
			s.add(*p1);
			p1++;
		}
		else if (*p1 == *p2)
		{
			p1++;
			p2++;
		}
	}

	return s;
}