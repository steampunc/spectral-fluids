//
// Created by finn on 3/7/20.
//

#ifndef SPECTRAL_C_TYPES_H
#define SPECTRAL_C_TYPES_H

#include <complex.h>
#include "fftw3.h"
#include <fstream>
#include <math.h>

class Data {
public:
  Data(int Nx, int Ny, int Nz);
  ~Data();
  void set_in(int x, int y, int z, double val);
  void set_out(int x, int y, int z, std::complex<double> val);
  double* get_in();
  double get_in(int x, int y, int z);
  fftw_complex* get_out();
  fftw_complex* get_out(int k, int l, int m);
  int* get_dimensions();
  void save(char * filename);
  void normalize();
private:
  double* _in;
  fftw_complex* _out;
  int _dimensions[3];
};

#endif // SPECTRAL_C_TYPES_H
