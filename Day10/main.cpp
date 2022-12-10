#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
    std::fstream file;
    file.open("data.txt", std::ios::in);

    if (!file.is_open())
        throw std::runtime_error("File not found");

    std::vector<int> operations;
    operations.emplace_back(1);
    std::stringstream crt;

    std::string line;
    while (std::getline(file, line))
    {
        const std::string op = line.substr(0, line.find_first_of(' '));

        if (op == "noop")
        {
            operations.emplace_back(operations.back());
        } else if (op == "addx")
        {
            const int nb = std::stoi(line.substr(line.find_first_of(' ')));
            operations.emplace_back(operations.back());
            operations.emplace_back(operations.back() + nb);
        }
    }
    file.close();

    // Q1
    const std::array requested_cycles = {20, 60, 100, 140, 180, 220};
    const int sum_of_requested_cycle_strength = std::accumulate(requested_cycles.cbegin(), requested_cycles.cend(), 0,
                                                                [&operations](const int& nb, const int& cycle)
                                                                {
                                                                    return operations[cycle - 1] * cycle + nb;
                                                                });
    std::cout << "The sum of the strengths of requested cycles is: " << sum_of_requested_cycle_strength << std::endl;

    // Q2
    std::cout << "CRT Result: " << std::endl;
    for (int i = 0; i < static_cast<int>(operations.size()) - 1; i++)
    {
        const int pixel = i % 40;
        const int cycle = i + 1;

        if (pixel >= operations[i] - 1 && pixel <= operations[i] + 1)
            crt << '#';
        else
            crt << '.';

        if (cycle % 40 == 0)
            crt << std::endl;
    }
    std::cout << crt.str() << std::endl;
    return 0;
}
