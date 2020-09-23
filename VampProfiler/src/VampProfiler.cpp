#include "VampProfiler.h"
#include <iostream>
#include <fstream>

int main()
{
	nlohmann::json j = 
	{
		{"name", "nikos"},
		{"last", "bampaliaris"},
		{"age", 20},
		{"time", 13.5120},

		{"errors", 
			{
				{"20", "error 20"},
				{"30", "error 30"},
			}
		}
	};

	
	std::ofstream file_write("test.json");

	if (file_write.is_open())
	{
		file_write << j << std::endl;

		file_write.close();
	}

	else
	{
		std::cout << "File_write failed to open!!!" << std::endl;
	}




	std::ifstream file_read("test.json");
	nlohmann::json j_in;;

	if (file_read.is_open())
	{
		file_read >> j_in;

		file_read.close();

		std::cout << j_in["time"] << std::endl;
	}

	else
	{
		std::cout << "File_read failed to open!!!" << std::endl;
	}

	std::cin.get();
	return 0;
}