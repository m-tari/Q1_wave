#include "header.h"

void solver(_FLOAT *u, _FLOAT *x,int nt, _FLOAT dt, int n, _FLOAT cfl,int CASE, 
		    _FLOAT *u_p, _FLOAT *u_pp)
{
	int i,j;

	for (j=0; j < nt; j++)
	{
		if (j==0)
		{
			initialize(n, u, x, u_p, u_pp);
			writeOutput(j, n, x, u);
		}

		if (j!=0)
		{
			scheme_selector(j, CASE,u,cfl,n, u_p, u_pp);
			writeOutput(j, n, x, u);
		}
	}
}
