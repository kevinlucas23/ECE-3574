#ifndef CQSORT_HPP
#define CQSORT_HPP
#include <algorithm>
#include <thread>
#include <future>
#include <atomic>
#include <iostream>

template <typename T>
class CQSort {
public:
	CQSort(int mthr) {
		// TODO: your code here
		thread_max = mthr;
		thread_count = 0;
	}

	void operator()(T& vec) {
		// TODO: your code here
		list_size = (int)vec.size();
		qsort(vec, 0, (int)vec.size() - 1);
	}

	void qsort(T& vec, int low, int high) {
		if (low < high) {
			int p = partition_it(vec, low, high);
			if (thread_count + 1 < thread_max) {
				std::future<void> thread1 = std::async(std::launch::async, &CQSort::qsort, this, std::ref(vec), low, p - 1);
				std::future<void> thread2 = std::async(std::launch::async, &CQSort::qsort, this, std::ref(vec), p + 1, high);
				thread_count = thread_count + 2;
			}
			else {
				qsort(vec, low, p - 1);
				qsort(vec, p + 1, high);
			}
		}
	}

	int partition_it(T& vec, int low, int high) {
		auto pivot = vec[high];
		int i = low - 1;
		for (int j = low; j <= high - 1; j++) {
			if (vec[j] < pivot) {
				i++;
				std::swap(vec[i], vec[j]);
			}
		}
		std::swap(vec[i + 1], vec[high]);
		return (i + 1);
	}

	int getlist() {
		return list_size;
	}

private:
	int list_size;
	int thread_max;
	int thread_count;
};

#include "cqsort.tpp"
#endif // CQSORT_HPP