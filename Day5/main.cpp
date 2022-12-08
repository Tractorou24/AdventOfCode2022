#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

template<typename T>
void stack_push(std::vector<std::stack<T>>& stacks, const std::initializer_list<T>& values)
{
	std::stack<T> stack;
	for (auto val : values)
		stack.push(val);
	stacks.push_back(stack);
}

template<typename T>
void stack_insert(std::stack<T>& stack, const std::vector<T>& values)
{
    for (auto val : values)
        stack.push(val);
}

template<typename T>
std::vector<T> stack_pop(std::stack<T>& stack, const int& size)
{
    std::vector<T> res;
    for (int i = 0; i < size; ++i)
    {
        const T& val = stack.top();
        res.push_back(val);
        stack.pop();
    }
	std::ranges::reverse(res);
    return res;
}

int main()
{
    std::fstream file;
    file.open("data.txt", std::ios::in);

    if (!file.is_open())
        throw std::runtime_error("File not found");

    /*
                [M]     [B]             [N]
        [T]     [H]     [V] [Q]         [H]
        [Q]     [N]     [H] [W] [T]     [Q]
        [V]     [P] [F] [Q] [P] [C]     [R]
        [C]     [D] [T] [N] [N] [L] [S] [J]
        [D] [V] [W] [R] [M] [G] [R] [N] [D]
        [S] [F] [Q] [Q] [F] [F] [F] [Z] [S]
        [N] [M] [F] [D] [R] [C] [W] [T] [M]
         1   2   3   4   5   6   7   8   9
     */
    std::vector<std::stack<char>> stacks1, stacks2;
    stack_push<char>(stacks1, { 'N', 'S', 'D', 'C', 'V', 'Q', 'T' });
    stack_push<char>(stacks1, { 'M', 'F', 'V' });
    stack_push<char>(stacks1, { 'F', 'Q', 'W', 'D', 'P', 'N', 'H', 'M' });
    stack_push<char>(stacks1, { 'D', 'Q', 'R', 'T', 'F' });
    stack_push<char>(stacks1, { 'R', 'F', 'M', 'N', 'Q', 'H', 'V', 'B' });
    stack_push<char>(stacks1, { 'C', 'F', 'G', 'N', 'P', 'W', 'Q' });
    stack_push<char>(stacks1, { 'W', 'F', 'R', 'L', 'C', 'T' });
    stack_push<char>(stacks1, { 'T', 'Z', 'N', 'S' });
    stack_push<char>(stacks1, { 'M', 'S', 'D', 'J', 'R', 'Q', 'H', 'N' });
	stacks2 = stacks1;

    std::string line, _;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        int nb, from, to;
        ss >> _ >> nb >> _ >> from >> _ >> to;

        for (int i = 0; i < nb; ++i)
        {
			stacks1[to - 1].push(stacks1[from - 1].top());
			stacks1[from - 1].pop();
        }
		stack_insert<char>(stacks2[to - 1], stack_pop<char>(stacks2[from - 1], nb));
    }
    file.close();

	std::cout << "Part 1: ";
    std::ranges::for_each(stacks1, [](const auto& stack) { std::cout << stack.top(); });
	std::cout << std::endl << "Part 2: ";
    std::ranges::for_each(stacks2, [](const auto& stack) { std::cout << stack.top(); });
	std::cout << std::endl;
}
