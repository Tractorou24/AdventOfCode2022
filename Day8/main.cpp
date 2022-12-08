#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
    std::fstream file;
    file.open("data.txt", std::ios::in);

    if (!file.is_open())
        throw std::runtime_error("File not found");

    std::vector<std::vector<int>> data;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::vector<int> row;
        row.reserve(line.size());
        for (const char& c : line)
            row.push_back(static_cast<int>(c) - 48);
        data.push_back(row);
    }
    file.close();


    const std::size_t x = data.size(), y = data.front().size();
    std::vector visited(x, std::vector(y, false));

    // Q1
    std::size_t nb_of_visible_trees = 2 * x + 2 * y - 4;
    for (std::size_t i = 1; i < x - 1; i++)
    {
        // Left to Right
        int maxi = data[i][0];
        for (std::size_t j = 1; j < y - 1; j++)
            if (data[i][j] > maxi)
            {
                maxi = data[i][j];
                visited[i][j] = true;
                nb_of_visible_trees++;
            }

        // Right to Left
        maxi = data[i][y - 1];
        for (std::size_t j = y - 2; j > 0; j--)
            if (data[i][j] > maxi)
            {
                maxi = data[i][j];
                if (!visited[i][j])
                {
                    visited[i][j] = true;
                    nb_of_visible_trees++;
                }
            }
    }

    for (std::size_t j = 1; j < y - 1; j++)
    {
        int maxi = data[0][j];
        // Top to Bottom
        for (std::size_t i = 1; i < x - 1; i++)
            if (data[i][j] > maxi)
            {
                maxi = data[i][j];
                if (!visited[i][j])
                {
                    visited[i][j] = true;
                    nb_of_visible_trees++;
                }
            }

        // Bottom to Top
        maxi = data[x - 1][j];
        for (std::size_t i = x - 2; i > 0; i--)
            if (data[i][j] > maxi)
            {
                maxi = data[i][j];
                if (!visited[i][j])
                {
                    visited[i][j] = true;
                    nb_of_visible_trees++;
                }
            }
    }

    // Q2
    std::size_t max_scenic_score = 0;
    for (std::size_t i = 1; i < x - 1; i++)
    {
        for (std::size_t j = 1; j < y - 1; j++)
        {
            std::size_t left = 0, right = 0, top = 0, bottom = 0;
            for (std::size_t k = j; k > 0; k--)
            {
                left++;
                if (data[i][k - 1] >= data[i][j])
                    break;
            }
            for (std::size_t k = j + 1; k < y; k++)
            {
                right++;
                if (data[i][k] >= data[i][j])
                    break;
            }
            for (std::size_t k = i; k > 0; k--)
            {
                top++;
                if (data[k - 1][j] >= data[i][j])
                    break;
            }
            for (std::size_t k = i + 1; k < x; k++)
            {
                bottom++;
                if (data[k][j] >= data[i][j])
                    break;
            }
            max_scenic_score = std::max(max_scenic_score, top * bottom * left * right);
        }
    }

    std::cout << "Number of visible trees from the border: " << nb_of_visible_trees << std::endl;
    std::cout << "Max scenic score: " << max_scenic_score << std::endl;
    return 0;
}
