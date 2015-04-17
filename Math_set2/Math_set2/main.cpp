#include <ctime>
#include "set_operations.h"

using namespace std;

int main()
{
	srand(time(NULL));
	Set<int> s1;
	for (int i = 0; i < 5; ++i)
		s1.add(rand() % 10);
	s1.print();
	cout << endl;
	Set<int> s2;
	for (int i = 0; i < 5; ++i)
		s2.add(rand() % 10);
	s2.print();
	cout << endl;
	cout << "Intersection: ";
	s_intersection(s1, s2).print();
	cout << "Union: ";
	s_union(s1, s2).print();
	cout << "Difference: ";
	s_difference(s1, s2).print();
	return 0;
}