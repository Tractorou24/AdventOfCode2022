#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
	std::fstream file;
	file.open("data.txt", std::ios::in);

	if(!file.is_open())
		throw std::runtime_error("File not found");

	std::vector<int> numbers;
	std::string line;
	int current_sum = 0;

	while (file)
	{
		std::getline(file, line);
		if (line.empty())
		{
			numbers.push_back(current_sum);
			current_sum = 0;
			continue;
		}
		
		current_sum += std::stoi(line);
	}
	file.close();

	std::ranges::sort(numbers);
	const auto max_value = numbers.back();

	std::cout << "Q1: Max value is: " << max_value << std::endl;
	std::cout << "Q2: Sum of top 3 is: " << std::reduce(numbers.end() - 3, numbers.end()) << std::endl;
}
