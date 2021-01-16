#include "header.h"

void euler_backward(_FLOAT *u, _FLOAT cfl, int n) // Euler backward scheme
{
	int i;
	_FLOAT u_n[n];

	// periodic BC
	u_n[0] = u[n-1];

	// Backward Euler method
	for (i=1; i<n; i++)
	{
		u_n[i] = u[i] - (cfl*(u[i] - u[i-1]));
	}

	// update solution vector
	for(i=0; i<n; i++)
	{
		u[i] = u_n[i];
	}

}