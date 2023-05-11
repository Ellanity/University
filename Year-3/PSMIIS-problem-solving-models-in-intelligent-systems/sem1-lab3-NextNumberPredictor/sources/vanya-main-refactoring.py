import numpy as np
import math
# import random
import copy


class LabCalculator:

    def __init__(self):
        self.ALPHA = 0.2

    def matrix_multiplying(self, matrix_1, matrix_2):
        matrix_1 = copy.deepcopy(matrix_1)
        matrix_2 = copy.deepcopy(matrix_2)
        transposed_matrix_2 = list(zip(*matrix_2))

        return [[sum(el1 * el2 for el1, el2 in zip(row_1, col_2)) for col_2 in transposed_matrix_2] for row_1 in
                matrix_1]

    def ELU(self, x_input):
        if x_input >= 0:
            return x_input
        if x_input < 0:
            result = self.ALPHA * (math.exp(x_input) - 1)
            return result

    def ELU_dif(self, x_input):
        if x_input > 0:
            return 1
        else:
            return self.ELU(x_input) + self.ALPHA

    def sigma_func(self, x_input):
        return 1 / (1 + math.exp((-1) * x_input))

    def sigma_func_def(self, x_input):
        return self.sigma_func(x_input) * (1 - self.sigma_func(x_input))

    def factorial(self, x_input):
        result = 1
        for i in range(1, x_input + 1):
            result *= i
        return result

    def get_fibonacci_series(self, quantity_of_nums):
        sequence = []
        for index_of_primary_fill in range(quantity_of_nums):
            sequence.append(1)
        for index_of_fibonacci in range(2, quantity_of_nums):
            sequence[index_of_fibonacci] = sequence[index_of_fibonacci - 1] + sequence[index_of_fibonacci - 2]
        return sequence

    def get_factorial_function(self, quantity_of_nums):
        sequence = []
        for index_of_primary_fill in range(quantity_of_nums):
            sequence.append(1)
        for index_of_factorial in range(quantity_of_nums):
            sequence[index_of_factorial] = self.factorial(index_of_factorial + 1)
        return sequence

    def get_periodic_function(self, quantity_of_nums):
        sequence = []
        for index_of_primary_fill in range(quantity_of_nums):
            if index_of_primary_fill % 2 == 0:
                sequence.append(1)
            else:
                sequence.append(0)
        return sequence

    def create_matrix_win(self, sequence, rows, columns):
        matrix_win = []
        for row in range(rows):
            new_row = []
            for col in range(columns):
                new_row.append(sequence[row + col])
            matrix_win.append(new_row)
        return matrix_win


class NeuralNetwork:

    def __init__(self):
        self.calc = LabCalculator()

    def train_network(self, parameters):
        # L = 4
        # p = len(selected_sequence) - L - 1
        # limit_of_iterations = 1000
        number_of_neurons_on_hidden_layer = 5
        self.calc.ALPHA = parameters.get("ALPHA")
        learning_matrix_win = self.calc.create_matrix_win(parameters.get("selected_sequence"),
                                                          parameters.get("p"),
                                                          parameters.get("L"))
        contexts_list = []
        for adding_contexts in range(len(learning_matrix_win)):
            new_context = [0]
            contexts_list.append(new_context)

        weights_matrix_first = []
        weights_matrix_second = []

        # ==================== ИНИЦИАЛИЗАЦИЯ ВЕСОВЫХ МАТРИЦ

        for init_weights_matrix_first_index_row in range(parameters.get("L") + 1):
            new_row = []
            for init_weights_matrix_first_index_col in range(number_of_neurons_on_hidden_layer):
                weight = np.random.randn() / 10
                new_row.append(weight)
            weights_matrix_first.append(new_row)

        for init_weights_matrix_second_index_row in range(number_of_neurons_on_hidden_layer):
            weight = np.random.randn() / 10
            weights_matrix_second.append([weight])

        # ==================== ОБУЧЕНИЕ

        sum_err = parameters.get("E") + 1
        current_iteration = 0
        while sum_err > parameters.get("E") and current_iteration < parameters.get("limit_of_iterations"):
            current_iteration += 1
            for sample_index in range(len(learning_matrix_win) - 1):
                input_layer = np.array(learning_matrix_win[sample_index] + contexts_list[sample_index])
                hidden_layer = np.matmul(input_layer, np.array(weights_matrix_first))
                for activating_index in range(len(hidden_layer)):
                    hidden_layer[activating_index] = self.calc.sigma_func(hidden_layer[activating_index])
                output_layer = np.matmul(hidden_layer, np.array(weights_matrix_second))
                output_layer[0] = self.calc.sigma_func(output_layer[0])

                contexts_list[sample_index][0] = output_layer[0]

                intended_outcome = learning_matrix_win[sample_index + 1][parameters.get("L") - 1]
                err = output_layer[0] - intended_outcome

                # ============ КОРРЕКТИРОВКА МАТРИЦ

                XT_weights_matrix_secondT = np.matmul(np.array([input_layer]).T, np.array(weights_matrix_second).T)
                inactive_hidden_layer = np.matmul([input_layer], weights_matrix_first)
                deactivated_hidden_layer = []
                for deactivating_index in range(len(inactive_hidden_layer[0])):
                    deactivated_hidden_layer.append(
                        self.calc.sigma_func_def(inactive_hidden_layer[0][deactivating_index]))
                Xt_weights_matrix_secondT_DHL = np.array(self.calc.matrix_multiplying(list(XT_weights_matrix_secondT),
                                                                                      [deactivated_hidden_layer]))
                for multiplying_index in range(len(Xt_weights_matrix_secondT_DHL)):
                    Xt_weights_matrix_secondT_DHL[multiplying_index][0] *= self.calc.ALPHA
                    Xt_weights_matrix_secondT_DHL[multiplying_index][0] *= err

                weights_matrix_first = np.array(weights_matrix_first) - Xt_weights_matrix_secondT_DHL

                deactivated_output_layer = [0]
                H_weights_matrix_second = np.matmul(hidden_layer, weights_matrix_second)
                deactivated_output_layer[0] = self.calc.sigma_func_def(H_weights_matrix_second[0])
                HL_DOL = np.matmul(np.array([hidden_layer]).T, np.array([deactivated_output_layer]))

                for multiplying_index in range(len(HL_DOL)):
                    HL_DOL[multiplying_index] *= self.calc.ALPHA
                    HL_DOL[multiplying_index] *= err

                weights_matrix_second = weights_matrix_second - HL_DOL

            sum_err = 0
            for sample_index in range(len(learning_matrix_win) - 1):
                input_layer = np.array(learning_matrix_win[sample_index] + contexts_list[sample_index])
                hidden_layer = np.matmul(input_layer, np.array(weights_matrix_first))
                output_layer = np.matmul(hidden_layer, np.array(weights_matrix_second))

                contexts_list[sample_index][0] = output_layer[0]

                intended_outcome = learning_matrix_win[sample_index + 1][parameters.get("L") - 1]
                err = output_layer[0] - intended_outcome
                sum_err += err ** 2
            print("\r", "training iteration ", current_iteration, " ", sum_err, end="")

        print("\n", str(predict_next(weights_matrix_first, weights_matrix_second, learning_matrix_win[-1])))

        with open("wm1", 'w') as weight_matrix_file:
            np.save("wm1", weights_matrix_first)
        with open("wm2", 'w') as weight_matrix_file:
            np.save("wm2", weights_matrix_second)


