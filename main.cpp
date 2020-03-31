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
  VectorField v = VectorField(Nx, Ny, Nz);

  FFT3d f = FFT3d(&v);

  // Initializing input data - initial conditions will go here
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      for (int z = 0; z < Nz; z++) {
          double val[3] = {0, 0, 0};
          if (x == int(Nx / 2)) {
              std::cout << "HII" << std::endl;
              val[0] = 1;
              val[1] = 2;
              val[2] = 3;
          }
          v.set_in(x, y, z, val);
      }
    }
  }

  f.forward();

  v.save("vx.csv", "vy.csv", "vz.csv");
  f.backward();

  v.normalize();
  v.save("vx1.csv", "vy1.csv", "vz1.csv");
  return 0;
}