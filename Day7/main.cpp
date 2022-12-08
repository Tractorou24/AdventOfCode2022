#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

static constexpr int FILESYSTEM_SIZE = 70000000, UPDATE_SIZE = 30000000;

struct File
{
    std::string name;
    int size = 0;
};

struct Folder
{
    std::string parent;
    std::string path;
    std::vector<Folder*> folders;
    std::vector<File> files;

    [[nodiscard]] int recursive_size(int current = 0) const noexcept
    {
        int tmp = std::accumulate(files.begin(), files.end(), 0, [](int a, File b) { return a + b.size; });
        for (auto& folder : folders)
            tmp += folder->recursive_size(current);
        return current + tmp;
    }
};

void free_directory(const Folder* root) noexcept
{
    for (const auto* folder : root->folders)
        free_directory(folder);
    delete root;
}

int main()
{
    std::fstream file;
    file.open("data.txt", std::ios::in);

    if (!file.is_open())
        throw std::runtime_error("File not found");

    auto* root = new Folder;
    root->path = "/";

    Folder* current_directory = nullptr;
    std::map<std::string, Folder*> directories;
    directories.insert_or_assign("/", root);

    std::string line;
    bool in_ls_mode = false;
    while (std::getline(file, line))
    {
        if (line.starts_with("$"))
        {
            in_ls_mode = false;
            line = line.substr(2);
            if (line.starts_with("cd"))
            {
                line = line.substr(3);
                if (line == "/")
                    current_directory = root;
                else if (line == "..")
                    current_directory = directories[current_directory->parent];
                else
                    current_directory = directories[current_directory->path + line + "/"];
            } else if (line.starts_with("ls"))
            {
                in_ls_mode = true;
            } else
                throw std::runtime_error("Unknown command !");
            continue;
        }
        if (in_ls_mode)
        {
            if (line.starts_with("dir"))
            {
                line = line.substr(4);

                auto* folder = new Folder;
                folder->parent = current_directory->path;
                folder->path = current_directory->path + line + "/";
                current_directory->folders.push_back(folder);
                directories.insert_or_assign(folder->path, folder);
            } else if (std::isdigit(line[0]))
            {
                int size = std::stoi(line.substr(0, line.find_first_of(' ') + 1));
                line = line.substr(line.find_first_of(' ') + 1);

                File current_file = {};
                current_file.name = line;
                current_file.size = size;
                current_directory->files.push_back(current_file);
            } else
                throw std::runtime_error("Unknown file type !");
        }
    }
    file.close();

    // Q1
    std::vector<std::string> dirs;
    for (auto& [key, value] : directories)
        if (value->recursive_size() <= 100000)
            dirs.push_back(key);
    std::erase(dirs, "/");

    std::cout << "Total size with dirs less than 100000 bytes: " << std::accumulate(
        dirs.begin(), dirs.end(), 0, [directories](int nb, const std::string& dir)
        {
            return nb + directories.at(dir)->recursive_size();
        }) << std::endl;

    // Q2
    const int total_used_space = root->recursive_size();
    const int to_free = total_used_space - (FILESYSTEM_SIZE - UPDATE_SIZE);

    std::vector<std::pair<std::string, Folder*>> directories_vector;
    directories_vector.reserve(directories.size());
    for (const auto& pair : directories)
        directories_vector.emplace_back(pair);

    std::ranges::sort(directories_vector,
                      [&](const std::pair<std::string, Folder*>& a, const std::pair<std::string, Folder*>& b)
                      {
                          return std::abs(a.second->recursive_size() - to_free) < std::abs(
                                     b.second->recursive_size() - to_free) && a.second->recursive_size() >= to_free;
                      });

    std::cout << "Folder to delete is: " << directories_vector[0].first << " and it's size is: " << directories_vector[
        0].second->recursive_size() << std::endl;

    free_directory(root);
    return 0;
}
