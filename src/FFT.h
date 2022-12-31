#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

void fft(float *inreal, float *inimag, float *outreal, float *outimag, int len);
void ifft(float *inreal, float *inimag, float *outreal, float *outimag, int len);
