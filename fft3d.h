#ifndef SPECTRAL_C_LIBRARY_H
#define SPECTRAL_C_LIBRARY_H

#include <fftw3.h>
#include "data.h"
#include "vector_field.h"

class FFT3d {
public:
    // Initializes the object for a scalar field
    FFT3d(Data *d);

    // Initializes the fourier transform object for a real vector field
    FFT3d(VectorField *v);

    ~FFT3d();

    // Executes the forward Fourier transform on all components of data
    void forward();

    // Executes the inverse Fourier transform on all components of data
    void backward();

private:
    bool vectorTransform_;
    fftw_plan fPx_, fPy_, fPz_, bPx_, bPy_, bPz_;
};

#endif // SPECTRAL_C_LIBRARY_H
