#include "header.h"

void leapfrog(int j, _FLOAT *u, _FLOAT *u_p, _FLOAT cfl, int n) // Leapfrog scheme
{
	
	// for the first timestep only, solve by Backward Euler methid //
	if (j==1)
	{
		euler_backward(u, cfl, n);
	}
	else // 
	{
		int i;
		_FLOAT u_n[n];

		// periodic BCs for leapfrog formula
		u_n[0] = u_p[0] - (cfl*(u[1] - u[n-2]));
		for (i=1; i<n-1; i++)
		{
			u_n[i] = u_p[i] - (cfl*(u[i+1] - u[i-1]));
		}
		u_n[n-1]=u[0];

		// update previous u
		for(i=0; i<n; i++)
		{
			u_p[i]=u[i];
		}

		// update u
		for(i=0; i<n; i++)
		{
			u[i]=u_n[i];
		}
	}	

}