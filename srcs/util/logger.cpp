#include "logger.hpp"

void gen_file_logger(std::string file_path, std::string log)
{
	std::ofstream	ofs(file_path.c_str());
	if (!ofs.is_open())
	{
		std::cerr << "Logging impossible" << std::endl;
		return;
	}
	ofs << log ;
	ofs.close();
}

void raw_logger(std::string file_path, std::string log)
{
	std::ofstream	ofs(file_path.c_str(), std::ios_base::app);
	if (!ofs.is_open())
	{
		std::cerr << "Logging impossible" << std::endl;
		return;
	}
	ofs << log ;
	ofs.close();
}

void one_file_logger_int(std::string src, std::string log)
{
	if(DEBUG)
		std::cout << log;
	std::ofstream	ofs((std::string(LOGS_FOLDER) + std::string("/") + ONE_FILE_LOGS).c_str(), std::ios_base::app);
	if (!ofs.is_open())
	{
		std::cerr << "Logging impossible" << std::endl;
		return;
	}
	ofs << std::endl << "#----------------------------- NEW LOG FROM " << src << " ----------------------#\n"<< log << std::endl;
	ofs.close();
}

void one_file_logger_raw(std::string log)
{
	if(DEBUG)
		std::cout << log;
	std::ofstream	ofs((std::string(LOGS_FOLDER) + std::string("/") + ONE_FILE_LOGS).c_str(), std::ios_base::app);
	if (!ofs.is_open())
	{
		std::cerr << "Logging impossible" << std::endl;
		return;
	}
	ofs << log;
	ofs.close();
}
