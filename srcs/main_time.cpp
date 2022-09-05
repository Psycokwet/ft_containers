#include <iostream>
#include <string>
#include <deque>

#ifndef STL // CREATE A REAL STL EXAMPLE
#include <set>
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
#include <stack.hpp>
#include <vector.hpp>
#endif

#include <stdlib.h>
#include <ctime>

int main()
{

	/*
	** --------------------------------- MAP TIME TESTS --------------------------
	*/
	{
		std::cout << "MAP TEST: " << "\n";
		clock_t start, end;
		start = clock();
		ft::map<int, int> map_test;
		for (int i = 0; i < 1000; i++)
			map_test[i] = i;

		end = clock();
		std::cout << "Process took: " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << "\n";
		start = clock();
		for (int i = 0; i < 1000; i++)
			map_test[i] = i;

		end = clock();
		std::cout << "Process took: " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << "\n";
		start = clock();
		for (ft::map<int, int>::iterator it = map_test.begin(); it != map_test.end(); )
			map_test.erase(it++);

		end = clock();
		std::cout << "Process took: " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << "\n";
		start = clock();
	}
	/*
	** --------------------------------- VECTOR TIME TESTS --------------------------
	*/
	{
		std::cout << "VECTOR TEST: " << "\n";
		clock_t start, end;
		start = clock();
		ft::vector<int> vector_test;
		for (int i = 0; i < 1000; i++)
			vector_test.push_back(i);

		end = clock();
		std::cout << "Process took: " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << "\n";
		start = clock();
		for (int i = 0; i < 1000; i++)
			vector_test[i] = i;

		end = clock();
		std::cout << "Process took: " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << "\n";
		start = clock();
		for (ft::vector<int>::iterator it = vector_test.begin(); it != vector_test.end(); )
			vector_test.erase(it++);

		end = clock();
		std::cout << "Process took: " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << "\n";
		start = clock();
	}
	return (0);
}