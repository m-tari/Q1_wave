#include "header.h"
// TDMA (tri-diagonal matrix algorithm) Solver, 
// working based on Versteeg (An Introduction to Computational Fluid Dynamics, p-222)
void solver_TDMA(int n, _FLOAT matx[n][4], _FLOAT *phi) 
{
	_FLOAT A[n];
    _FLOAT c_dash[n];
	int i;

	_FLOAT alpha[n], beta[n], D[n], C[n];


	for(i=0; i<n; i++)
	{
		alpha[i] = -1*matx[i][0];
		D[i] = matx[i][1];
		beta[i] = -1*matx[i][2];
		C[i] = matx[i][3];
	}

	// BCs
	A[0] = 0.0;
	c_dash[0] = phi[0];
	A[n-1] = 0.0;
	c_dash[n-1] = phi[n-1];

    for(i=1 ; i<n; i++)
        {
			A[i] = alpha[i]/(D[i]-beta[i]*A[i-1]);
        	c_dash[i] = (beta[i]*c_dash[i-1]+ C[i])/(D[i]-beta[i]*A[i-1]);
		}


    for(i=n-2; i>0; i--)
    {
        phi[i]=A[i]*phi[i+1]+c_dash[i];
	}
}