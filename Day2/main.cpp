#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class Choices
{
public:
	constexpr Choices(const char& shape = ' ', const int& score = 0, Choices* winning_shape = nullptr, Choices* losing_shape = nullptr)
		: shape(shape), score(score), win_against(winning_shape), loses_against(losing_shape)
	{}

	char shape;
	int score;
	Choices* win_against;
	Choices* loses_against;
};

int main()
{
	std::fstream file;
	file.open("data.txt", std::ios::in);

	if(!file.is_open())
		throw std::runtime_error("File not found");

	Choices A('A', 1);
	Choices B('B', 2);
	Choices C('C', 3);

	std::unordered_map<char, Choices> possible_choices;
	possible_choices['A'] = Choices('A', 1, &C, &B);
	possible_choices['B'] = Choices('B', 2, &A, &C);
	possible_choices['C'] = Choices('C', 3, &B, &A);

	int question1 = 0, question2 = 0;
	std::string line;
	while(std::getline(file, line))
	{
		const char part1 = line[0], part2 = static_cast<char>('A' + (line[2] - 'X'));
		
		// Q1
		const Choices& choice = possible_choices.at(part2);
		if (choice.win_against->shape == part1) 
			question1 += choice.score + 6;
		else if (choice.loses_against->shape == part1)
			question1 += choice.score + 0;
		else 
			question1 += choice.score + 3;

		// Q2
		switch (part2)
		{
		case 'A':
			question2 += possible_choices[part1].win_against->score;
			break;
		case 'B':
			question2 += possible_choices[part1].score + 3;
			break;
		case 'C':
			question2 += possible_choices[part1].loses_against->score + 6;
			break;
		default:
			break;
		}
	}
	file.close();

	std::cout << "Q1: Total score: " << question1 << std::endl;
	std::cout << "Q2: Total score: " << question2 << std::endl;
	return 0;
}
