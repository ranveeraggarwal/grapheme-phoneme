data_dir = "./data"
cmu_dict = data_dir + "/cmudict_SPHINX_40"

temp_dir = "./temp"  #gen data stored in here
equal_graph_phones_file = temp_dir + "/equal_graph_phone.dat"
training_data_file = temp_dir + "/training_data.dat"
testing_data_file = temp_dir + "/testing_data.dat"
initial_probabilities_file = temp_dir + "/initial_probabilities.dat"
festival_file = temp_dir + "/temp_festival_data.dat"

bin_dir = "./bin"
bin_file = bin_dir + "/phoneme_to_graphene.out"

compilation_string = "g++ ./src/phoneme_to_graphene.cpp -o "+bin_file