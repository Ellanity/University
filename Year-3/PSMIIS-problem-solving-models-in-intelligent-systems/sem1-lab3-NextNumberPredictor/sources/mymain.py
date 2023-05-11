import copy
import math
from random import randint

import numpy as np
# from json import load, dump




def countSecondW(W2, standard, Y, Z, alpha):
    return delta(W2, alpha_matrix(alpha_matrix(transp(Y), Z - standard), alpha))


def hidden_error(W2, gamma):  # супер частный случай для этой нейронки
    return alpha_matrix(W2, gamma)


# (W1, buffer, training_sequences[train][col_training_matrix + k + pred], Z[0][0], X, Y, alpha)
def countFirstW(W1, W2, standard, Z, X, Y, alpha):
    error = hidden_error(W2, Z - standard)
    devtos = transp(der_act(multipl(transp(X), W1)))
    delW1 = alpha_matrix(multipl(X, transp(hadamard(error, devtos))), alpha)
    return delta(W1, delW1)


class NeuralNetwork:
    def __init__(self):
        # standard
        self.__layer_input = []
        self.__layer_hidden = []
        self.__layer_output = []
        self.__layer_context = []
        self.__weights_input_hidden = []
        self.__weights_hidden_output = []
        # self.__weights_output_context = []
        # self.__weights_context_hidden = []
        # training
        self.__sequences_for_training = []
        self.__numbers_to_train_quantity = 0
        self.__max_RMS = 0
        self.__current_RMS = 0
        self.__learning_rate = 0
        self.__max_iterations_quantity = 0
        self.__subsequence_length = 0
        self.__train_iteration_num = 0
        # prediction
        self.__numeric_sequence_length = 0
        self.__numeric_sequence = np.array([])

    def set_numeric_sequence_length(self, numeric_sequence_length):
        self.__numeric_sequence_length = numeric_sequence_length

    def set_numeric_sequence(self, numeric_sequence):
        self.__numeric_sequence = np.array(numeric_sequence)

    def get_output(self):
        return self.__layer_output

    def __activation_function(self, layer):
        for i in range(len(layer)):
            layer[i] = math.sin(math.atan(layer[i]))
        return layer

    def __derivative_activation_function(self, layer):
        for i in range(len(layer)):
            layer[i] = -(layer[i] ** 2) / ((layer[i] + 1) ** (3 / 2)) + 1 / (layer[i] ** 2 + 1) ** (1 / 2)
        return layer
        # for i in range(len(weights)):
        #     for j in range(len(weights[0])):
        #         weights[i][j] = -(weights[i][j] ** 2) /
        #         ((weights[i][j] + 1) ** (3 / 2)) + 1 / (weights[i][j] ** 2 + 1) ** (1 / 2)
        # return weights

    def create_network(self, **kwargs):
        try:
            settings = kwargs.get("settings")
            self.__numbers_to_train_quantity = settings.get("numbers_to_train_quantity")
            self.__max_RMS = settings.get("max_RMS")
            self.__learning_rate = settings.get("learning_rate")
            self.__max_iterations_quantity = settings.get("max_iterations_quantity")
            self.__subsequence_length = settings.get("subsequence_length")
        except Exception as ex:
            print("Training is not possible", ex)
            return

        # splitting into subsequences with overlay
        if self.__numeric_sequence_length < self.__subsequence_length:
            self.__subsequence_length = self.__numeric_sequence_length
        for i in range(self.__numeric_sequence_length - self.__subsequence_length + 1):
            # print(i, self.__numeric_sequence_length + i, self.__numeric_sequence[i:self.__subsequence_length + i])
            self.__sequences_for_training.append(self.__numeric_sequence[i:self.__subsequence_length + i])
        # print(self.__sequences_for_training)

        weights_input_hidden_width = weights_input_hidden_height = self.__subsequence_length - 1
        self.__weights_input_hidden = [[(randint(int(-1e5), int(1e5)) / 1e5) for j in range(weights_input_hidden_width)] for i in range(weights_input_hidden_height)]
        weights_hidden_output_width, weights_hidden_output_height = 1, self.__subsequence_length
        self.__weights_hidden_output = [[(randint(int(-1e5), int(1e5)) / 1e5) for j in range(weights_hidden_output_width)] for i in range(weights_hidden_output_height)]
        # print(self.__weights_input_hidden, "\n\n", self.__weights_hidden_output)

    def normalizeWeights(self, weights):
        weights_copy = np.asarray(weights)
        for i in range(0, weights_copy.shape[0]):
            sum_of_squares = 0
            for k in weights_copy[i]:
                sum_of_squares += k * k
            module = math.sqrt(sum_of_squares)
            for j in range(0, weights_copy.shape[1]):
                weights_copy[i][j] /= module

    def train(self):
        while self.__current_RMS > self.__max_RMS or self.__current_RMS == 0:
            self.__current_RMS = 0
            self.__layer_context = [0]
            for input_sequence in self.__sequences_for_training:
                # Create layers
                standard = float(input_sequence[-1:])
                self.__layer_input = np.array(input_sequence[:-1])
                # print(standard, self.__layer_input)
                self.__layer_hidden = np.array(self.__layer_input) @ np.array(self.__weights_input_hidden)
                self.__layer_hidden = np.append(self.__layer_hidden, self.__layer_context)
                self.__layer_output = np.array(self.__activation_function(self.__layer_hidden)) @ np.array(self.__weights_hidden_output)
                self.__layer_context = copy.deepcopy(self.__layer_output)
                # Calculate rms and delta between last layer and standard
                rms = standard - self.__layer_output
                self.__current_RMS += float(rms)
                # Update weights
                error = self.__weights_hidden_output[:-1] * rms
                der_func = np.matrix(self.__derivative_activation_function(self.__layer_hidden[:-1])).T
                hadamar = np.matrix(np.multiply(error, der_func))
                delta_weights_input_hidden = np.matmul(hadamar, np.matrix(self.__layer_input)) * self.__learning_rate
                new_weights_input_hidden = np.matrix(self.__weights_input_hidden) - delta_weights_input_hidden
                delta_weights_hidden_output = np.matrix(self.__layer_hidden).T * rms * self.__learning_rate
                new_weights_hidden_output = np.matrix(self.__weights_hidden_output) - delta_weights_hidden_output
                self.__weights_input_hidden = copy.deepcopy(new_weights_input_hidden)
                self.__weights_hidden_output = copy.deepcopy(new_weights_hidden_output)
                self.normalizeWeights(self.__weights_input_hidden)
                self.normalizeWeights(self.__weights_hidden_output)
                # Output
                self.__train_iteration_num += 1
                # print("\nweights:\n", self.__weights_input_hidden, "\ndelta:\n", delta_weights_input_hidden)
                print(f"\rmax error: {self.__max_RMS:.{10}f} | "
                      f"current error: {self.__current_RMS:.{10}f} | "
                      f"Iterations: {self.__train_iteration_num}", end="")

            if self.__train_iteration_num > self.__max_iterations_quantity:
                break

    def predict(self):
        pass


def main():
    network = NeuralNetwork()
    numeric_sequence_length = 4  # int(input("Length of the numeric sequence [>=2]: "))
    numeric_sequence_length = max(numeric_sequence_length, 2)
    numeric_sequence = [1, 3, 5, 7]  # []
    # for i in range(0, numeric_sequence_length):
    #     numeric_sequence.append(float(input("_/: ")))
    print(*numeric_sequence)
    network.set_numeric_sequence_length(numeric_sequence_length=numeric_sequence_length)
    network.set_numeric_sequence(numeric_sequence=numeric_sequence)

    print("1 - training\n2 - prediction")
    choice = 1  # int(input())
    if choice == 1:
        networkSettings = {
            "numbers_to_train_quantity": 8,
            "max_RMS": 0.0001,
            "learning_rate": 0.001,
            "max_iterations_quantity": 10000,
            "subsequence_length": 4,
        }
        network.create_network(settings=networkSettings)
        network.train()
    elif choice == 2:
        network.predict()
        # print(network.get_output())


if __name__ == "__main__":
    main()
