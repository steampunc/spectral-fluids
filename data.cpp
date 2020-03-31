//
// Created by finn on 3/7/20.
//

#include "data.h"

Data::Data(int Nx, int Ny, int Nz) {
    _in = fftw_alloc_real(Nx * Ny * Nz);
    _out = fftw_alloc_complex(Nx * Ny * (Nz / 2 + 1));
    _dimensions[0] = Nx;
    _dimensions[1] = Ny;
    _dimensions[2] = Nz;
}

Data::~Data() {
    fftw_free(_in);
    fftw_free(_out);
}

void Data::set_in(int x, int y, int z, double val) {
    int index = z + _dimensions[2] * (y + _dimensions[1] * x);
    _in[index] = val;
}

void Data::set_out(int k, int l, int m, std::complex<double> val) {
    int index = m + (_dimensions[2] / 2 + 1) * (l + _dimensions[1] * k);
    _out[index][0] = val.real();
    _out[index][1] = val.imag();
}

double *Data::get_in() { return _in; }

double Data::get_in(int x, int y, int z) {
    return _in[z + _dimensions[2] * (y + _dimensions[1] * x)];
}

fftw_complex *Data::get_out() { return _out; }

double *Data::get_out(int k, int l, int m) {
    return _out[m + (_dimensions[2] / 2 + 1) * (l + _dimensions[1] * k)];
}

int *Data::get_dimensions() { return _dimensions; }

void Data::normalize() {
    double size = _dimensions[0] * _dimensions[1] * _dimensions[2];
    for (int i = 0; i < _dimensions[0]; i++) {
        for (int j = 0; j < _dimensions[1]; j++) {
            for (int k = 0; k < _dimensions[2]; k++) {
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
    int numOut = _dimensions[0] * _dimensions[1] * (_dimensions[2] / 2 + 1);
    for (int i = 0; i < _dimensions[0] * _dimensions[1] * _dimensions[2]; i++) {
        if (i < numOut) {
            logFile << _in[i] << ", " << _out[i][0] << ", " << _out[i][1]
                    << ", "
                    << sqrt(_out[i][0] * _out[i][0] + _out[i][1] * _out[i][1])
                    << std::endl;
        } else {
            logFile << _in[i] << ", , , " << std::endl;
        }
    }
    logFile.close();
}
