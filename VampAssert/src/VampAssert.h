#pragma once
#include <VampLogger.h>

#if (defined VAMP_ENABLE_ASSERTS && defined VAMP_DEBUG)

	//Define Breakpoint Macro.
	#ifdef _MSC_BUILD
		#define VAMP_BREAKPOINT __debugbreak()
	#else
		#define VAMP_BREAKPOINT
	#endif


	//Define Vamp Assertion.
	#define VAMP_ASSERT(cond, ...)\
	{\
		if ( !(cond) )\
		{\
			VAMP_PRINT_RED("Assertion Failed:\n");\
			VAMP_PRINT_PINK("\tAt File  : %s\n", __FILE__);\
			VAMP_PRINT_PINK("\tAt Line  : %d\n", __LINE__);\
			VAMP_PRINT_PINK("\tCondition: %s\n", #cond);\
			VAMP_PRINT_CYAN("\tMessage  : ");\
			VAMP_PRINT_CYAN(__VA_ARGS__);\
			printf("\n\n");\
			VAMP_BREAKPOINT;\
		}\
	}

//Disable Assertions.
#else
	#define VAMP_ASSERT(cond, ...)


#endif