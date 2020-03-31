//
// Created by finn on 3/31/20.
//

#include "vector_field.h"
#include <iostream>

VectorField::VectorField(int Nx, int Ny, int Nz) {
    _data[0] = new Data(Nx, Ny, Nz);
    _data[1] = new Data(Nx, Ny, Nz);
    _data[2] = new Data(Nx, Ny, Nz);
    _dimensions[0] = Nx;
    _dimensions[1] = Ny;
    _dimensions[2] = Nz;
}

VectorField::~VectorField() {
    std::cout << "Deleting vector field of size 3x" << _dimensions[0] << "x"
              << _dimensions[1] << "x" << _dimensions[2] << std::endl;
    delete (_data[0]);
    delete (_data[1]);
    delete (_data[2]);
}

void VectorField::set_in(int x, int y, int z, double *val) {
    _data[0]->set_in(x, y, z, val[0]);
    _data[1]->set_in(x, y, z, val[1]);
    _data[2]->set_in(x, y, z, val[2]);
}

void VectorField::set_out(int x, int y, int z, std::complex<double> *val) {
    _data[0]->set_out(x, y, z, val[0]);
    _data[1]->set_out(x, y, z, val[1]);
    _data[2]->set_out(x, y, z, val[2]);
}

// Value of vector at (x, y, z)
double *VectorField::get_in(int x, int y, int z) {
    double v0 = _data[0]->get_in(x, y, z);
    double v1 = _data[1]->get_in(x, y, z);
    double v2 = _data[2]->get_in(x, y, z);
    return new double[3]{v0, v1, v2};
}


double VectorField::mag_in(int x, int y, int z) {
    double mag = 0;
    mag += pow(_data[0]->get_in(x, y, z), 2);
    mag += pow(_data[1]->get_in(x, y, z), 2);
    mag += pow(_data[2]->get_in(x, y, z), 2);
    return pow(mag, 0.5);
}

fftw_complex *VectorField::get_out(int x, int y, int z) {
    fftw_complex *retVal[3];
    retVal[0] = _data[0]->get_out(x, y, z);
    retVal[1] = _data[1]->get_out(x, y, z);
    retVal[2] = _data[2]->get_out(x, y, z);
    return *retVal;
}

int *VectorField::get_dimensions() { return _dimensions; }

void VectorField::normalize() {
    _data[0]->normalize();
    _data[1]->normalize();
    _data[2]->normalize();
}

void VectorField::save(char *filenameX, char *filenameY, char *filenameZ) {
    _data[0]->save(filenameX);
    _data[1]->save(filenameY);
    _data[2]->save(filenameZ);
}

double *VectorField::get_in_x() {
    return _data[0]->get_in();
}

double *VectorField::get_in_y() {
    return _data[1]->get_in();
}

double *VectorField::get_in_z() {
    return _data[2]->get_in();
}

fftw_complex *VectorField::get_out_x() {
    return _data[0]->get_out();
}

fftw_complex *VectorField::get_out_y() {
    return _data[1]->get_out();
}

fftw_complex *VectorField::get_out_z() {
    return _data[2]->get_out();
}