def predict_next(weights_matrix_first, weights_matrix_second, line):
    input_layer = np.array(line + [0])
    hidden_layer = np.matmul(input_layer, weights_matrix_first)
    output_layer = np.matmul(hidden_layer, weights_matrix_second)
    result = math.fabs(output_layer[0])
    return result


def main_menu():
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

        selected_sequence = []
        row_type = ""
        if sequence_type == '1':
            row_type = "fib"
            selected_sequence = neural_network.calc.get_fibonacci_series(quantity_of_numbers_in_sequence)
        elif sequence_type == '2':
            row_type = "fac"
            selected_sequence = neural_network.calc.get_factorial_function(quantity_of_numbers_in_sequence)
        elif sequence_type == '3':
            row_type = "loop"
            selected_sequence = neural_network.calc.get_periodic_function(quantity_of_numbers_in_sequence)
        print(*selected_sequence)
        network_training_parameters["selected_sequence"] = selected_sequence
        network_training_parameters["row_type"] = row_type

        network_training_parameters["E"] = float(input("Enter the error: "))
        network_training_parameters["ALPHA"] = float(input("Enter the learning coefficient: "))
        network_training_parameters["L"] = int(input("Enter the number of columns in the learning matrix: "))
        network_training_parameters["p"] = int(input("Enter the number of rows in the learning matrix: "))
        network_training_parameters["limit_of_iterations"] = int(input("Enter the number of training steps that the network can complete: "))

        neural_network.train_network(network_training_parameters)

    elif start_choice == '2':
        weights_matrix_first = np.array([])
        weights_matrix_second = np.array([])
        with open("wm1.npy", "r") as weight_matrix_file:
            weights_matrix_first = np.load("wm1.npy")
        with open("wm2.npy", "r") as weight_matrix_file:
            weights_matrix_second = np.load("wm2.npy")

        # sequence_type = input("Выберите последовательность: \n1 - ряд Фиббоначи\n2 - Факториальная функция\n\n")
        sequence_type = input("Select sequence type:\n"
                              "1 - Fibonacci series\n"
                              "2 - Factorial function\n")
        quantity_of_numbers_in_sequence = int(input("Enter the number of items in the selected sequence: "))
        selected_sequence = []
        row_type = ""
        if sequence_type == '1':
            row_type = "fib"
            selected_sequence = neural_network.calc.get_fibonacci_series(quantity_of_numbers_in_sequence)
        elif sequence_type == '2':
            row_type = "fac"
            selected_sequence = neural_network.calc.get_factorial_function(quantity_of_numbers_in_sequence)

        learning_matrix_win = neural_network.calc.create_matrix_win(selected_sequence, 7, 4)
        print("\n", str(predict_next(weights_matrix_first, weights_matrix_second, selected_sequence[-5:-1])))
    else:
        exit()


if __name__ == "__main__":
    main_menu()
