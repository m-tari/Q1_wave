#include "header.h"

// Initialize with the profile given in the question
void initialize(int n, _FLOAT *u, _FLOAT *x, _FLOAT *uh, _FLOAT *u_p, _FLOAT *u_pp) 
{
	int i;
	printf("Initializing! \n");

	for (i=0; i<=n; i++)
	{
		if (x[i] < 0.5 || x[i] > 1.0)
		{
			uh = 0;
			u[i] = 0;
			u_p[i] = 0;
			u_pp[i] = 0;
		}
		else if (*(x+i) >= 0.5 && *(x+i) <= 1.0)
		{
			u[i] = 1;
			u_p[i] = 1;
			u_pp[i] = 1;
		}
	}

}