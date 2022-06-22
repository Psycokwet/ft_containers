#ifndef LOGGER_HPP
# define LOGGER_HPP
# include <cstring>
# include <string.h>
# include <ctype.h>
# include <algorithm>
# include <fstream>
# include <iostream>
# include <sstream>
# include <ios>
# include <string>
# include <typeinfo>
# define ONE_FILE_LOGS "one_file_logs.logs"

void gen_file_logger(std::string file_path, std::string log);
void raw_logger(std::string file_path, std::string log);

template <typename T> 
std::string streamFunctionToString(std::ostream &(T::*print)(std::ostream &) const, const T *obj)
{
	std::stringstream ss;
	(obj->*print)(ss);
	return ss.str();
}

void one_file_logger_int(std::string src, std::string log);
template <typename T> 
void one_file_logger(T src, std::string log)
{
	one_file_logger_int(typeid(src).name(), log);
}
//Must avoid usage, because it imply we are making a lot of small call, upper functions are preferred for perfs issues.
void one_file_logger_raw(std::string log);
#endif