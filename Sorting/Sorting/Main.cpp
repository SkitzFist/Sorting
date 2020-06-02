#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "SortingFunctions.hpp"

std::vector<int> ReadValuesFromFile(const std::string& filepath)
{
	std::ifstream file(filepath);
	int number;
	std::vector<int> numbers;

	while (file >> number)
		numbers.push_back(number);

	return numbers;
}

void WriteValuesToFile(const std::vector<int>& numbers, const std::string& filepath = "Output.txt")
{
	std::ofstream file(filepath);

	for (std::vector<int>::size_type i = 0; i < numbers.size() - 1; ++i)
		file << numbers[i] << std::endl;

	file << numbers.back();
}

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		std::cout << "To few arguments" << std::endl;
		return -1;
	}

	std::vector<int> numbers = ReadValuesFromFile(argv[1]);
	SortingFunctions sort;
	auto start = std::chrono::steady_clock::now();

	switch (argv[2][0])
	{
	case '1':
		sort.heapSort(numbers);
		break;
	case '2':
		sort.mergeSort(numbers);
		break;
	case '3':
		sort.quickSort(numbers);
		break;
	default:
		std::cout << "Incorrect argument for choosing the sorting algorithm!" << std::endl;
		std::cout << "Aborting process!" << std::endl;
		return -1;
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Sorting took: " << elapsed_seconds.count() << " seconds" << std::endl;

	WriteValuesToFile(numbers, argv[3]);