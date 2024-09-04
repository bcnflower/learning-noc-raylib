#include <iostream>
#include <algorithm>

int irandfrom(int min, int max)
{
   return min + std::rand() / (RAND_MAX / (max - min + 1) + 1);
}

double rand_0_1()
{
   return std::rand() / ((double)RAND_MAX);
}

double drandfrom(double min, double max)
{
   double range = (max - min);
   double div = RAND_MAX / range;
   return min + (std::rand() / div);
}

// Defination from p5js
double map(double n, double start1, double stop1, double start2, double stop2, bool withinBounds = false)
{
   double newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
   if (withinBounds)
   if (start2 < stop2)
   {
      newval = std::clamp(newval, start2, stop2);
   } else{
      newval = std::clamp(newval, stop2, start2);
   }
   return newval;
}