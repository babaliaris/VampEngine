#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <stdio.h>


#ifdef VAMP_WINDOWS

	#include <Windows.h>

	#define VAMP_COLOR_DEFAULT 7
	#define VAMP_COLOR_INFO 10
	#define VAMP_COLOR_ERROR 4
	#define VAMP_COLOR_WARN 6
	#define VAMP_COLOR_TRACE 15
	#define VAMP_COLOR_BLUE 9
	#define VAMP_COLOR_PINK 12
	#define VAMP_COLOR_CYAN 11

	#define __VAMP_PRINT_LOG__(color, formater, ...)\
	{\
		auto start	= std::chrono::system_clock::now();\
		auto end = std::chrono::system_clock::now();\
		\
		std::chrono::duration<double> elapsed_seconds = end - start;\
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);\
		\
		std::string date_now = std::string(std::ctime(&end_time));\
		date_now			 = date_now.substr(0, date_now.length() - 6);\
		\
		HANDLE  hConsole;\
		\
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
		\
		SetConsoleTextAttribute(hConsole, color);\
		\
		std::string format = "[%s]: " + std::string(formater) + "\n";\
		printf(format.c_str(), date_now.c_str(), __VA_ARGS__);\
		\
		SetConsoleTextAttribute(hConsole, VAMP_COLOR_DEFAULT);\
		\
	}


	#define __VAMP_PRINT__(color, ...)\
	{\
		HANDLE  hConsole;\
		\
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
		\
		SetConsoleTextAttribute(hConsole, color);\
		\
		printf( __VA_ARGS__);\
		\
		SetConsoleTextAttribute(hConsole, VAMP_COLOR_DEFAULT);\
		\
	}


#else
	#error VampLogger Supports only Windows For Now!

#endif



#ifdef VAMP_DEBUG
	#define VAMP_INFO(formatter, ...)	__VAMP_PRINT_LOG__(VAMP_COLOR_INFO,		formatter, __VA_ARGS__)
	#define VAMP_ERROR(formatter, ...)	__VAMP_PRINT_LOG__(VAMP_COLOR_ERROR,	formatter, __VA_ARGS__)
	#define VAMP_WARN(formatter, ...)	__VAMP_PRINT_LOG__(VAMP_COLOR_WARN,		formatter, __VA_ARGS__)
	#define VAMP_TRACE(formatter, ...)	__VAMP_PRINT_LOG__(VAMP_COLOR_TRACE,	formatter, __VA_ARGS__)

	#define VAMP_PRINT(...)			__VAMP_PRINT__(VAMP_COLOR_TRACE, __VA_ARGS__)
	#define VAMP_PRINT_GREEN(...)	__VAMP_PRINT__(VAMP_COLOR_INFO, __VA_ARGS__)
	#define VAMP_PRINT_RED(...)		__VAMP_PRINT__(VAMP_COLOR_ERROR, __VA_ARGS__)
	#define VAMP_PRINT_YELLOW(...)	__VAMP_PRINT__(VAMP_COLOR_WARN, __VA_ARGS__)
	#define VAMP_PRINT_BLUE(...)	__VAMP_PRINT__(VAMP_COLOR_BLUE, __VA_ARGS__)
	#define VAMP_PRINT_PINK(...)	__VAMP_PRINT__(VAMP_COLOR_PINK, __VA_ARGS__)
	#define VAMP_PRINT_CYAN(...)	__VAMP_PRINT__(VAMP_COLOR_CYAN, __VA_ARGS__)

#else
	#define VAMP_INFO(formatter, ...)
	#define VAMP_ERROR(formatter, ...)
	#define VAMP_WARN(formatter, ...)
	#define VAMP_TRACE(formatter, ...)

	#define VAMP_PRINT(...)	
	#define VAMP_PRINT_GREEN(...)
	#define VAMP_PRINT_RED(...)
	#define VAMP_PRINT_YELLOW(...)

#endif