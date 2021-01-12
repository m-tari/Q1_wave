#include "header.h"

struct S_wave *wave;

int main(int argc, char *argv[])
{

    printf("\nOne-dimensional wave equation solver, executable version\n");
    printf("Usage:   ./wave inputfilename \n\n");	
	
	int i,nt;
	_FLOAT dt, dx;

	// initialize and read input file
    initialize_wave(argv[1]);

	dx = (pi - 0)/wave->n ;  // spatial grid size
	dt = wave->cfl*dx/wave->c ;  // temporal grid size
	nt = (int)(wave->time/dt); // number of time steps
	printf("Number of time steps are: %d \n", nt);

	grid_generator(wave->n, wave->x); // generation of spatial grid

	if (wave->scheme == 0) { // scheme = 0 means running all the schemes
		
		for(i=1; i<=8; i++) {
			solver(wave->u,wave->x,nt,dt,wave->n,wave->cfl,i,&wave->uh,wave->u_p,wave->u_pp);
		}
	}
	else {
		solver(wave->u,wave->x,nt,dt,wave->n,wave->cfl,wave->scheme,&wave->uh,wave->u_p,wave->u_pp);
	}


	// free memory
	free(wave->u);
	free(wave->x);
	free(wave->u_p);
	free(wave->u_pp);
	free(wave);

	printf("Simulation Completed!\n");

	return 0;
}