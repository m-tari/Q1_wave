#include "header.h"

void lax(_FLOAT *u, _FLOAT cfl, int n) //lax scheme
{
		int i;
	_FLOAT u_n[n];

	// lax method
	u_n[0] = (u[1]+u[n-2])/2. - cfl*0.5*(u[1] - u[n-2]);
	for (i=1; i<n-1; i++)
	{
		u_n[i] = (u[i+1]+u[i-1])/2. - cfl*0.5*(u[i+1] - u[i-1]);
	}
	u_n[n-1]=u[0];

	// update solution vector
	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}