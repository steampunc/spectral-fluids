import pandas as pd 
import math
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np

Nx = 64
Ny = 64
Nz = 64
z_index = 0

x_range = 2 * np.pi
y_range = 2 * np.pi
z_range = 2 * np.pi

def freq_spacing(domain_size, num_points):
    return 2 * np.pi / float(domain_size)

def realIndex(x, y, z):
    return (x * Ny + y) * Nz + z

def FFTIndex(x, y, z):
    return (x * Ny + y) * (Nz / 2 + 1) + z

def plotReal(values):
    Z = np.zeros(shape=(Ny, Nx))

    X = np.arange(0, Nx, 1)
    Y = np.arange(0, Ny, 1)

    for x in X:
        for y in Y:
            dbg = values[realIndex(x, y, z_index)]
            Z[y][x] = dbg

    x_coords = np.arange(0, x_range, float(x_range) / float(Nx))
    y_coords = np.arange(0, y_range, float(y_range) / float(Ny))

    fig, ax = plt.subplots()
    im = ax.imshow(Z, interpolation='bilinear', cmap=cm.RdYlGn,
                   origin='lower', extent=[x_coords.min(), x_coords.max(), y_coords.min(), y_coords.max()],
                   vmax=Z.max(), vmin=Z.min())

    plt.colorbar(im, ax=ax)
    plt.show()


def plotFFT(values):
    x_df = freq_spacing(x_range, Nx)
    y_df = freq_spacing(y_range, Ny)

    kX = np.arange(-Nx, Nx * x_df, x_df)
    kY = np.arange(-Ny, Ny * y_df, y_df)
    Z = np.zeros(shape=(2 * Ny, 2 * Nx))

    X = np.arange(-Nx + 1, Nx, 1)
    Y = np.arange(-Ny + 1, Ny, 1)

    for x in X:
        for y in Y:
            dbg = values[FFTIndex(abs(x), abs(y), z_index)]
            Z[y][x] = dbg

    fig, ax = plt.subplots()
    im = ax.imshow(Z, interpolation='none', cmap=cm.RdYlGn,
                   origin='lower', extent=[kX.min(), kX.max(), kY.min(), kY.max()],
                   vmax=Z.max(), vmin=Z.min())

    plt.colorbar(im, ax=ax)
    plt.show()

df = pd.read_csv('cmake-build-debug/log.csv', sep=", ", engine="python") 
df2 = pd.read_csv('cmake-build-debug/reverse.csv', sep=", ", engine="python") 

plotReal(df["in"])
plotFFT(df["out_r"])
plotFFT(df["out_mag"])
plotReal(df2["in"])
