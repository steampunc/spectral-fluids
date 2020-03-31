//
// Created by finn on 3/7/20.
//

#include <iostream>
#include "data.h"

Data::Data(int Nx, int Ny, int Nz) {
    in_ = fftw_alloc_real(Nx * Ny * Nz);
    out_ = fftw_alloc_complex(Nx * Ny * (Nz / 2 + 1));
    dimensions_[0] = Nx;
    dimensions_[1] = Ny;
    dimensions_[2] = Nz;
}

Data::~Data() {
    std::cout << "Removing scalar field." << std::endl;
    fftw_free(in_);
    fftw_free(out_);
}

void Data::set_in(int x, int y, int z, double val) {
    int index = z + dimensions_[2] * (y + dimensions_[1] * x);
    in_[index] = val;
}

void Data::set_out(int k, int l, int m, std::complex<double> val) {
    int index = m + (dimensions_[2] / 2 + 1) * (l + dimensions_[1] * k);
    out_[index][0] = val.real();
    out_[index][1] = val.imag();
}

double *Data::get_in() { return in_; }

double Data::get_in(int x, int y, int z) {
    return in_[z + dimensions_[2] * (y + dimensions_[1] * x)];
}

fftw_complex *Data::get_out() { return out_; }

fftw_complex *Data::get_out(int k, int l, int m) {
    return &out_[m + (dimensions_[2] / 2 + 1) * (l + dimensions_[1] * k)];
}

int *Data::get_dimensions() { return dimensions_; }

void Data::normalize() {
    double size = dimensions_[0] * dimensions_[1] * dimensions_[2];
    for (int i = 0; i < dimensions_[0]; i++) {
        for (int j = 0; j < dimensions_[1]; j++) {
            for (int k = 0; k < dimensions_[2]; k++) {
                set_in(i, j, k, get_in(i, j, k) / size);
            }
        }
    }
}

void Data::save(char *filename) {
    remove(filename);
    std::ofstream logFile;
    logFile.open(filename);
    logFile << "in, out_r, out_c, out_mag" << std::endl;
    int numOut = dimensions_[0] * dimensions_[1] * (dimensions_[2] / 2 + 1);
    for (int i = 0; i < dimensions_[0] * dimensions_[1] * dimensions_[2]; i++) {
        if (i < numOut) {
            logFile << in_[i] << ", " << out_[i][0] << ", " << out_[i][1]
                    << ", "
                    << sqrt(out_[i][0] * out_[i][0] + out_[i][1] * out_[i][1])
                    << std::endl;
        } else {
            logFile << in_[i] << ", , , " << std::endl;
        }
    }
    logFile.close();
}
