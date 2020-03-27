import math
import numpy as np


def buildMatrices(omega, k1, k2, layers):
    print('In Build')
    for layer in layers:
        # layer = layers[num]
        e = layer.epsilon
        u = layer.mu
        imaginary = complex(0, 1)
        omega = omega * imaginary
        maxwell_matrices = []
        m11 = omega * (-(e[2][0]*k1/e[2][2]) - (k2*u[1][2]/u[2][2]))
        m12 = omega * (-(e[2][1]*k1/e[2][2]) + (k1*u[1][2]/u[2][2]))
        m13 = omega * ((k1*k2/e[2][2]) + u[1][0] -
                       (u[1][2]*u[2][0]/u[2][2]))
        m14 = omega * ((-k1 ** 2/e[2][2]) + u[1]
                       [1] - (u[1][2]*u[2][1]/u[2][2]))
        m21 = omega * (-(e[2][0]*k2/e[2][2]) - (k2*(u[0][2]/u[2][2])))
        m22 = omega * (-(e[2][1]*k2/e[2][2]) - (k1*u[0][2]/u[2][2]))
        m23 = omega * ((k2 ** 2/e[2][2]) - u[0]
                       [0] + (u[0][2]*u[2][0]/u[2][2]))
        m24 = omega * (-(k1*k2/e[2][2]) - u[0]
                       [1] + (u[0][2]*u[2][1]/u[2][2]))
        m31 = omega * (-e[1][0] + (e[1][2]*e[2][0] /
                                   e[2][2]) - (k1*k2/u[2][2]))
        m32 = omega * (-e[1][1] + (e[1][2]*e[2][1] /
                                   e[2][2]) + (k1 ** 2/u[2][2]))
        m33 = omega * (-(e[1][2]*k2/e[2][2]) - (k1*u[2][0]/u[2][2]))
        m34 = omega * ((e[1][2]*k1/e[2][2]) - (k1*u[2][1]/u[2][2]))
        m41 = omega * (e[0][0] - (e[0][2]*e[2][0] /
                                  e[2][2]) - (k2 ** 2/u[2][2]))
        m42 = omega * (e[0][1] - (e[0][2]*e[2][1] /
                                  e[2][2]) + (k1*k2/u[2][2]))
        m43 = omega * ((e[0][2]*k2/e[2][2]) - (k2*u[2][0]/u[2][2]))
        m44 = omega * (-(e[0][2]*k1/e[2][2]) - (k2*u[2][1]/u[2][2]))
        maxwell_matrix = np.array([[m11,  m12, m13, m14],
                                   [m21,  m22, m23, m24],
                                   [m31,  m32, m33, m34],
                                   [m41,  m42, m43, m44]])
        # maxwell_matrix = map(lambda x: x * omega, maxwell_matrix)
        # maxwell_matrix = map(lambda x: map(
        #     lambda y: complex(y, 1), x), maxwell_matrix)
        maxwell_matrices.append(maxwell_matrix)
        m = list(maxwell_matrix)
        # print("layer" + str(num+1) + ": ")
        print(m)
        # print("\n")
    return maxwell_matrices
