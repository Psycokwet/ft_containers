#include <iostream>
#include <string>
#include <deque>

#ifndef STL // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <type_traits.hpp>
#include <pair.hpp>
// #include <map.hpp>
#include <stack.hpp>
// #include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer

{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template <typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T> &src) { *this = src; }
// 	MutantStack<T> &operator=(const MutantStack<T> &rhs)
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

int main(int argc, char **argv)
{

#ifdef STL // c++ 11 so untestable for the real one
	std::cout << std::boolalpha;
	std::cout << ft::is_integral<float>::value << ":" << true << std::endl;
	std::cout << ft::is_integral<int>::value << ":" << true << std::endl;
	std::cout << ft::is_integral<bool>::value << ":" << true << std::endl;
#endif
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	// ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::vector<int> vector_int_filled(42, 42);
	try
	{
		vector_int.reserve(-1);
		/* code */
	}
	catch (const std::exception &e)
	{
		std::cerr << "exception : " << e.what() << '\n';
	}

	std::cout << "MAX_SIZE : " << vector_int.max_size() << std::endl;
	std::cout << "MAX_SIZE : " << vector_int_filled.max_size() << std::endl;
	std::cout << "SIZE : " << vector_int.size() << std::endl;
	std::cout << "SIZE : " << vector_int_filled.size() << std::endl;
	std::cout << "CAPACITY : " << vector_int.capacity() << std::endl;
	std::cout << "CAPACITY : " << vector_int_filled.capacity() << std::endl;
	try
	{
		std::cout << "val.at(0) : " << vector_int.at(0) << std::endl;
		/* code */
	}
	catch (const std::exception &e)
	{
		std::cerr << "exception : " << e.what() << '\n';
	}
	std::cout << "val[0] : " << vector_int_filled[0] << std::endl;

	vector_int.resize(32);
	vector_int_filled.resize(32); // ft::stack<int> stack_int;
	std::cout << "MAX_SIZE : " << vector_int.max_size() << std::endl;
	std::cout << "MAX_SIZE : " << vector_int_filled.max_size() << std::endl;
	std::cout << "SIZE : " << vector_int.size() << std::endl;
	std::cout << "SIZE : " << vector_int_filled.size() << std::endl;
	std::cout << "CAPACITY : " << vector_int.capacity() << std::endl;
	std::cout << "CAPACITY : " << vector_int_filled.capacity() << std::endl;
	std::cout << "val[0] : " << vector_int[0] << std::endl;
	std::cout << "val[0] : " << vector_int_filled[0] << std::endl;
	vector_int.clear();
	vector_int_filled.clear(); // ft::stack<int> stack_int;
	std::cout << "MAX_SIZE : " << vector_int.max_size() << std::endl;
	std::cout << "MAX_SIZE : " << vector_int_filled.max_size() << std::endl;
	std::cout << "SIZE : " << vector_int.size() << std::endl;
	std::cout << "SIZE : " << vector_int_filled.size() << std::endl;
	std::cout << "CAPACITY : " << vector_int.capacity() << std::endl;
	std::cout << "CAPACITY : " << vector_int_filled.capacity() << std::endl;
	vector_int.assign(50, 99);
	vector_int_filled.assign(22, 64); // ft::stack<int> stack_int;
	std::cout << "MAX_SIZE : " << vector_int.max_size() << std::endl;
	std::cout << "MAX_SIZE : " << vector_int_filled.max_size() << std::endl;
	std::cout << "SIZE : " << vector_int.size() << std::endl;
	std::cout << "SIZE : " << vector_int_filled.size() << std::endl;
	std::cout << "CAPACITY : " << vector_int.capacity() << std::endl;
	std::cout << "CAPACITY : " << vector_int_filled.capacity() << std::endl;
	std::cout << "val[0] : " << vector_int[0] << std::endl;
	std::cout << "val[0] : " << vector_int_filled[0] << std::endl;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	// for (ft::vector<int>::iterator it = vector_int.begin(); it != vector_int.end(); it++)
	// 	std::cout << "val[it] : " << *it << std::endl;
	// ft::map<int, int> map_int;

	// for (int i = 0; i < COUNT; i++)
	// {
	// 	vector_buffer.push_back(Buffer());
	// }

	// for (int i = 0; i < COUNT; i++)
	// {
	// 	const int idx = rand() % COUNT;
	// 	vector_buffer[idx].idx = 5;
	// }
	// ft::vector<Buffer>().swap(vector_buffer);

	// try
	// {
	// 	for (int i = 0; i < COUNT; i++)
	// 	{
	// 		const int idx = rand() % COUNT;
	// 		vector_buffer.at(idx);
	// 		std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
	// 	}
	// }
	// catch (const std::exception &e)
	// {
	// 	// NORMAL ! :P
	// }

	// for (int i = 0; i < COUNT; ++i)
	// {
	// 	map_int.insert(ft::make_pair(rand(), rand()));
	// }

	// int sum = 0;
	// for (int i = 0; i < 10000; i++)
	// {
	// 	int access = rand();
	// 	sum += map_int[access];
	// }
	// std::cout << "should be constant with the same seed: " << sum << std::endl;

	// {
	// 	ft::map<int, int> copy = map_int;
	// }
	// MutantStack<char> iterable_stack;
	// for (char letter = 'a'; letter <= 'z'; letter++)
	// 	iterable_stack.push(letter);
	// for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	// {
	// 	std::cout << *it;
	// }
	// std::cout << std::endl;
	return (0);
}