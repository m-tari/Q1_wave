#include "header.h"

void hybrid_theta(_FLOAT *u, _FLOAT cfl, int n, _FLOAT *uh) //hybrid implicit-explicit scheme
{
	int i;
	_FLOAT phi[n];
	_FLOAT matx[n+1][4];
	_FLOAT theta = 1;


	for (i=0; i<n; i++)
	{
		matx[i][0] = 0.5*theta*cfl;
		matx[i][1] = 1;
		matx[i][2] = -0.5*theta*cfl;
		if (i==0)  {
			matx[i][3] = u[i] - ((1-theta)*0.5*cfl*(u[i+1] - *uh));
		}
      	else {      
      		matx[i][3] = u[i] - ((1-theta)*0.5*cfl*(u[i+1] - u[i-1]));
      	}
	}

    u[n] = (2*u[n-1]) - u[n-2];

   *uh = (2*u[0]) - u[1];


	for(i=0; i<n; i++)
	{
		phi[i] = 0;
	}


	solver_TDMA(n, matx, phi);


	for(i=0; i<n; i++)
	{
		u[i]=phi[i];
	}
}