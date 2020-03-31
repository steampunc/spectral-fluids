#ifndef SPECTRAL_C_LIBRARY_H
#define SPECTRAL_C_LIBRARY_H

#include <fftw3.h>
#include "data.h"

class FFT3d {
public:
  FFT3d(Data* d);
  ~FFT3d();
  void forward();
  void backward();
private:
  fftw_plan _forwardPlan, _backPlan;
};

#endif // SPECTRAL_C_LIBRARY_H
