#include "header.h"

void timeo2_spaceo4(_FLOAT *u,_FLOAT cfl,int imax,_FLOAT *u_p,_FLOAT *u_pp)
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