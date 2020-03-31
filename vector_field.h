//
// Created by finn on 3/31/20.
//

#ifndef SPECTRAL_C_VECTOR_FIELD_H
#define SPECTRAL_C_VECTOR_FIELD_H

#include <complex.h>
#include "data.h"
#include <fftw3.h>

class VectorField {
public:
    VectorField(int Nx, int Ny, int Nz);
    ~VectorField();
    void set_in(int x, int y, int z, double val[]);
    void set_out(int x, int y, int z, std::complex<double> val[]);
    double* get_in(int x, int y, int z);
    double mag_in(int x, int y, int z);
    fftw_complex* get_out(int k, int l, int m);
    void normalize();
    int* get_dimensions();
    void save(char * filenameX, char* filenameY, char* filenameZ);

    double * get_in_x();
    double * get_in_y();
    double * get_in_z();
    fftw_complex * get_out_x();
    fftw_complex * get_out_y();
    fftw_complex * get_out_z();
private:
    Data* _data[3];
    int _dimensions[3];

};


#endif //SPECTRAL_C_VECTOR_FIELD_H
