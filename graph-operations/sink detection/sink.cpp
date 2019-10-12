#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

// This function fills the map with data from file
void create_adjacency_matrix(std::map<int, std::vector<int>>& map, std::string file_name);

// This function tries to find sink vertex if it does not exist, 0 is returned
int find_sink(std::map<int, std::vector<int>>& map);

int main()
{
    std::map<int, std::vector<int>> matrix_form;

    create_adjacency_matrix(matrix_form, "matrix_data.txt");
    std::cout << find_sink(matrix_form) << '\n';

    return 0;
}

void create_adjacency_matrix(std::map<int, std::vector<int>>& map, std::string file_name)
{
    std::ifstream matrix_data_input(file_name);
    // String object for holding data from file
    std::string data;
    // Temporary file object for string parsing
    std::string temp;
    int vertex_num;
    // Object for string parsing
    std::stringstream line_data;

    if (!matrix_data_input.is_open()) {
        std::cerr << "An error occured during opening file\n";
        std::exit(EXIT_FAILURE);
    }

    // First line of text file will contain data about vertex numbers
    std::getline(matrix_data_input, data);
    line_data << data;
    while (line_data >> temp) {
        if (std::stringstream(temp) >> vertex_num) {
            map[vertex_num];
        }
    }

    // This part is for parsing all the other data
    for (auto map_iterator = map.begin();
         std::getline(matrix_data_input, data);
         ++map_iterator) {
        // Object must be cleaned otherwise string parsing operation fails
        line_data.clear();
        line_data << data;
        while (line_data >> temp) {
            if (std::stringstream(temp) >> vertex_num) {
                map_iterator->second.push_back(vertex_num);
            }
        }
    }
}

int find_sink(std::map<int, std::vector<int>>& map)
{
    auto map_iterator = map.begin();
    unsigned long map_size = map.size();
    unsigned long i = 0;
    int sink = 0;

    while (map_iterator != map.end() && i != map_size) {
        if (map_iterator->second[i] == 0) {
            ++i;
        } else {
            ++map_iterator;
        }
    }

    if (i == map_size) {
        sink = map_iterator->first;
    }

    return sink;
}
