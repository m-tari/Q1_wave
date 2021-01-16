#include "header.h"

void euler_forward(_FLOAT *u, _FLOAT cfl, int n)  // Euler forward scheme
{
	int i;
	_FLOAT u_n[n];

	// Foreward Euler method
	for (i=0; i<n-1; i++)
	{
		u_n[i] = u[i] - (cfl*(u[i+1] - u[i]));
	}

	// periodic BC
	u_n[n-1]=u[0];

	// update solution vector
	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}