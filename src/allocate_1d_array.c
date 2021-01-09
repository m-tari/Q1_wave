#include "header.h"
#define STLEN 128

_FLOAT *allocate_1d_array(int nbpt,char *str)
{
  _FLOAT *tmp;  
  
  tmp=(_FLOAT *)calloc(nbpt,sizeof(_FLOAT));

  //for (i=0;i<nbpt;i++) tmp[i]=0.;
  
  return tmp;
}