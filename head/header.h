#ifndef head_wave
#define head_wave
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.14159265358979323846
#define _FLOAT double

/* ------ Structs -------*/
typedef struct S_wave
{
	int n; // number of points along the wave
	_FLOAT cfl; // clf number
	_FLOAT c; // speed of the wave
	_FLOAT time; // simulation duration
	int scheme;  // discretization scheme

	_FLOAT *x;
	_FLOAT *u;
	_FLOAT *u_p;
	_FLOAT *u_pp;
	_FLOAT uh; // halo cell

} S_wave;

extern S_wave *wave;

/* ------ Functions -------*/
extern void solver(_FLOAT *u, _FLOAT *x,int nt, _FLOAT dt, int n, _FLOAT cfl,int CASE, 
		    _FLOAT *uh, _FLOAT *u_p, _FLOAT *u_pp);
extern void scheme_selector(int CASE, _FLOAT *u, _FLOAT cfl, int n, _FLOAT *uh, _FLOAT *u_p, _FLOAT *u_pp);
extern void initialize(int n, _FLOAT *u, _FLOAT *x, _FLOAT *uh, _FLOAT *u_p, _FLOAT *u_pp); 
extern void grid_generator(int n, _FLOAT *x); //Generate 1-D grid
extern void timeo2_spaceo4(_FLOAT *u,_FLOAT cfl,int imax,_FLOAT *u_p,_FLOAT *u_pp);
extern void hybrid_theta(_FLOAT *u, _FLOAT cfl, int n, _FLOAT *uh); //hybrid implicit-explicit scheme
extern void solver_TDMA(int n, _FLOAT matx[n][4], _FLOAT *phi); 
extern void leap_frog(_FLOAT *u, _FLOAT cfl, int n); // Leap frog scheme
extern void lax(_FLOAT *u, _FLOAT cfl, int n); //lax scheme
extern void lax_wendroff(_FLOAT *u, _FLOAT cfl, int n); // lax_wendroff scheme
extern void FTCS(_FLOAT *u, _FLOAT cfl, int n); // Forward time, Centered space scheme
extern void euler_forward(_FLOAT *u, _FLOAT cfl, int n);  // Euler forward scheme
extern void euler_backward(_FLOAT *u, _FLOAT cfl, int n); // Euler backward scheme
extern void read_input_wave(char *filename);
extern _FLOAT *allocate_1d_array(int nbpt,char *str); 
extern void initialize_wave(char *inputfilename);
extern void writeOutput(int j, int n, _FLOAT *x, _FLOAT *u);

#endif