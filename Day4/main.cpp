#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
	std::fstream file;
	file.open("data.txt", std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("File not found");

	int range_contains = 0, range_overlaps = 0;
	std::string line;
	while(std::getline(file, line))
	{
		const std::string first_elf = line.substr(0, line.find(','));
		const std::string second_elf = line.substr(line.find(',') + 1);

		const int a = std::stoi(first_elf.substr(0, first_elf.find('-')));
		const int b = std::stoi(first_elf.substr(first_elf.find('-') + 1));
		const int c = std::stoi(second_elf.substr(0, second_elf.find('-')));
		const int d = std::stoi(second_elf.substr(second_elf.find('-') + 1));

		if (a >= c && b <= d || c >= a && d <= b)
			range_contains++;
		if (a >= c && a <= d || b >= c && b <= d || c >= a && d <= b)
			range_overlaps++;
	}
	file.close();

	std::cout << "Pairs fully containing others: " << range_contains << std::endl;
	std::cout << "Pairs fully overlapping others: " << range_overlaps << std::endl;
}
