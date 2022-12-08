#include <fstream>
#include <iostream>
#include <string>

template <typename T>
bool is_different(const typename T::const_iterator& start, const typename T::const_iterator& end)
{
    for (auto it = start; it != end + 1; ++it)
        for (auto it2 = it + 1; it2 != end + 1; ++it2)
            if (*it == *it2)
                return false;
    return true;
}

int main()
{
    std::fstream file;
    file.open("data.txt", std::ios::in);

    if (!file.is_open())
        throw std::runtime_error("File not found");

    std::string line, data;
    while (std::getline(file, line)) { data += line; }
    file.close();

    for (size_t i = 0; i < data.size() - 4; i++)
    {
        if (is_different<std::string>(data.begin() + i, data.begin() + i + 3))
        {
            std::cout << "First part value: " << i + 4 << std::endl;
            break;
        }
    }

    for (size_t i = 0; i < data.size() - 14; i++)
    {
        if (is_different<std::string>(data.begin() + i, data.begin() + i + 13))
        {
            std::cout << "Second part value: " << i + 14 << std::endl;
            break;
        }
    }
    return 0;
}
