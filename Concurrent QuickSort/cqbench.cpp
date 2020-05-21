#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include <tuple>
#include <iomanip>
#include "cqsort.hpp"

int main(int argc, char* argv[])
{
	// TODO: your code here
	std::ofstream fout("finally_over.txt");
	CQSort<std::vector<double>> seq_(0);
	CQSort<std::vector<double>> con_(0);
	std::vector < CQSort<std::vector<int>>> all_sort = { 0,0,1,1,1,10,20,110 };
	std::vector<int> vec_1 = { 1 }, vec_2 = { 1, 7, 4, 90, 40, 28, 39, 43, 87, 101 }, vec_3, vec_4, vec_5, vec_6, vec_7;
	double total_, avg_seq, avg_con;
	std::vector<double> seq_t, con_t;
	std::chrono::time_point<std::chrono::system_clock> begin, end;
	std::chrono::duration<double> t_spend(0);

	int i = 0;
	while ( i < 1000000) {
		auto kev = rand() % 10000000;
		if (i < 100) {
			vec_3.push_back(kev);
		}
		if (i < 1000) {
			vec_4.push_back(kev);
		}
		if (i < 10000) {
			vec_5.push_back(kev);
		}
		if (i < 100000) {
			vec_6.push_back(kev);
		}
		if (i < 1000000) {
			vec_7.push_back(kev);
		}
		i++;
	}

	fout << "List Size   Sequential Sort Time (s)   Concurrent Sort Time (s)" << std::endl;
	fout << "             min     max    average     min     max    average" << std::endl;
	fout << "---------   -----   -----   -------    -----   -----   -------" << std::endl;

	i = 0;
	while (i < 10) {
		std::vector<int> myvec = vec_1;
		begin = std::chrono::system_clock::now();
		all_sort[0](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		seq_t.push_back(total_ / 1000000000);
		myvec = vec_1;
		begin = std::chrono::system_clock::now();
		all_sort[1](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		con_t.push_back(total_ / 1000000000);
		i++;
	}
	avg_seq = (seq_t[0] + seq_t[1] + seq_t[2] + seq_t[3] + seq_t[4] + seq_t[5] + seq_t[6] + seq_t[7] + seq_t[8] + seq_t[9]) / 10;
	avg_con = (con_t[0] + con_t[1] + con_t[2] + con_t[3] + con_t[4] + con_t[5] + con_t[6] + con_t[7] + con_t[8] + con_t[9]) / 10;
	seq_(seq_t);
	con_(con_t);
	fout << "1           " << std::fixed << std::setprecision(4) << seq_t[0] << "  " << seq_t[9] << "  " << std::setprecision(5) << avg_seq << "    " << std::setprecision(4) << con_t[0] << "  " << con_t[9] << "  " << std::setprecision(5) << avg_con << std::endl;
	seq_t.clear();
	con_t.clear();

	i = 0;
	while (i < 10) {
		std::vector<int> myvec = vec_2;
		begin = std::chrono::system_clock::now();
		all_sort[0](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		seq_t.push_back(total_ / 1000000000);
		myvec = vec_2;
		begin = std::chrono::system_clock::now();
		all_sort[2](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		con_t.push_back(total_ / 1000000000);
		i++;
	}
	avg_seq = (seq_t[0] + seq_t[1] + seq_t[2] + seq_t[3] + seq_t[4] + seq_t[5] + seq_t[6] + seq_t[7] + seq_t[8] + seq_t[9]) / 10;
	avg_con = (con_t[0] + con_t[1] + con_t[2] + con_t[3] + con_t[4] + con_t[5] + con_t[6] + con_t[7] + con_t[8] + con_t[9]) / 10;
	seq_(seq_t);
	con_(con_t);
	fout << "10          " << std::fixed << std::setprecision(4) << seq_t[0] << "  " << seq_t[9] << "  " << std::setprecision(5) << avg_seq << "    " << std::setprecision(4) << con_t[0] << "  " << con_t[9] << "  " << std::setprecision(5) << avg_con << std::endl;
	con_t.clear();

	i = 0;
	while (i < 10) {
		std::vector<int> myvec = vec_3;
		begin = std::chrono::system_clock::now();
		all_sort[0](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		seq_t.push_back(total_ / 1000000000);
		myvec = vec_3;
		begin = std::chrono::system_clock::now();
		all_sort[3](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		con_t.push_back(total_ / 1000000000);
		i++;
	}
	avg_seq = (seq_t[0] + seq_t[1] + seq_t[2] + seq_t[3] + seq_t[4] + seq_t[5] + seq_t[6] + seq_t[7] + seq_t[8] + seq_t[9]) / 10;
	avg_con = (con_t[0] + con_t[1] + con_t[2] + con_t[3] + con_t[4] + con_t[5] + con_t[6] + con_t[7] + con_t[8] + con_t[9]) / 10;
	seq_(seq_t);
	con_(con_t);
	fout << "100         " << std::fixed << std::setprecision(4) << seq_t[0] << "  " << seq_t[9] << "  " << std::setprecision(5) << avg_seq << "    " << std::setprecision(4) << con_t[0] << "  " << con_t[9] << "  " << std::setprecision(5) << avg_con << std::endl;
	seq_t.clear();
	con_t.clear();

	i = 0;
	while (i < 10) {
		std::vector<int> myvec = vec_4;
		begin = std::chrono::system_clock::now();
		all_sort[0](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		seq_t.push_back(total_ / 1000000000);
		myvec = vec_4;
		begin = std::chrono::system_clock::now();
		all_sort[4](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		con_t.push_back(total_ / 1000000000);
		i++;
	}
	avg_seq = (seq_t[0] + seq_t[1] + seq_t[2] + seq_t[3] + seq_t[4] + seq_t[5] + seq_t[6] + seq_t[7] + seq_t[8] + seq_t[9]) / 10;
	avg_con = (con_t[0] + con_t[1] + con_t[2] + con_t[3] + con_t[4] + con_t[5] + con_t[6] + con_t[7] + con_t[8] + con_t[9]) / 10;
	seq_(seq_t);
	con_(con_t);
	fout << "1000        " << std::fixed << std::setprecision(4) << seq_t[0] << "  " << seq_t[9] << "  " << std::setprecision(5) << avg_seq << "    " << std::setprecision(4) << con_t[0] << "  " << con_t[9] << "  " << std::setprecision(5) << avg_con << std::endl;
	seq_t.clear();
	con_t.clear();

	i = 0;
	while (i < 10) {
		std::vector<int> myvec = vec_5;
		begin = std::chrono::system_clock::now();
		all_sort[0](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		seq_t.push_back(total_ / 1000000000);
		myvec = vec_5;
		begin = std::chrono::system_clock::now();
		all_sort[5](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		con_t.push_back(total_ / 1000000000);
		i++;
	}
	avg_seq = (seq_t[0] + seq_t[1] + seq_t[2] + seq_t[3] + seq_t[4] + seq_t[5] + seq_t[6] + seq_t[7] + seq_t[8] + seq_t[9]) / 10;
	avg_con = (con_t[0] + con_t[1] + con_t[2] + con_t[3] + con_t[4] + con_t[5] + con_t[6] + con_t[7] + con_t[8] + con_t[9]) / 10;
	seq_(seq_t);
	con_(con_t);
	fout << "10000       " << std::fixed << std::setprecision(4) << seq_t[0] << "  " << seq_t[9] << "  " << std::setprecision(5) << avg_seq << "    " << std::setprecision(4) << con_t[0] << "  " << con_t[9] << "  " << std::setprecision(5) << avg_con << std::endl;
	seq_t.clear();
	con_t.clear();

	i = 0;
	while (i < 10) {
		std::vector<int> myvec = vec_6;
		begin = std::chrono::system_clock::now();
		all_sort[0](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		seq_t.push_back(total_ / 1000000000);
		myvec = vec_6;
		begin = std::chrono::system_clock::now();
		all_sort[6](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		con_t.push_back(total_ / 1000000000);
		i++;
	}
	avg_seq = (seq_t[0] + seq_t[1] + seq_t[2] + seq_t[3] + seq_t[4] + seq_t[5] + seq_t[6] + seq_t[7] + seq_t[8] + seq_t[9]) / 10;
	avg_con = (con_t[0] + con_t[1] + con_t[2] + con_t[3] + con_t[4] + con_t[5] + con_t[6] + con_t[7] + con_t[8] + con_t[9]) / 10;
	seq_(seq_t);
	con_(con_t);
	fout << "100000      " << std::fixed << std::setprecision(4) << seq_t[0] << "  " << seq_t[9] << "  " << std::setprecision(5) << avg_seq << "    " << std::setprecision(4) << con_t[0] << "  " << con_t[9] << "  " << std::setprecision(5) << avg_con << std::endl;
	seq_t.clear();
	con_t.clear();

	i = 0;
	while (i < 10) {
		std::vector<int> myvec = vec_7;
		begin = std::chrono::system_clock::now();
		all_sort[0](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		seq_t.push_back(total_ / 1000000000);
		myvec = vec_7;
		begin = std::chrono::system_clock::now();
		all_sort[7](myvec);
		end = std::chrono::system_clock::now();
		total_ = (double)(end - begin).count();
		con_t.push_back(total_ / 1000000000);
		i++;
	}
	avg_seq = (seq_t[0] + seq_t[1] + seq_t[2] + seq_t[3] + seq_t[4] + seq_t[5] + seq_t[6] + seq_t[7] + seq_t[8] + seq_t[9]) / 10;
	avg_con = (con_t[0] + con_t[1] + con_t[2] + con_t[3] + con_t[4] + con_t[5] + con_t[6] + con_t[7] + con_t[8] + con_t[9]) / 10;
	seq_(seq_t);
	con_(con_t);
	fout << "1000000     " << std::fixed << std::setprecision(4) << seq_t[0] << "  " << seq_t[9] << "  " << std::setprecision(5) << avg_seq << "    " << std::setprecision(4) << con_t[0] << "  " << con_t[9] << "  " << std::setprecision(5) << avg_con << std::endl;
	seq_t.clear();
	con_t.clear();
	fout.close();
	all_sort.clear();
	return EXIT_SUCCESS;
}