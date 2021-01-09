#include "header.h"
//TDMA (tri-diagonal matrix algorithm) Solver, working based on Versteeg (An Introduction to Computational Fluid Dynamics)
void solver_TDMA(int n, _FLOAT matx[n][4], _FLOAT *phi) 
{
	_FLOAT a[n];
    _FLOAT c_dash[n];
	int i;

	for(i=0; i<n; i++)
	{
		a[i] = 0;
		phi[i] = 0;
		c_dash[i] = 0;
	}

	c_dash[0]=phi[0];
	c_dash[n-1]=phi[n-1];

	_FLOAT alpha[n], beta[n], D[n], C[n];


	for(i=0; i<n; i++)
	{
		alpha[i] = matx[i][2];
		beta[i] = matx[i][0];
		D[i] = matx[i][1];
		C[i] = matx[i][3];
	}

	// Check the above markings, they may be wrong, check with python file

    for(i=0 ; i<n; i++)
        {
			a[i] = alpha[i]/(D[i]-(beta[i]*a[i-1]));
        	c_dash[i] = ((beta[i]*c_dash[i-1])+ C[i])/(D[i]-(beta[i]*a[i-1]));
		}
	phi[n-1] = c_dash[n-1];

    for(i=n-2; i>=0; i--)
    {

        phi[i]=(a[i]*phi[i+1])+c_dash[i];
	}
}