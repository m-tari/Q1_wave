#include "header.h"

void leap_frog(_FLOAT *u, _FLOAT cfl, int n) // Leap frog scheme
{
		int i;
	_FLOAT u_n[n], u_p[n];

	for(i=0; i<n; i++)
	{
		u_p[i]=u[i];
	}

	for (i=1; i<n-1; i++)
	{
		u_n[i] = u_p[i] - (cfl*(u[i+1] - u[i-1]));
	}
	u_n[0]=u[1];
	u_n[n-1]=u_n[n-2];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}