#include <stdio.h>
#include <math.h>
#define pi 3.14159265358979323846
#define gamma 1.4
#define R 287

extern void grid_generator(int n, float *x) //Generate 1-D grid
{
	int i;
	for (i=0; i < n; i++)
	{
		x[i] = ((float)pi/n)*i;
	}
}

extern void initialize(int n, float *u, float *x, float *uh, float *u_p, float *u_pp) // Initialize with the profile given in the question
{
	int i;
	printf("Initializing!! \n");

	for (i=0; i<=n; i++)
	{
		if (x[i] < 0.5 || x[i] > 1.0)
		{
			uh =0;
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

extern void euler_backward(float *u, float cfl, int n) // Euler backward scheme
{
	int i;
	float u_n[n];

	for (i=1; i<n; i++)
	{
		u_n[i] = u[i] - (cfl*(u[i] - u[i-1]));
	}
	u_n[0]=u_n[1];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}

}

extern void euler_forward(float *u, float cfl, int n)  // Euler forward scheme
{
	int i;
	float u_n[n];

	for (i=0; i<n-1; i++)
	{
		u_n[i] = u[i] - (cfl*(u[i+1] - u[i]));
	}
	u_n[n-1]=u_n[n-2];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}

extern void FTCS(float *u, float cfl, int n) // Forward time, Centered space scheme
{
	int i;
	float u_n[n];

	for (i=1; i<n-1; i++)
	{
		u_n[i] = u[i] - (cfl*0.5*(u[i+1] - u[i-1]));
	}
	u_n[0]=u[1];
	u_n[n-1]=u_n[n-2];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}

extern void lax_wendroff(float *u, float cfl, int n) // lax_wendroff scheme
{
		int i;
	float u_n[n];

	for (i=1; i<n-1; i++)
	{
		u_n[i] = u[i] - (cfl*0.5*(u[i+1] - u[i-1])) + (0.5*pow(cfl,2)*(u[i+1] - (2*u[i]) + u[i-1])) ;
	}
	u_n[0]=u[1];
	u_n[n-1]=u_n[n-2];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}

extern void lax(float *u, float cfl, int n) //lax scheme
{
		int i;
	float u_n[n];

	for (i=1; i<n-1; i++)
	{
		u_n[i] = ((u[i+1]+u[i-1])/2) - (cfl*0.5*(u[i+1] - u[i-1]));
	}
	u_n[0]=u[1];
	u_n[n-1]=u_n[n-2];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}

extern void leap_frog(float *u, float cfl, int n) // Leap frog scheme
{
		int i;
	float u_n[n], u_p[n];

	for(i=0; i<n; i++)
	{
		u_p[i]=u[i];
	}

	for (i=1; i<n-1; i++)
	{
		u_n[i] = u_p[i] - (cfl*(u[i+1] - u[i-1]));
	}
	u_n[0]=u[1];
	u_n[n-1]=u_n[n-2];

	for(i=0; i<n; i++)
	{
		u[i]=u_n[i];
	}
}

extern void solver_TDMA(int n, float matx[n][4], float *phi) //TDMA (tri-diagonal matrix algorithm) Solver, working based on Versteeg (An Introduction to Computational Fluid Dynamics)
{
	float a[n];
    float c_dash[n];
	int i;

	for(i=0; i<n; i++)
	{
		a[i] = 0;
		phi[i] = 0;
		c_dash[i] = 0;
	}

	c_dash[0]=phi[0];
	c_dash[n-1]=phi[n-1];

	float alpha[n], beta[n], D[n], C[n];


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


extern void hybrid_theta(float *u, float cfl, int n, float *uh) //hybrid implicit-explicit scheme
{
	int i;
	float phi[n];
	float matx[n+1][4];
	float theta = 1;


	for (i=0; i<n; i++)
	{
		matx[i][0] = 0.5*theta*cfl;
		matx[i][1] = 1;
		matx[i][2] = -0.5*theta*cfl;
		if (i==0)  matx[i][3] = u[i] - ((1-theta)*0.5*cfl*(u[i+1] - *uh));
      else 		matx[i][3] = u[i] - ((1-theta)*0.5*cfl*(u[i+1] - u[i-1]));
	}

    u[n] = (2*u[n-1]) - u[n-2];

   *uh = (2*u[0]) - u[1];


	for(i-0; i<n; i++)
	{
		phi[i] = 0;
	}


	solver_TDMA(n, matx, phi);


	for(i=0; i<n; i++)
	{
		u[i]=phi[i];
	}
}

extern void timeo2_spaceo4(float *u,float cfl,int imax,float *u_p,float *u_pp)
{
   int i;

   for (i=0; i<imax; i++)
   {
      u_p[i] = u[i];
   }


   for (i=4; i<imax; i++)
   {
      u[i] = u[i]- ((cfl/12)*((25*u[i]) -(48*u[i-1]) + (36*u[i-2]) - (16*u[i-3]) + (3*u[i-4])));
   }

   u[3]=u[4];
   u[2]=u[3];
   u[1]=u[2];
   u[0]=u[1];

   for(i=0; i<imax; i++)
   {
      u_pp[i] = u_p[i];
   }



}


extern void scheme_selector(int CASE, float *u, float cfl, int n, float *uh, float *u_p, float *u_pp) // To select the discretization scheme to be used
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
		lax_wendroff(u,cfl,n);
	}
	else if (CASE==5)
	{
		lax(u,cfl,n);
	}
	else if (CASE==6)
	{
		leap_frog(u,cfl,n);
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

extern void solver (float *u, float *x,int nt, float dt, int n, float cfl,int CASE, FILE *fichier, float *uh, float *u_p, float *u_pp)
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

int main()
{
	int n,i,nt,j,k, CASE;
	float Temp, c, cfl, dt, dx, t, uh;



/*
		printf("Enter the number of grid points: ");
	scanf("%d", &n);


	float u[n+1], x[n+1], u_p[n+1], u_pp[n+1];

	printf("Enter the temperature: ");
	scanf("%f", &Temp);
	printf("Enter the CFL number: ");
	scanf("%f", &cfl);
	printf("Enter the time for simulation: ");
	scanf("%f", &t);
*/

	printf("Enter the scheme to be used (Enter 0 for test mode): ");
	scanf("%d", &CASE);

    n=100;
    Temp =300;
    cfl = 0.5;
    t = 0.05;

    float u[n+1], x[n+1], u_p[n+1], u_pp[n+1];

	c = sqrt(gamma*R*Temp); //speed of sound
	dx = (pi - 0)/n ;  //spatial grid size
	dt = cfl*dx/c ;  //temporal grid size
	nt = (int)(t/dt); // number of time steps
	printf("Number of time steps are: %d \n", nt);

	FILE *fichier;

	fichier = (fopen("result.txt","w"));  //output file

	grid_generator(n, x); // generation of spatial grid

	printf("CASE used is %d", CASE);

	if (CASE==0)  //Case = 0  means test case(running all the schemes )
	{
		for(i=1; i<=8; i++)
		{
			solver(u,x,nt,dt,n,cfl,i,fichier,&uh,u_p,u_pp);
		}
	}
	else
	{
		solver(u,x,nt,dt,n,cfl,CASE,fichier,&uh,u_p,u_pp);
	}


	printf("Simulation Completed!! \n");
}
