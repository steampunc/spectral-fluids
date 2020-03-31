#include "fft3d.h"

FFT3d::FFT3d(Data* d) {
  int* dims = d->get_dimensions();
  _backPlan = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
      d->get_out(), d->get_in(), FFTW_MEASURE);
  _forwardPlan = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
      d->get_in(), d->get_out(), FFTW_MEASURE);
}

FFT3d::~FFT3d(){
  fftw_destroy_plan(_forwardPlan);
  fftw_destroy_plan(_backPlan);
}

void FFT3d::forward() {
  fftw_execute(_forwardPlan);
}

void FFT3d::backward() {
  fftw_execute(_backPlan);
}
