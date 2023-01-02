#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

static void complex_add(float *x_real, float *x_imag, float *y_real, float *y_imag) {
    *x_real += (*y_real);
    *x_imag += (*y_imag);
}

static void complex_sub(float *x_real, float *x_imag, float *y_real, float *y_imag) {
    *x_real -= (*y_real);
    *x_imag -= (*y_imag);
}

static void complex_mul(float *x_real, float *x_imag, float *y_real, float *y_imag) {
    *x_real = (*x_real) * (*y_real) - (*x_imag) * (*y_imag);
    *x_imag = (*x_real) * (*y_imag) + (*y_real) * (*x_imag);
}

static void complex_exp(float *x_real, float *x_imag, float y) {
    *x_real = cos(y);
    *x_imag = sin(y);
}

static void fftcore(float *inreal, float *inimag, float *outreal, float *outimag, int len, int stride, int direction) {
    if (len == 1) {
        outreal[0] = inreal[0];
        outimag[0] = inimag[0];
    } else {
        fftcore(inreal, inimag, outreal, outimag, len / 2, stride * 2, direction);
        fftcore(&inreal[stride], &inimag[stride], &outreal[len/2], &outimag[len/2], len/2, stride * 2, direction);

        for (int k = 0; k < len/2; k++) {
            float p_real = outreal[k];
            float p_imag = outimag[k];

            float twiddle_real, twiddle_imag;
            complex_exp(&twiddle_real, &twiddle_imag, 2 * M_PI * k / len * (direction?-1:1));

            float bias_real, bias_imag;
            bias_real = outreal[k+len/2];
            bias_imag = outimag[k+len/2];

            complex_mul(&bias_real, &bias_imag, &twiddle_real, &twiddle_imag);
            float temp_real, temp_imag;
            temp_real = outreal[k];
            temp_imag = outimag[k];

            complex_add(&outreal[k], &outimag[k], &bias_real, &bias_imag);
            complex_sub(&temp_real, &temp_imag , &bias_real, &bias_imag);
            outreal[k+len/2] = temp_real;
            outimag[k+len/2] = temp_imag;


        }
    }
}

void fft(float *inreal, float *inimag, float *outreal, float *outimag, int len) {
    fftcore(inreal, inimag, outreal, outimag, len, 1, 1);
}

void ifft(float *inreal, float *inimag, float *outreal, float *outimag, int len) {
    fftcore(inreal, inimag, outreal, outimag, len, 1, 0);
    for (int i = 0; i < len; i++) {
         outreal[i] /= len;
         outimag[i] /= len;
     }
}
