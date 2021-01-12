#include "header.h"

void writeOutput(int j, int n, _FLOAT *x, _FLOAT *u)
{

	char outputfilename[100];
    sprintf(outputfilename, "results-%d.csv", j);

	FILE *output;
	output = fopen(outputfilename,"w");  //output file
	fprintf(output, "x,u\n");				
	
	for(int i=0; i< n; i++)
	{
		fprintf(output, "%f, %f\n", x[i], u[i]);
	}

	fclose(output);
}