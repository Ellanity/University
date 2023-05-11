import copy
import numpy as np
import random
import ast


class NeuralNetwork:
    memorized_standards = []
    weights_matrix = []
    current_standard = []

    def __init__(self):
        self.IMAGE_SIZE = 5
        self.network_is_relaxed = False
        self.numpy_distinct_standard = []

        self.__init__weights_matrix__()
        self.__init__shuffle_neurons__()

    def __init__weights_matrix__(self):
        for weights_matrix_line in range(self.IMAGE_SIZE ** 2):
            self.weights_matrix.append([])
            for weights_matrix_col in range(self.IMAGE_SIZE ** 2):
                self.weights_matrix[weights_matrix_line].append(0)

    def __init__shuffle_neurons__(self):
        self.shuffled_neurons = []
        for shuffle_index in range(self.IMAGE_SIZE ** 2):
            self.shuffled_neurons.append(shuffle_index)
        random.shuffle(self.shuffled_neurons)

    def memorize_standard(self, standard):
        self.memorized_standards.append(standard)
        addition_to_weights_matrix = np.matmul(np.array([standard]).T, np.array([standard]))
        numpy_array_of_new_weights_matrix = (np.array(self.weights_matrix) + addition_to_weights_matrix)
        self.weights_matrix = numpy_array_of_new_weights_matrix.tolist()
        for nullifying_index in range(len(self.weights_matrix)):
            self.weights_matrix[nullifying_index][nullifying_index] = 0
        print(self.__print_standard(standard))

    def recognize_standard(self, standard):
        print(self.__print_standard(standard) + "\n")
        iteration = 0
        numpy_weights_matrix = np.array(self.weights_matrix)
        self.numpy_distinct_standard = np.array([standard]).T
        vector_of_values_next_state = np.array([0])
        while not self.network_is_relaxed:
            iteration += 1
            # print(f"iter: {iteration}")
            if iteration > 10000:
                print("It is impossible to identify the image.\n")
                exit()
            vector_of_values_next_state = self.__iteration(vector_of_values_next_state, numpy_weights_matrix)

    def __iteration(self, vector_of_values_next_state, numpy_weights_matrix):
        previous_iteration = vector_of_values_next_state
        multiplied_matrix = np.matmul(numpy_weights_matrix, self.numpy_distinct_standard)
        vector_of_values_next_state = multiplied_matrix
        for activating_index in range(len(vector_of_values_next_state)):
            vector_of_values_next_state[activating_index][0] = 1 if vector_of_values_next_state[activating_index][0] >= 0 else -1

        self.numpy_distinct_standard = vector_of_values_next_state
        print(self.__print_standard(vector_of_values_next_state.T.flatten().tolist()) + "\n")

        if (previous_iteration == vector_of_values_next_state).all():
            self.network_is_relaxed = True
        return vector_of_values_next_state

    def __print_standard(self, standard):
        image = ""
        for current_value in range(len(standard)):
            if standard[current_value] == 1:
                image = image + "█"  # "▓"
            elif standard[current_value] == -1:
                image = image + "░"  # "_"
            if (current_value + 1) % self.IMAGE_SIZE == 0:
                image = image + "\n"
        return image

    def get_weights_matrix(self):
        return self.weights_matrix


def get_standards_from_text(raw_data):

    def read_raw_standards(text):
        standards = []
        current_index_of_standard_start = 0
        for current_line in range(len(text)):
            if text[current_line] == '\n':
                new_standard = text[current_index_of_standard_start:current_line]
                standards.append(new_standard)
                current_index_of_standard_start = current_line + 1
        return standards

    def raw_standards_into_vectors_of_values(raw_standards):
        vectors_of_values = copy.deepcopy(raw_standards)
        for standard_index in range(len(raw_standards)):
            for standard_line_index in range(len(raw_standards[0])):
                raw_standards[standard_index][standard_line_index] = \
                    raw_standards[standard_index][standard_line_index][:-1]  # delete "\n"
                vector_of_values = []
                for symbol in raw_standards[standard_index][standard_line_index]:
                    if symbol == '1':
                        vector_of_values.append(1)
                    if symbol == '0':
                        vector_of_values.append(-1)
                vectors_of_values[standard_index][standard_line_index] = vector_of_values
        return vectors_of_values

    def flatten_vectors_standards(vectors_standards):
        flattened_distinct_standards = []
        for standard_index in range(len(vectors_standards)):
            flattened_standard = []
            for line_index in range(len(vectors_standards[0])):
                flattened_standard += vectors_standards[standard_index][line_index]
            flattened_distinct_standards.append(flattened_standard)
        return flattened_distinct_standards

    distinct_raw_standards = read_raw_standards(raw_data)
    vectors_of_values_standards = raw_standards_into_vectors_of_values(distinct_raw_standards)
    # flattened_vectors_standards = flatten_vectors_standards(vectors_of_values_standards)
    # print(flattened_vectors_standards)
    return flatten_vectors_standards(vectors_of_values_standards)


def add_txt_to_file_name(file_name):
    if file_name[-4:] != ".txt":
        file_name = file_name + ".txt"
    return file_name


def training_network_with_standards(neural_network):
    file_name_with_standards = add_txt_to_file_name(input("Enter the name of the file with the standards: "))
    # file_name_with_standards = "alphabet.txt"
    with open(file_name_with_standards, "r") as file_with_standards:
        standards = file_with_standards.readlines()
    distinct_standards_list = get_standards_from_text(standards)

    for index_of_standard in range(len(distinct_standards_list)):
        neural_network.memorize_standard(distinct_standards_list[index_of_standard])

    save_input = input("Standards are memorized.\n"
                       "If you don't want to save the weight matrix, press Enter\n"
                       "If you want, enter the name of the corresponding file\n\n")
    if save_input != "":
        # save_input = "alphabet-weights"
        with open(add_txt_to_file_name(save_input), "w") as weights_matrix_file:
            weights_matrix_file.write(str(neural_network.get_weights_matrix()))


def image_recognition(neural_network):
    weights_matrix_file_name = add_txt_to_file_name(input("Enter the name of the file with the trained weight matrix: "))
    # weights_matrix_file_name = "alphabet-weights.txt"
    with open(weights_matrix_file_name, "r") as weights_matrix_file:
        weights_matrix = ast.literal_eval(weights_matrix_file.readline())
    neural_network.weights_matrix = weights_matrix

    distorted_image_name = input("Enter the name of the file with the distorted image: ")
    # distorted_image_name = "alphabet-distorted"
    with open(add_txt_to_file_name(distorted_image_name), "r") as distorted_image_file:
        distorted_image = distorted_image_file.readlines()
    distinct_distorted_image = get_standards_from_text(distorted_image)

    for current_standard_index in range(len(distinct_distorted_image)):
        neural_network.recognize_standard(distinct_distorted_image[current_standard_index])
        print("End of recognition\n\n")

    # print(distinct_distorted_image)


def main_menu():
    neural_network = NeuralNetwork()
    main_menu_text = "Enter the operating mode of the program:\n" \
                     "1 - training by standards\n" \
                     "2 - recognition\n" \
                     "other - exit\n"
    choice = input(main_menu_text)
    if choice == "1":
        training_network_with_standards(neural_network)
    elif choice == "2":
        image_recognition(neural_network)
    else:
        exit()


if __name__ == "__main__":
    main_menu()
