#include "header.h"
// To select the discretization scheme to be used
void scheme_selector(int j, int CASE, _FLOAT *u, _FLOAT cfl, int n, _FLOAT *uh, _FLOAT *u_p, _FLOAT *u_pp) 
{
	if (CASE==1)
	{
		euler_backward(u,cfl,n);
	}
	else if (CASE==2)
	{
		euler_forward(u,cfl,n);
	}
	else if (CASE==3)
	{
		FTCS(u,cfl,n);
	}
	else if (CASE==4)
	{
		leapfrog(j,u,u_p,cfl,n);
	}
	else if (CASE==5)
	{
		lax_wendroff(u,cfl,n);		
	}
	else if (CASE==6)
	{
		lax(u,cfl,n);	
	}
	else if (CASE==7)
	{
		hybrid_theta(u,cfl,n,uh);
	}
	else if (CASE==8)
	{
	   timeo2_spaceo4(u,cfl,n,u_p, u_pp);
	}
}