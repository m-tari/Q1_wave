#include "header.h"

void solver(_FLOAT *u, _FLOAT *x,int nt, _FLOAT dt, int n, _FLOAT cfl,int CASE, 
		    _FLOAT *uh, _FLOAT *u_p, _FLOAT *u_pp)
{
	int i,j;

	for (j=0; j < nt; j++)
	{
		if (j==0)
		{
			initialize(n, u, x, uh, u_p, u_pp);
			writeOutput(j, n, x, u);
		}

		if (j!=0)
		{
			scheme_selector(CASE,u,cfl,n, uh, u_p, u_pp);
			writeOutput(j, n, x, u);
		}
	}
}
