import math


class Maxwell:
    def buildLayers(self, num_layers, z_values):
        for l in range(self.num_layers):
            # layer_name = "layer_" + str(l)
            # print(layer_name + ": ")
            if l != 1:  # guide layers
                layer = Layer(10, [[1.5, 0, 0], [0, 8, 0], [0, 0, 1]], [
                              [4, 0, 0], [0, 1, 0], [0, 0, 1]])
            else:  # slab layer
                layer = Layer(7, [[8, 0, 0], [0, 1.5, 0], [0, 0, 1]], [
                              [1, 0, 0], [0, 4, 0], [0, 0, 1]])

            # layer = Layer(input("   Enter Length of layer: "),
            #               input("   Enter epsilon values: "),
            #               input("   Enter mu values: "))
            # print("\n")
            if l != 0:
                self.z_values.append(z_values[l-1]+int(layer.length))
            else:
                list_of_layers = [layer] * num_layers
            list_of_layers[l] = layer
        return list_of_layers

    def buildMatrices(self, omega, k1, k2, layers, n):
        for num in range(n):
            layer = layers[num]
            e = layer.epsilon
            u = layer.mu
            imaginary = complex(0,1)
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
            maxwell_matrix = [[m11,  m12, m13, m14],
                              [m21,  m22, m23, m24],
                              [m31,  m32, m33, m34],
                              [m41,  m42, m43, m44]]
            # maxwell_matrix = map(lambda x: x * omega, maxwell_matrix)
            # maxwell_matrix = map(lambda x: map(
            #     lambda y: complex(y, 1), x), maxwell_matrix)
            maxwell_matrices.append(maxwell_matrix)
            m = list(maxwell_matrix)
            print("layer" + str(num+1) + ": ")
            print(m)
            print("\n")
        return maxwell_matrices

    def __init__(self):
        self.num_layers = 3  # input("Enter the Number of Layers: ")
        self.interfaces = self.num_layers + 1
        self.z_values = []
        self.z_values.append(0)
        self.list_of_layers = self.buildLayers(self.num_layers, self.z_values)
        self.omega = 0.398  # input("Enter omega value: ")
        self.k1 = 0.5  # input("Enter k1 value: ")
        self.k2 = 0.22  # input("Enter k2 value: ")
        self.list_of_matrices = list(self.buildMatrices(
            self.omega, self.k1, self.k2, self.list_of_layers, self.num_layers))


class Layer:
    def __init__(self, length, epsilon, mu):
        self.length = length
        self.epsilon = epsilon
        self.mu = mu


if __name__ == "__main__":
    Maxwell()
