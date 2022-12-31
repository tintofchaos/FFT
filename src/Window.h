#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

void hann(float *data, int len);
void hamming(float *data, int len);
void blackman(float *data, int len);
