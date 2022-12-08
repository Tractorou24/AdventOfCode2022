#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main()
{
	std::fstream file;
	file.open("data.txt", std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("File not found");

	std::vector<char> items, items2;
	std::vector<std::string> elf_group;
	std::string line;
	while(std::getline(file, line))
	{
		// Q1
		std::string part1 = line.substr(0, line.size() / 2);
		std::string part2 = line.substr(line.size() / 2, line.size() / 2);

		if(part1.size() != part2.size())
			throw std::runtime_error("Invalid input");

		for(const char& c : part1)
			if (part2.find(c) != std::string::npos)
			{
				items.push_back(c);
				break;
			}

		// Q2
		elf_group.push_back(line);
		if(elf_group.size() % 3 == 2)
		{
			std::ranges::sort(elf_group, [](const std::string& a, const std::string& b) { return a.size() < b.size(); });
			for (const char& c : elf_group[0])
				if (elf_group[1].find(c) != std::string::npos && elf_group[2].find(c) != std::string::npos)
				{
					items2.push_back(c);
					break;
				}
			elf_group.clear();
		}
	}

	const auto get_priority = [](const int& old_sum, const char& c)
	{
		int priority;
		if (std::islower(c))
			priority = c - 'a' + 1;
		else
			priority = c - 'A' + 1 + 26;

		return old_sum + priority;
	};

	const int sum1 = std::accumulate(items.begin(), items.end(), 0, get_priority);
	const int sum2 = std::accumulate(items2.begin(), items2.end(), 0, get_priority);

	std::cout << "Q1: Priority sums is: " << sum1 << std::endl;
	std::cout << "Q2: Priority sum of groups is: " << sum2 << std::endl;
}
