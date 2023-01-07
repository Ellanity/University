import numpy as np
import math
import copy


class LabCalculator:

    def __init__(self):
        self.ALPHA = 0.2

    def matrix_multiplying(self, matrix_first, matrix_second):
        matrix_first = copy.deepcopy(matrix_first)
        matrix_second = copy.deepcopy(matrix_second)
        transposed_matrix_second = list(zip(*matrix_second))
        return [[sum(element_1 * element_2 for element_1, element_2 in zip(row_1, col_2)) for col_2 in
                 transposed_matrix_second] for row_1 in matrix_first]

    def activation_function(self, num_input):
        if num_input < 0:
            num_result = self.ALPHA * (math.exp(num_input) - 1)
            return num_result
        return num_input

    def activation_function_dif(self, num_input):
        if num_input <= 0:
            return self.activation_function(num_input) + self.ALPHA
        return 1

    def sigmoid_function(self, num_input):
        return 1 / (1 + math.exp((-1) * num_input))

    def sigmoid_function_def(self, num_input):
        return self.sigmoid_function(num_input) * (1 - self.sigmoid_function(num_input))

    def factorial(self, num_input):
        num_result = 1
        for i in range(1, num_input + 1):
            num_result *= i
        return num_result

    def get_fibonacci_series(self, quantity_of_nums):
        sequence = []
        for index_of_primary_fill_ in range(quantity_of_nums):
            sequence.append(1)
        for index_of_fibonacci_ in range(2, quantity_of_nums):
            sequence[index_of_fibonacci_] = sequence[index_of_fibonacci_ - 1] + sequence[index_of_fibonacci_ - 2]
        return sequence

    def get_factorial_function(self, quantity_of_nums):
        sequence = []
        for index_of_primary_fill_ in range(quantity_of_nums):
            sequence.append(1)
        for index_of_factorial_ in range(quantity_of_nums):
            sequence[index_of_factorial_] = self.factorial(index_of_factorial_ + 1)
        return sequence

    def get_periodic_function(self, quantity_of_nums):
        sequence = []
        for index_of_primary_fill_ in range(quantity_of_nums):
            if index_of_primary_fill_ % 2 == 0:
                sequence.append(1)
            else:
                sequence.append(0)
        return sequence

    def create_matrix(self, sequence_, rows_, columns_):
        matrix_ = []
        for row_ in range(rows_):
            new_row_ = []
            for col_ in range(columns_):
                new_row_.append(sequence_[row_ + col_])
            matrix_.append(new_row_)
        return matrix_


