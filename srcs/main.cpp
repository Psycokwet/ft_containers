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
#include <type_traits.hpp>
#include <pair.hpp>
#include <map.hpp>
#include <stack.hpp>
#include <vector.hpp>
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

template <typename T>
class MutantStack : public ft::stack<T>
{
public:
	// MutantStack() {}
	MutantStack(const MutantStack<T> &src) { *this = src; }
	MutantStack<T> &operator=(const MutantStack<T> &rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	void print()
	{
		std::cout << this->c << std::endl;
	}
	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

int main(int argc, char **argv)
{

	/*
	** --------------------------------- MAP CONSTRUCTORS TESTS --------------------------
	*/
	ft::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	ft::map<char, int> second(first.begin(), first.end());

	ft::map<char, int> third(second);

	ft::map<char, int, classcomp> fourth; // class as Compare

	bool (*fn_pt)(char, char) = fncomp;
	ft::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare

	// ft::map<int, int> map_int;
	ft::map<std::string, int> map_str;
	// ft::map<std::string, int> map_str_int;
	ft::map<std::string, std::string> map_str_str;

	map_str["1"] = 2;
	map_str["1"] = 7;
	map_str["0"] = 5;
	map_str["2"] = 25;
	map_str["3"] = 42;
	map_str["4"] = 2;
	map_str["5"] = 6;
	map_str["6"] = 66;
	map_str["7"] = 166;
	map_str["8"] = 1166;
	map_str["9"] = 11166;
	ft::map<std::string, int>::const_iterator cit;
	ft::map<std::string, int> map_str_copy(map_str);
	std::cout << "COPY MAP"
			  << "\n";
	for (cit = map_str_copy.begin(); cit != map_str_copy.end(); cit++)
	{
		std::cout << "key[" << cit->first << "] : "
				  << "val[" << cit->second << "] : " << std::endl;
	}
	ft::map<std::string, int>::iterator it;
	it = map_str_copy.begin();
	it++;
	it++;
	ft::map<std::string, int> map_str_copy_partial(it, map_str_copy.end());
	std::cout << "COPY partial"
			  << "\n";
	for (it = map_str_copy_partial.begin(); it != map_str_copy_partial.end(); it++)
	{
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
	}

	/*
	** --------------------------------- MAP ACCESS TESTS --------------------------
	*/
	try
	{
		map_str.at("42");
		/* code */
	}
	catch (const std::exception &e)
	{
		std::cerr << "exception : " << e.what() << '\n';
	}
	std::cout <<"1:val[" << map_str["1"]<< "] : " << std::endl;
	std::cout << "5:val[" << map_str["5"]<< "] : " << std::endl;
	std::cout << "10:val[" << map_str["10"] << "] : " << std::endl;

	/*
	** --------------------------------- MAP ITERATORS TESTS --------------------------
	*/
	std::cout << "first\n";
	it = map_str.begin();
	while (true)
	{
		if (it == map_str.end())
			break;
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
		it++;
	}
	std::cout << "second\n";
	it--;
	while (true)
	{
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
		if (it == map_str.begin())
			break;
		it--;
	}

	std::cout << "third\n";
	while (true)
	{
		if (it == map_str.end())
			break;
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
		it++;
	}
	it--;
	std::cout << "last\n";
	while (true)
	{
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
		if (it == map_str.begin())
			break;
		it--;
	}

	map_str.erase("5");
	std::cout << "Erase key 5"
			  << "\n";
	for (it = map_str.begin(); it != map_str.end(); it++)
	{
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
	}

	map_str.erase(map_str.begin());
	std::cout << "Erase begin"
			  << "\n";
	for (it = map_str.begin(); it != map_str.end(); it++)
	{
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
	}

	std::cout << "Erased all start-------"
			  << "\n";
	map_str.erase(map_str.begin(), map_str.end());
	std::cout << "-------Erased all done"
			  << "\n";
	for (it = map_str.begin(); it != map_str.end(); it++)
	{
		std::cout << "key[" << it->first << "] : "
				  << "val[" << it->second << "] : " << std::endl;
	}

	return 0;
	ft::vector<std::string> vectorTeststr;
	std::cout << "pushback str :"
			  << "\n";
	vectorTeststr.push_back("cc");
	std::cout << "end pushback str :"
			  << "\n";
	std::cout << "test str :" << vectorTeststr.size() << "\n";
	std::cout << "test str :" << vectorTeststr[0] << "\n";
	vectorTeststr[0] += "pwett";
	std::cout << "test str :" << vectorTeststr[0] << "\n";
	std::cout << "all good \n";
	ft::vector<ft::pair<int, int> // bug indent
	> vectorTest;
	vectorTest.push_back(ft::make_pair(1337, 42));
	std::cout << vectorTest.size() << "\n";
	std::cout << vectorTest[0].first << "\n"
			  << ":" << vectorTest[0].second << "\n";
	// a tester plus tard quand vector fini
	//  ft::vector<int> vectorTest;
	//  ft::stack<int, ft::vector<int> > test(vectorTest);
	//  test.print();
	//  std::cout << &vectorTest << std::endl;

	// #ifdef STL // c++ 11 so untestable for the real one
	// 	std::cout << std::boolalpha;
	// 	std::cout << ft::is_integral<float>::value << ":" << true << std::endl;
	// 	std::cout << ft::is_integral<int>::value << ":" << true << std::endl;
	// 	std::cout << ft::is_integral<bool>::value << ":" << true << std::endl;
	// #endif
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::vector<int> vector_int_filled(42, 42);
	(void)vector_int_filled;
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
	vector_int[0] = 56;
	vector_int_filled[0] = 56;
	std::cout << "val[0] : " << vector_int[0] << std::endl;
	std::cout << "val[0] : " << vector_int_filled[0] << std::endl;

	int i = 0;
	std::cout << "full content int" << std::endl;
	for (ft::vector<int>::iterator it = vector_int.begin(); it != vector_int.end(); it++)
	{
		std::cout << "val[" << i << "] : " << vector_int[i] << std::endl;
		std::cout << "val[" << i << "] : " << *it << std::endl;
		i++;
	}

	i = 0;
	std::cout << "full content int" << std::endl;
	for (ft::vector<int>::const_iterator it = vector_int.begin(); it != vector_int.end(); it++)
	{
		std::cout << "val[" << i << "] : " << vector_int[i] << std::endl;
		std::cout << "val[" << i << "] : " << *it << std::endl;
		i++;
	}

	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> // bug indent
	> stack_deq_buffer;
	// for (ft::vector<int>::iterator it = vector_int.begin(); it != vector_int.end(); it++)
	// 	std::cout << "val[it] : " << *it << std::endl;
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
	// 	map_str.insert(ft::make_pair(rand(), rand()));
	// }

	// int sum = 0;
	// for (int i = 0; i < 10000; i++)
	// {
	// 	int access = rand();
	// 	sum += map_str[access];
	// }
	// std::cout << "should be constant with the same seed: " << sum << std::endl;

	// {
	// 	ft::map<int, int> copy = map_str;
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