#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "SortingFunctions.hpp"

void print(const std::vector<int>& vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << "  ";
	}
}

std::vector<int> ReadValuesFromFile(const std::string& filepath)
{
	std::ifstream file(filepath);
	int number;
	std::vector<int> numbers;

	while(file >> number)
		numbers.push_back(number);

	return numbers;
}

void WriteValuesToFile(const std::vector<int>& numbers, const std::string& filepath = "../Data/Output.txt")
{
	std::ofstream file(filepath, std::ios_base::trunc); //lade till trunc för att rensa output filen

	for(std::vector<int>::size_type i = 0; i < numbers.size() - 1; ++i)
		file << numbers[i] << std::endl;

	file << numbers.back();
}

int main(int argc, char** argv)
{
	//if(argc < 4)
	//{
	//	std::cout << "To few arguments" << std::endl;
	//	return -1;
	//}
	SortingFunctions sort;
	std::vector<int> numbers = ReadValuesFromFile("../Data/1000000(0,10000000).txt");


	std::vector<int> num;
	int size = 100;
	num.reserve(size);
	for (int i = 0; i < size; ++i) {
		num.emplace_back(rand() & 150);
	}
	auto start = std::chrono::steady_clock::now();



	sort.heapSort(numbers);

	//switch (argv[2][0])
	//{
	//case '1':
	//	sort.mergeSort(numbers);
	//	break;
	//case '2':
	//	// Insert necessary operations and function calls here
	//	// for sorting the vector using your second algorithm
	//	break;
	//case '3':
	//	// Insert necessary operations and function calls here
	//	// for sorting the vector using your third algorithm
	//	break;
	//default:
	//	std::cout << "Incorrect argument for choosing the sorting algorithm!" << std::endl;
	//	std::cout << "Aborting process!" << std::endl;
	//	return -1;
	//}

	auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "Sorting took: " << elapsed_seconds.count() << " seconds" << std::endl;
	WriteValuesToFile(numbers);



	std::cout << "Done writing to file";
	//WriteValuesToFile(numbers, argv[3]);

	return 0;
}