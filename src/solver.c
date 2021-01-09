#include "header.h"

void solver(_FLOAT *u, _FLOAT *x,int nt, _FLOAT dt, int n, _FLOAT cfl,int CASE, FILE *fichier, 
		    _FLOAT *uh, _FLOAT *u_p, _FLOAT *u_pp)
{
	int i,j;

	for (j=0; j < nt; j++)
	{
		fprintf(fichier, "%f \n", dt*j);

		if (j==0)
		{
			initialize(n, u, x, uh, u_p, u_pp);
			for(i=0; i< n; i++)
			{
				fprintf(fichier, "%f, %f\n", x[i], u[i]);
			}
		}

		if (j!=0)
		{
			scheme_selector(CASE,u,cfl,n, uh, u_p, u_pp);
			for(i=0; i< n; i++)
			{
				fprintf(fichier, "%f, %f\n", x[i], u[i]);
			}
		}
	}
}
