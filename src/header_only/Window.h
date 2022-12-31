#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

void hann(float *data, int len) {
    for (int i = 0; i < len; i++)
        data[i] *= 0.5 * (1 - cos(2 * M_PI * i / len));
}

void hamming(float *data, int len) {
    for (int i = 0; i < len; i++)
        data[i] *= 0.54 - (0.46 * cos(2 * M_PI * i / len));
}

void blackman(float *data, int len) {
    for (int i = 0; i < len; i++)
        data[i] *= 0.42 - 0.5 * cos( (2 * M_PI * i) / (len - 1) ) + 0.08 * cos( (4 * M_PI * i) / (len - 1) );
}
