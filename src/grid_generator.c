#include "header.h"

void grid_generator(int n, _FLOAT *x) //Generate 1-D grid
{
	int i;
	for (i=0; i < n; i++)
	{
		x[i] = ((_FLOAT)5.0/n)*i;
	}
}