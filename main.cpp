//
// Created by finn on 3/1/20.
//

#include <iostream>
#include <array>
#include <complex.h>
#include <fftw3.h>
#include <math.h>
#include <stdio.h>

#include "data.h"
#include "fft3d.h"

// Used everywhere to determine ground truths.
// Complex arrays have N/2 + 1 datapoints.
// Real arrays have N datapoints.
static const int Nx = 64;
static const int Ny = 64;
static const int Nz = 64;

static const double X_RANGE = 2 * M_PI;
static const double Y_RANGE = 2 * M_PI;
static const double Z_RANGE = 2 * M_PI;

int main() {
  // Defining datastructures for FFT
  Data d = Data(Nx, Ny, Nz);

  FFT3d f = FFT3d(&d);

  // Initializing input data - initial conditions will go here
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      for (int z = 0; z < Nz; z++) {
        double tx = x * X_RANGE / Nx;
        double ty = y * Y_RANGE / Ny;
        double tz = z * Z_RANGE / Nz;

        double v = 0;
        if ((y == int(Ny / 3) && x == int(Nx / 3)) || (y == int(Ny * 2 / 3) &&  x == int(Nx * 2 / 3))) {
                v = 1;
        }

        d.set_in(x, y, z, v);
      }
    }
  }



  f.forward();

  d.save("log.csv");
  f.backward();
  d.normalize();
  d.save("reverse.csv");
  return 0;
}