class NeuralNetwork:

    def __init__(self):
        self.calc = LabCalculator()
        # structs 
        self.learning_matrix_window = None
        self.contexts_neurons_list = []
        self.weights_matrix_first = []
        self.weights_matrix_second = []
        self.sum_error = 0

    def __init_matrices(self, parameters):
        number_of_neurons_on_hidden_layer = parameters.get("L")
        for init_weights_matrix_first_index_row in range(parameters.get("L") + 1):
            new_row = []
            for init_weights_matrix_first_index_col in range(number_of_neurons_on_hidden_layer):
                weight = np.random.randn() / 10
                new_row.append(weight)
            self.weights_matrix_first.append(new_row)

        for init_weights_matrix_second_index_row in range(number_of_neurons_on_hidden_layer):
            weight = np.random.randn() / 10
            self.weights_matrix_second.append([weight])

    def train_network(self, parameters):
        self.calc.ALPHA = parameters.get("ALPHA")
        self.learning_matrix_window = self.calc.create_matrix(parameters.get("selected_sequence"),
                                                              parameters.get("p"),
                                                              parameters.get("L"))
        self.contexts_neurons_list = [[0] for _ in range(len(self.learning_matrix_window))]
        self.__init_matrices(parameters)
        # TRAINING
        self.sum_error = parameters.get("E") + 1
        iteration = 0
        while self.sum_error > parameters.get("E") \
                and iteration < parameters.get("limit_of_iterations"):
            iteration += 1
            self.__iteration(parameters)
            print("\r", "training iteration ", iteration, " ", self.sum_error, end="")
        print("\n")

        with open("weights_matrix_first", 'w') as weight_matrix_file:
            np.save("weights_matrix_first", self.weights_matrix_first)
            weight_matrix_file.close()
        with open("weights_matrix_second", 'w') as weight_matrix_file:
            np.save("weights_matrix_second", self.weights_matrix_second)
            weight_matrix_file.close()

    def __iteration(self, parameters):
        self.sum_error = 0
        for standard_index in range(len(self.learning_matrix_window) - 1):
            input_layer_neurons = np.array(
                self.learning_matrix_window[standard_index] + self.contexts_neurons_list[standard_index])
            hidden_layer_neurons = np.matmul(input_layer_neurons, np.array(self.weights_matrix_first))
            for activating_index in range(len(hidden_layer_neurons)):
                hidden_layer_neurons[activating_index] = \
                    self.calc.sigmoid_function(hidden_layer_neurons[activating_index])
            output_layer_neurons = np.matmul(hidden_layer_neurons, np.array(self.weights_matrix_second))
            output_layer_neurons[0] = self.calc.sigmoid_function(output_layer_neurons[0])

            self.contexts_neurons_list[standard_index][0] = output_layer_neurons[0]

            intended_outcome = self.learning_matrix_window[standard_index + 1][parameters.get("L") - 1]
            error = output_layer_neurons[0] - intended_outcome

            # MATRICES CHANGES
            x_trans_weights_matrix_second_trans = np.matmul(np.array([input_layer_neurons]).T,
                                                                      np.array(self.weights_matrix_second).T)
            inactive_hidden_layer = np.matmul([input_layer_neurons], self.weights_matrix_first)
            deactivated_hidden_layer = []

            def first_matrix_changes():
                for deactivating_index in range(len(inactive_hidden_layer[0])):
                    deactivated_hidden_layer.append(
                        self.calc.sigmoid_function_def(inactive_hidden_layer[0][deactivating_index]))
                x_trans_weights_matrix_second_trans_DHL = \
                    np.array(self.calc.matrix_multiplying(list(x_trans_weights_matrix_second_trans),
                                                          [deactivated_hidden_layer]))
                for multiplying_index in range(len(x_trans_weights_matrix_second_trans_DHL)):
                    x_trans_weights_matrix_second_trans_DHL[multiplying_index][0] *= self.calc.ALPHA
                    x_trans_weights_matrix_second_trans_DHL[multiplying_index][0] *= error

                self.weights_matrix_first = np.array(self.weights_matrix_first) - x_trans_weights_matrix_second_trans_DHL

            def second_matrix_changes():
                deactivated_output_layer = [0]
                H_weights_matrix_second = np.matmul(hidden_layer_neurons, self.weights_matrix_second)
                deactivated_output_layer[0] = self.calc.sigmoid_function_def(H_weights_matrix_second[0])
                hl_dol_iters = np.matmul(np.array([hidden_layer_neurons]).T, np.array([deactivated_output_layer]))

                for multiplying_index in range(len(hl_dol_iters)):
                    hl_dol_iters[multiplying_index] *= self.calc.ALPHA
                    hl_dol_iters[multiplying_index] *= error

                self.weights_matrix_second = self.weights_matrix_second - hl_dol_iters

            first_matrix_changes()
            second_matrix_changes()

        for standard_index in range(len(self.learning_matrix_window) - 1):
            input_layer_neurons = np.array(
                self.learning_matrix_window[standard_index] + self.contexts_neurons_list[standard_index])
            hidden_layer_neurons = np.matmul(input_layer_neurons, np.array(self.weights_matrix_first))
            output_layer_neurons = np.matmul(hidden_layer_neurons, np.array(self.weights_matrix_second))

            self.contexts_neurons_list[standard_index][0] = output_layer_neurons[0]

            intended_outcome = self.learning_matrix_window[standard_index + 1][parameters.get("L") - 1]
            error = output_layer_neurons[0] - intended_outcome
            self.sum_error += error ** 2

    def predict_next_number(self, sequence):
        self.weights_matrix_first = np.array([])
        self.weights_matrix_second = np.array([])
        with open("weights_matrix_first.npy", "r") as weight_matrix_file:
            self.weights_matrix_first = np.load("weights_matrix_first.npy")
            weight_matrix_file.close()
        with open("weights_matrix_second.npy", "r") as weight_matrix_file:
            self.weights_matrix_second = np.load("weights_matrix_second.npy")
            weight_matrix_file.close()

        sequence.append(0)
        input_layer_neurons = np.array(sequence)
        # print(sequence)
        hidden_layer_neurons = np.matmul(input_layer_neurons, self.weights_matrix_first)
        output_layer_neurons = np.matmul(hidden_layer_neurons, self.weights_matrix_second)
        num_result = math.fabs(output_layer_neurons[0])
        return num_result


