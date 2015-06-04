#include "floyd_warshall.h"

int main()
{
	Graph gr("graph.txt");
	gr.Floyd_Warshall();
	gr.show();
	return 0;
}