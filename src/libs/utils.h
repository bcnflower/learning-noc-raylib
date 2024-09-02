#include <stdlib.h>

int irandfrom(int min, int max)
{
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

double rand_0_1()
{
   return rand() / ((double)RAND_MAX);
}

double drandfrom(double min, double max)
{
   double range = (max - min);
   double div = RAND_MAX / range;
   return min + (rand() / div);
}