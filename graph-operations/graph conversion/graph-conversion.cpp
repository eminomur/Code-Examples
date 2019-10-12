// Muhammed Emin ÖMÜR
// Atilim University - Software Engineering

// Notes:
// This program does not check if provided file is appropriate for it
//  so you should check your data first, then run the program.
// Output is formatted for both options but it can work well only if numbers have one digit
//  otherwise it is better if you delete code related to formatting output

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <list>
#include <sstream>
#include <cstring>

void create_adjacency_list(std::map<int, std::list<int>>& map, std::string file_name);
void create_adjacency_matrix(std::map<int, std::list<int>>& map, std::string file_name);

// This functions will create a new map objects and assign it to current ones
void convert_to_adjacency_matrix(std::map<int, std::list<int>>& map);
void convert_to_adjacency_list(std::map<int, std::list<int>>& map);

int main(int argc, char *argv[])
{
    int choice;

    if (argc == 1) {
        std::cerr << "Insufficient arguments\n";
        std::exit(EXIT_FAILURE);
    }

    if (std::strcmp(argv[1], "--help") == 0) {
        std::cout << "Enter 1 for convert adjacency list to adjacency matrix\n"
                  << "Enter 2 for vice versa\n"
                  << "After that provide file name\n";
        std::exit(EXIT_FAILURE);
    }


    choice = std::stoi(argv[1]);

    if (choice == 1) {
        std::map<int, std::list<int>> adjacency_list_map;

        create_adjacency_list(adjacency_list_map, argv[2]);
        convert_to_adjacency_matrix(adjacency_list_map);

        std::cout << "Adjacency Matrix is Given Below:\n";
        for (auto map_iterator = adjacency_list_map.begin();
             map_iterator != adjacency_list_map.end();
             ++map_iterator) {
            std::cout << "     " << map_iterator->first;
        }
        std::cout << '\n';
        
        for (auto map_iterator = adjacency_list_map.begin();
             map_iterator != adjacency_list_map.end();
             ++map_iterator) {
            std::cout << map_iterator->first << " |  ";
            for (auto list_iterator = map_iterator->second.begin();
                 list_iterator != map_iterator->second.end();
                 ++list_iterator) {
                std::cout << *list_iterator << "     ";
            }
            std::cout << '\n';
        }
    } else if (choice == 2) {
        std::map<int, std::list<int>> adjacency_matrix_map;

        create_adjacency_matrix(adjacency_matrix_map, argv[2]);
        convert_to_adjacency_list(adjacency_matrix_map);

        std::cout << "Adjacency List is Given Below:\n";
        for (auto map_iterator = adjacency_matrix_map.begin();
             map_iterator != adjacency_matrix_map.end();
             ++map_iterator) {
            std::cout << map_iterator->first;
            for (auto list_iterator = map_iterator->second.begin();
                 list_iterator != map_iterator->second.end();
                 ++list_iterator) {
                std::cout << " -> " << *list_iterator;
            }
            std::cout << '\n';
        }
    } else {
        std::cout << "Wrong Input\n";
        std::exit(EXIT_FAILURE);
    }

    return 0;
}

void create_adjacency_list(std::map<int, std::list<int>>& map, std::string file_name)
{
    std::ifstream graph_data_input(file_name);
    int index, value;

    if (!graph_data_input.is_open()) {
        std::cerr << "An error occured during opening file\n";
        std::exit(EXIT_FAILURE);
    }

    // Values are read from file and placed into map object
    while (graph_data_input >> index >> value) {
        map[index].push_back(value);
    }
}

void create_adjacency_matrix(std::map<int, std::list<int>>& map, std::string file_name)
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

void convert_to_adjacency_matrix(std::map<int, std::list<int>>& map)
{
    bool found;
    std::map<int, std::list<int>> new_map;

    for (auto map_iterator = map.begin();
         map_iterator != map.end();
         ++map_iterator) {
        new_map[map_iterator->first];
        for (auto inner_map_iterator = map.begin();
             inner_map_iterator != map.end();
             ++inner_map_iterator) {
            found = false;
            for (auto list_iterator = map_iterator->second.begin();
                 list_iterator != map_iterator->second.end();
                 ++list_iterator) {
                if (inner_map_iterator->first == *list_iterator) {
                    found = true;
                    break;
                }
            }
            if (found) {
                new_map[map_iterator->first].push_back(1);
            } else {
                new_map[map_iterator->first].push_back(0);
            }
        }
    }

    map = new_map;
}

void convert_to_adjacency_list(std::map<int, std::list<int>>& map)
{
    std::map<int, std::list<int>> new_map;

    for (auto map_iterator = map.begin();
         map_iterator != map.end();
         ++map_iterator) {
        auto inner_map_iterator = map.begin();
        auto list_iterator = map_iterator->second.begin();
        new_map[map_iterator->first];

        while (list_iterator != map_iterator->second.end()) {
            if (*list_iterator) {
                new_map[map_iterator->first].push_back(inner_map_iterator->first);
            }

            ++list_iterator;
            ++inner_map_iterator;
        }
    }

    map = new_map;
}
