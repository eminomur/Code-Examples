#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>

int main()
{
	std::map<std::string, int> m;
	std::ifstream inf;
	std::string str;
	
	std::cout << "Enter the name of the file: ";
	getline(std::cin, str);
	
	inf.open(str);
	
	if (inf.fail()) {
		std::cout << "Error while opening " << str << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	while (inf >> str) {
		++m[str];
	}
	
	for (auto& a : m) {
		std::cout << a.first << '\t' << a.second << std::endl;
	}
	
	inf.close();
	
	return 0;
}
