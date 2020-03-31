#include "fft3d.h"

FFT3d::FFT3d(Data *d) {
    vectorTransform_ = false;
    int *dims = d->get_dimensions();
    fPx_ = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                d->get_in(), d->get_out(), FFTW_MEASURE);
    bPx_ = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                d->get_out(), d->get_in(), FFTW_MEASURE);
}

FFT3d::FFT3d(VectorField *v) {
    vectorTransform_ = true;
    int *dims = v->get_dimensions();
    fPx_ = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                v->get_in_x(), v->get_out_x(), FFTW_MEASURE);
    fPy_ = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                v->get_in_y(), v->get_out_y(), FFTW_MEASURE);
    fPz_ = fftw_plan_dft_r2c_3d(dims[0], dims[1], dims[2],
                                v->get_in_z(), v->get_out_z(), FFTW_MEASURE);
    bPx_ = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                v->get_out_x(), v->get_in_x(), FFTW_MEASURE);
    bPy_ = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                v->get_out_y(), v->get_in_y(), FFTW_MEASURE);
    bPz_ = fftw_plan_dft_c2r_3d(dims[0], dims[1], dims[2],
                                v->get_out_z(), v->get_in_z(), FFTW_MEASURE);

}

FFT3d::~FFT3d() {
    fftw_destroy_plan(fPx_);
    fftw_destroy_plan(fPy_);
    fftw_destroy_plan(fPz_);
    fftw_destroy_plan(bPx_);
    fftw_destroy_plan(bPy_);
    fftw_destroy_plan(bPz_);
}

void FFT3d::forward() {
    fftw_execute(fPx_);
    if (vectorTransform_) {
        fftw_execute(fPy_);
        fftw_execute(fPz_);
    }
}

void FFT3d::backward() {
    fftw_execute(bPx_);
    if (vectorTransform_) {
        fftw_execute(bPy_);
        fftw_execute(bPz_);
    }
}