def main_menu():
    def get_sequence_of_numbers(str_number):
        sequence_of_numbers = []
        if str_number == '1':
            sequence_of_numbers = neural_network.calc.get_fibonacci_series(quantity_of_numbers_in_sequence)
        elif str_number == '2':
            sequence_of_numbers = neural_network.calc.get_factorial_function(quantity_of_numbers_in_sequence)
        elif str_number == '3':
            sequence_of_numbers = neural_network.calc.get_periodic_function(quantity_of_numbers_in_sequence)
        else:
            print("No such sequence")
            exit()
        return sequence_of_numbers

    neural_network = NeuralNetwork()
    start_choice = input("Select the operating mode:\n"
                         "1 - Training\n"
                         "2 - Prediction\n"
                         "3 - Exit\n")
    if start_choice == '1':
        sequence_type = input("Select sequence type:\n"
                              "1 - Fibonacci series\n"
                              "2 - Factorial function\n"
                              "3 - Periodic function\n")
        quantity_of_numbers_in_sequence = int(input("Enter the number of items in the selected sequence:\n"))
        network_training_parameters = {
            "E": 0.01,
            "ALPHA": 0.2,
            "L": 0,
            "p": 0,
            "limit_of_iterations": 100000,
        }
        selected_sequence = get_sequence_of_numbers(sequence_type)
        print(*selected_sequence)
        network_training_parameters["selected_sequence"] = selected_sequence
        network_training_parameters["E"] = float(input("Enter the error: "))
        network_training_parameters["ALPHA"] = float(input("Enter the learning coefficient: "))
        network_training_parameters["L"] = int(input("Enter the number of columns in the learning matrix: "))
        network_training_parameters["p"] = int(input("Enter the number of rows in the learning matrix: "))
        network_training_parameters["limit_of_iterations"] = int(
            input("Enter the number of training steps that the network can complete: "))
        neural_network.train_network(network_training_parameters)
        print(neural_network.predict_next_number(selected_sequence[(0 - network_training_parameters["L"]):]))

    elif start_choice == '2':
        sequence_type = input("Select sequence type:\n"
                              "1 - Fibonacci series\n"
                              "2 - Factorial function\n"
                              "3 - Periodic function\n")
        quantity_of_numbers_in_sequence = int(input("Enter the number of items in the selected sequence: "))
        selected_sequence = get_sequence_of_numbers(sequence_type)
        print(*selected_sequence)
        quantity_of_numbers_in_prediction_window_row = int(
            input("Enter the number of columns in the learning matrix: "))
        print(
            neural_network.predict_next_number(selected_sequence[(0 - quantity_of_numbers_in_prediction_window_row):]))
    else:
        exit()


if __name__ == "__main__":
    main_menu()
