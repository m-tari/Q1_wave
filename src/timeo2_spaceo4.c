#include "header.h"

void timeo2_spaceo4(_FLOAT *u, _FLOAT cfl, int n)
{
   int i;
   _FLOAT u_n[n];

   // periodic BCs.
   u_n[0] = u[0]- cfl*(-1./12*u[2] + 2./3*u[1] - 2./3*u[n-2] + 1./12*u[n-3])
            + 1./2*pow(cfl,2)*(-1./12*u[2] + 4./3*u[1] - 5./2*u[0] + 4./3*u[n-2] - 1./12*u[n-3]);

   u_n[1] = u[1]- cfl*(-1./12*u[3] + 2./3*u[2] - 2./3*u[0] + 1./12*u[n-2])
            + 1./2*pow(cfl,2)*(-1./12*u[3] + 4./3*u[2] - 5./2*u[1] + 4./3*u[0] - 1./12*u[n-2]);

   u_n[n-1] = u[0]; 
   u_n[n-2] = u[1];

   // T2S4 formula
   for (i=2; i<n-2; i++)
   {
      u_n[i] = u[i]- cfl*(-1./12*u[i+2] + 2./3*u[i+1] - 2./3*u[i-1] + 1./12*u[i-2])
               + 1./2*pow(cfl,2)*(-1./12*u[i+2] + 4./3*u[i+1] - 5./2*u[i] + 4./3*u[i-1] - 1./12*u[i-2]);
   }

   // update solution vector
   for(i=0; i<n; i++)
   {
      u[i]=u_n[i];
   }
}