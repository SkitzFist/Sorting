#include "SortingFunctions.hpp"

void SortingFunctions::mergeSort(std::vector<int>& vec)
{
	int size = static_cast<int>(vec.size());
	mergeSort(vec, 0, size-1 );
}

void SortingFunctions::quickSort(std::vector<int>& vec)
{
	int max = static_cast<int>(vec.size()) - 1;
	quickSort(vec, 0, max);
}

void SortingFunctions::mergeSort(std::vector<int>& vec, int low, int high)
{
	if (low < high) {
		int mid = (low + (high - 1)) / 2;
		mergeSort(vec, low, mid);
		mergeSort(vec, mid + 1, high);
		merge(vec, low, mid, high);
	}
}

void SortingFunctions::merge(std::vector<int>& vec, int low, int mid, int high)
{
	int lowSize = (mid - low + 1);
	int* lowArr = new int[lowSize];
	for (int i = 0; i < lowSize; ++i) {
		lowArr[i] = vec[low + i];
	}

	int highSize = (high - mid);
	int* highArr = new int[highSize];
	for (int i = 0; i < highSize; ++i) {
		highArr[i] = vec[mid + 1 + i];
	}

	int i = low, iLow = 0, iHigh = 0;
	
	while (iLow < lowSize && iHigh < highSize)
	{
		if (lowArr[iLow] < highArr[iHigh]) {
			vec[i] = lowArr[iLow];
			++iLow;
		}
		else {
			vec[i] = highArr[iHigh];
			++iHigh;
		}
		++i;
	}

	while (iLow < lowSize) {
		vec[i] = lowArr[iLow];
		++i;
		++iLow;
	}	
	while (iHigh < highSize) {
		vec[i] = highArr[iHigh];
		++i;
		++iHigh;
	}
}

void SortingFunctions::swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int SortingFunctions::partition(std::vector<int>& vec, int min, int max)
{
	int pivot = vec[max];
	int i = (min - 1);
	for (int j = min; j < max; ++j) {
		if (vec[j] < pivot) {
			++i;
			swap(&vec[i], &vec[j]);		
		}	
	}
	int newI = i + 1;
	swap(&vec[newI], &vec[max]);
	return (i+1);
}

void SortingFunctions::quickSort(std::vector<int>& vec, int min, int max)
{
	if (min < max) {
		int partitionIndex = partition(vec, min, max);
		quickSort(vec, min, partitionIndex - 1);
		quickSort(vec, partitionIndex + 1, max);
	}
}

ThreadPool::ThreadPool(size_t numOfThreads)
{
	shouldStop = false;
	start(numOfThreads);
}

ThreadPool::~ThreadPool()
{
	stop();
}

void ThreadPool::enqueue(Task task)
{
	{
		std::unique_lock<std::mutex> lock(mutex);
		tasks.emplace(std::move(task));
	}
	conVar.notify_one();
}

void ThreadPool::start(size_t numOfThreads)
{
	for (size_t i = 0; i < numOfThreads; ++i) {
		threads.emplace_back([=] {
			while (true)
			{
				Task task;
				{
					std::unique_lock<std::mutex> lock(mutex);
					conVar.wait(lock, [=] { return shouldStop || !tasks.empty(); });

					if (shouldStop && tasks.empty()) {
						break;
					}

					task = std::move(tasks.front());
					tasks.pop();
				}
				task();
			}
		});
	}
}

void ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock(mutex);
		shouldStop = true;
	}

	conVar.notify_all();

	for (size_t i = 0; i < threads.size(); ++i) {
		threads[i].join();
	}
}
