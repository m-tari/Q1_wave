#include "header.h"

void FTCS(_FLOAT *u, _FLOAT cfl, int n) // Forward time, Centered space scheme
{
	int i;
	_FLOAT u_n[n];

	for (i=1; i<n-1; i++)
	{
		u_n[i] = u[i] - (cfl*0.5*(u[i+1] - u[i-1]));
	}
	u_n[0]=u_n[n-1];
	u_n[n-1]=u_n[n-2];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}