#ifndef PRINT_HPP
#define PRINT_HPP
#include <cstring>
#include <string.h>
#include <ctype.h>
#include <sstream>

#define SSTR(x) static_cast<std::ostringstream &>(            \
					(std ::ostringstream() << std::dec << x)) \
					.str()

#endif