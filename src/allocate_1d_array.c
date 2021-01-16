#include "header.h"

_FLOAT *allocate_1d_array(int nbpt,char *str)
{
  _FLOAT *tmp;  
  
  tmp=(_FLOAT *)calloc(nbpt,sizeof(_FLOAT));

  return tmp;
}