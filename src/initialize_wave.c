#include "header.h"

void initialize_wave()
{
	// allocate memory for beam parameters
	wave = malloc(sizeof(S_wave));     

	// read input file
	char   filename[] = "InputFile";
	read_input_wave(filename);

	wave->u = allocate_1d_array(wave->n+1, "u");     // solution vector for now 
	wave->x = allocate_1d_array(wave->n+1, "x");     
	wave->u_p = allocate_1d_array(wave->n+1, "u_p");  // solution vector for previous step
	wave->u_pp = allocate_1d_array(wave->n+1, "u_pp");  	  // solution vector for the step before previous step
	wave->uh = 0.0;
}