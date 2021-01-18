#include "header.h"

void hybrid_theta(_FLOAT *u, _FLOAT cfl, int n) //hybrid implicit-explicit scheme
{
	int i;
	_FLOAT matx[n][4];
	_FLOAT theta = wave->theta;

	// setting coeffecient matrix 
	for (i=0; i<n; i++)
	{
		if (i==0)
		{
			matx[i][0] = 0.0;
			matx[i][1] = 1.0;
			matx[i][2] = 0.0;        		
		  	matx[i][3] = 0.0; 
		}
		else if (i==n-1)
		{
			matx[i][0] = 0.0;
			matx[i][1] = 1.0;
			matx[i][2] = 0.0;         		
		  	matx[i][3] = 0.0;  		
	    }
		else
		{
			matx[i][0] = 0.5*theta*cfl;
			matx[i][1] = 1;
			matx[i][2] = -0.5*theta*cfl;         		
		  	matx[i][3] = u[i] - ((1-theta)*0.5*cfl*(u[i+1] - u[i-1]));  
		}
    	
	}

	solver_TDMA(n, matx, u);
}