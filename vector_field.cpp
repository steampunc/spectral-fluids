//
// Created by finn on 3/31/20.
//

#include "vector_field.h"
#include <iostream>

VectorField::VectorField(int Nx, int Ny, int Nz) {
    data_[0] = new Data(Nx, Ny, Nz);
    data_[1] = new Data(Nx, Ny, Nz);
    data_[2] = new Data(Nx, Ny, Nz);
    dimensions_[0] = Nx;
    dimensions_[1] = Ny;
    dimensions_[2] = Nz;
}

VectorField::~VectorField() {
    std::cout << "Deleting vector field of size 3x" << dimensions_[0] << "x"
              << dimensions_[1] << "x" << dimensions_[2] << std::endl;
    delete (data_[0]);
    delete (data_[1]);
    delete (data_[2]);
}

void VectorField::set_in(int x, int y, int z, double *val) {
    data_[0]->set_in(x, y, z, val[0]);
    data_[1]->set_in(x, y, z, val[1]);
    data_[2]->set_in(x, y, z, val[2]);
}

void VectorField::set_out(int x, int y, int z, std::complex<double> *val) {
    data_[0]->set_out(x, y, z, val[0]);
    data_[1]->set_out(x, y, z, val[1]);
    data_[2]->set_out(x, y, z, val[2]);
}

// Value of vector at (x, y, z)
double *VectorField::get_in(int x, int y, int z) {
    double v0 = data_[0]->get_in(x, y, z);
    double v1 = data_[1]->get_in(x, y, z);
    double v2 = data_[2]->get_in(x, y, z);
    return new double[3]{v0, v1, v2};
}


double VectorField::mag_in(int x, int y, int z) {
    double mag = 0;
    mag += pow(data_[0]->get_in(x, y, z), 2);
    mag += pow(data_[1]->get_in(x, y, z), 2);
    mag += pow(data_[2]->get_in(x, y, z), 2);
    return pow(mag, 0.5);
}

fftw_complex *VectorField::get_out(int x, int y, int z) {
    fftw_complex *retVal[3];
    retVal[0] = data_[0]->get_out(x, y, z);
    retVal[1] = data_[1]->get_out(x, y, z);
    retVal[2] = data_[2]->get_out(x, y, z);
    return *retVal;
}

int *VectorField::get_dimensions() { return dimensions_; }

void VectorField::normalize() {
    data_[0]->normalize();
    data_[1]->normalize();
    data_[2]->normalize();
}

void VectorField::save(char *filenameX, char *filenameY, char *filenameZ) {
    data_[0]->save(filenameX);
    data_[1]->save(filenameY);
    data_[2]->save(filenameZ);
}

double *VectorField::get_in_x() {
    return data_[0]->get_in();
}

double *VectorField::get_in_y() {
    return data_[1]->get_in();
}

double *VectorField::get_in_z() {
    return data_[2]->get_in();
}

fftw_complex *VectorField::get_out_x() {
    return data_[0]->get_out();
}

fftw_complex *VectorField::get_out_y() {
    return data_[1]->get_out();
}

fftw_complex *VectorField::get_out_z() {
    return data_[2]->get_out();
}
