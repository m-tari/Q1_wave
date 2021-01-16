#include "header.h"

void initialize_wave(char *inputfilename)
{
	// allocate memory for wave parameters
	wave = malloc(sizeof(S_wave));     

	// read input file
	read_input_wave(inputfilename);

	wave->u = allocate_1d_array(wave->n+1, "u");		// solution vector for the current time 
	wave->x = allocate_1d_array(wave->n+1, "x");		// grid location
	wave->u_p = allocate_1d_array(wave->n+1, "u_p");		// solution vector for previous step
	wave->u_pp = allocate_1d_array(wave->n+1, "u_pp");		// solution vector for the step before previous step
}