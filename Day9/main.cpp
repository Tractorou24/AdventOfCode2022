#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

int main()
{
    std::fstream file;
    file.open("data.txt", std::ios::in);

    if (!file.is_open())
        throw std::runtime_error("File not found");

    std::pair<int, int> head = {0, 0}, tail = {0, 0};
    std::array<std::pair<int, int>, 10> rope;
    std::unordered_set<int> res, res2;

    std::string line;
    while (std::getline(file, line))
    {
        const char direction = line.front();
        const int distance = std::stoi(line.substr(line.find_first_of(' ')));
        for (int i = 0; i < distance; i++)
        {
            // Q1
            switch (direction)
            {
            case 'U':
                head.first++;
                rope.front().first++;
                break;
            case 'D':
                head.first--;
                rope.front().first--;
                break;
            case 'R':
                head.second++;
                rope.front().second++;
                break;
            case 'L':
                head.second--;
                rope.front().second--;
                break;
            default:
                throw std::invalid_argument("Invalid Direction !");
            }

            const std::pair diff = {head.first - tail.first, head.second - tail.second};
            if (std::abs(diff.first) == 2 && std::abs(diff.second) == 0)
            {
                tail.first += diff.first / 2;
            } else if (std::abs(diff.first) == 2 && std::abs(diff.second) == 1)
            {
                tail.first += diff.first / 2;
                tail.second += diff.second;
            } else if (std::abs(diff.first) == 0 && std::abs(diff.second) == 2)
            {
                tail.second += diff.second / 2;
            } else if (std::abs(diff.first) == 1 && std::abs(diff.second) == 2)
            {
                tail.first += diff.first;
                tail.second += diff.second / 2;
            }
            res.insert(tail.first * 10000 + tail.second);

            // Q2
            for (int j = 0; j < rope.size() - 1; j++)
            {
                const std::pair diff2 = {rope[j].first - rope[j + 1].first, rope[j].second - rope[j + 1].second};
                if (std::abs(diff2.first) == 2 && std::abs(diff2.second) == 0)
                {
                    rope[j + 1].first += diff2.first / 2;
                } else if (std::abs(diff2.first) == 2 && std::abs(diff2.second) == 1)
                {
                    rope[j + 1].first += diff2.first / 2;
                    rope[j + 1].second += diff2.second;
                } else if (std::abs(diff2.first) == 0 && std::abs(diff2.second) == 2)
                {
                    rope[j + 1].second += diff2.second / 2;
                } else if (std::abs(diff2.first) == 1 && std::abs(diff2.second) == 2)
                {
                    rope[j + 1].first += diff2.first;
                    rope[j + 1].second += diff2.second / 2;
                } else if (std::abs(diff2.first) == 2 && std::abs(diff2.second) == 2)
                {
                    rope[j + 1].first += diff2.first / 2;
                    rope[j + 1].second += diff2.second / 2;
                }
            }
            res2.insert(rope.back().first * 10000 + rope.back().second);
        }
    }
    file.close();

    std::cout << "The tail rope if the rope is size 2 visit at least " << res.size() << " positions." << std::endl;
    std::cout << "The tail rope if the rope is size 10 visit at least " << res2.size() << " positions." << std::endl;
    return 0;
}
