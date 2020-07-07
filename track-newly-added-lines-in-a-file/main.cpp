// Created by: Muhammed Emin ÖMÜR
//
// This code tracks given text file and writes out
// newly added characters.
//
// Warning:
// 1 - This code does not respond well changes occured
// on the previously created lines so while testing it you
// should add your new words on a new line.
// 2 - Do not modify previously added lines!

#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <chrono>
#include <cstdlib>

int main()
{
	std::ifstream in_file("foo.txt");
	std::string line;
	int previous_input_position = 0;

	if (!in_file.is_open()) {
		std::cerr << "Error opening file\n";
		std::exit(EXIT_FAILURE);
	}

	while (true) {
		std::getline(in_file, line);
		int current_input_position = in_file.tellg();
		if (current_input_position != EOF &&
			current_input_position != previous_input_position) {
			std::cout << line << '\n';
			previous_input_position = current_input_position;
			if (line == "exit program") {
				break;
			}
		}

		if (in_file.eof()) {
			std::this_thread::sleep_for(
				std::chrono::duration<int, std::milli>(1500));
			in_file.clear();
		}
	}

	return 0;
}
