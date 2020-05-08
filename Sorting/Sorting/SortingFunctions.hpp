#pragma once
#include <vector>

#include <thread>
#include <functional>
#include <condition_variable>
#include <queue>


class ThreadPool {
	
public:
	using Task = std::function<void()>;
	ThreadPool(size_t numOfThreads);
	~ThreadPool();
	void enqueue(Task task);

private:
	std::vector<std::thread> threads;
	std::condition_variable conVar;
	std::mutex mutex;
	bool shouldStop;
	std::queue<Task> tasks;

	void start(size_t numOfThreads);
	void stop();
	
};

class SortingFunctions {

public:
	void mergeSort(std::vector<int>& vec);
	void quickSort(std::vector<int>& vec);
	void heapSort(std::vector<int>& vec);
private:
	//merge sort
	void mergeSort(std::vector<int>& vec, int low, int high);
	void merge(std::vector<int>&, int low, int mid, int high);

	//quickSort
	void swap(int* a, int* b);
	int partition(std::vector<int>& vec, int min, int max);
	void quickSort(std::vector<int>& vec, int min, int max);

	//HeapSort
	const int ROOT = 0;
	void heapSort(std::vector<int>& vec, int lastIndex);
	void balance(std::vector<int>& vec,int index, int lastIndex);
	inline int getParent(int index);
	inline int getLeft(int index);
	inline int getRight(int index);

};