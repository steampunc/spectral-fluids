#include "fft3d.h"

FFT3d::FFT3d(Data *d) {
    _vectorTransform = false;
    int *dims = d->get_dimensions();
    _fPx = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                d->get_in(), d->get_out(), FFTW_MEASURE);
    _bPx = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                d->get_out(), d->get_in(), FFTW_MEASURE);
}

FFT3d::FFT3d(VectorField *v) {
    _vectorTransform = true;
    int *dims = v->get_dimensions();
    _fPx = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                v->get_in_x(), v->get_out_x(), FFTW_MEASURE);
    _fPy = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                v->get_in_y(), v->get_out_y(), FFTW_MEASURE);
    _fPz = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                v->get_in_z(), v->get_out_z(), FFTW_MEASURE);
    _bPx = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                v->get_out_x(), v->get_in_x(), FFTW_MEASURE);
    _bPy = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                v->get_out_y(), v->get_in_y(), FFTW_MEASURE);
    _bPz = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                v->get_out_z(), v->get_in_z(), FFTW_MEASURE);

}

FFT3d::~FFT3d() {
    fftw_destroy_plan(_fPx);
    fftw_destroy_plan(_fPy);
    fftw_destroy_plan(_fPz);
    fftw_destroy_plan(_bPx);
    fftw_destroy_plan(_bPy);
    fftw_destroy_plan(_bPz);
}

void FFT3d::forward() {
    fftw_execute(_fPx);
    if (_vectorTransform) {
        fftw_execute(_fPy);
        fftw_execute(_fPz);
    }
}

void FFT3d::backward() {
    fftw_execute(_bPx);
    if (_vectorTransform) {
        fftw_execute(_bPy);
        fftw_execute(_bPz);
    }
}
