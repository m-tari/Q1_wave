#include "header.h"

void lax_wendroff(_FLOAT *u, _FLOAT cfl, int n) // lax_wendroff scheme
{
		int i;
	_FLOAT u_n[n];

	// lax wendroff method with periodic BCs
	u_n[0] = u[n-1] - cfl*0.5*(u[1] - u[n-2]) + 0.5*pow(cfl,2)*(u[1] - 2*u[0] + u[n-2]);
	for (i=1; i<n-1; i++)
	{
		u_n[i] = u[i] - cfl*0.5*(u[i+1] - u[i-1]) + 0.5*pow(cfl,2)*(u[i+1] - 2*u[i] + u[i-1]) ;
	}
	u_n[n-1]=u[0];

	// update solution vector
	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}