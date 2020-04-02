import math
import numpy as np


# Classes for storing structure data
class Structure:

    # Sub class for defining each layer
    class Layer:
        # Instance variables for each Layer object
        def __init__(self, name, length, epsilon, mu):
            print('Instanciating Layer')
            self.name = name
            self.length = length
            self.epsilon = epsilon
            self.mu = mu

        def __str__(self):
            return self.name + ': ' + str(self.length)

    # Instance variables for each Structure object
    def __init__(self, num, omega, k1, k2):
        print('Instanciating Structure')
        self.num = num
        self.omega = omega
        self.k1 = k1
        self.k2 = k2
        self.layers = []

    def printLayers(self):
        print('LAYERS: ')
        for layer in self.layers:
            print(layer)

    def removeLayer(self, n):
        print('Removing Layer')
        self.layers.pop(n)

    # Method for adding a layer to the structure
    def addLayer(self, name, length, epsilon, mu):
        print('Adding Layer')
        l = self.Layer(name, length, epsilon, mu)
        self.layers.append(l)

    def insertLayer(self, name, length, epsilon, mu, n):
        print('Inserting Layer')
        l = self.Layer(name, length, epsilon, mu)
        self.layers.insert(n, l)

    # Create the maxwell matrices
    def buildMatrices(self):
        print('Building Maxwell')
        maxwell_matrices = []
        for layer in self.layers:
            # layer = layers[num]
            e = layer.epsilon
            u = layer.mu
            k1 = self.k1
            k2 = self.k2
            imaginary = complex(0, 1)
            omega = self.omega * imaginary
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
            # m = list(maxwell_matrix)
            # print("layer" + str(num+1) + ": ")
            # print("\n")
        self.maxwell = maxwell_matrices
        return maxwell_matrices

# Test code
def test():
    s = Structure(3, 1, 1, 1)
    e = np.array([[1,1,1],
                [1,1,1],
                [1,1,1]])
    u = np.array([[1,1,1],
                [1,1,1],
                [1,1,1]])
    s.addLayer('Ambient Left', 10, e, u)
    s.addLayer('Layer 1', 7, e, u)
    s.addLayer('Ambient Right', 10, e, u)
    s.printLayers()
    s.removeLayer(1)
    s.printLayers()
    s.insertLayer('Layer 1', 7, e, u, 1)
    s.printLayers()
    m = s.buildMatrices()
    print('Number of Layers: ' + str(len(m)))
    print('Dimension of 1st layer: ' + str(m[0].shape))
    print('Dimension of 2nd layer: ' + str(m[1].shape))
    print('Dimension of 3rd layer: ' + str(m[2].shape))
    eig = np.linalg.eig(m)
    print('Eigenvalues: ' + str(eig[0]))
    print('Eigenvectors: ' + str(eig[1]))

test()