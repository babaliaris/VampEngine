#pragma once

//Make sure VAMP_DEBUG and VAMP_ENABLE_ASSERTS are defined.
//This testing framework is intented to work in debug mode even
//when you build it for release or distribution!!!
#define VAMP_DEBUG
#define VAMP_ENABLE_ASSERTS

#include <VampLogger.h>
#include <iostream>
#include <vector>
#include <functional>

/*
* MULTIPLE FILES ARE NOT SUPPORTED FOR NOW!!!!!!
* 
* USAGE			: Define VAMP_TEST_ENTRY in ONLY ONE cpp file!!!
* USE THE MACRO	: VAMP_TEST(case_name, test_name) followed by a function body {} to define your test logic.
* USE ASSERTS	: VAMP_TEST_EQUAL, VAMP_TEST_NOTEQUAL inside your test logic.
*/

namespace VampEngine
{

	//Global Vector Of Tests.
	struct Test;

	std::vector<Test*> G__VampTestCases__;


	//Test Structure//
	struct Test
	{
		std::string CaseName;
		std::string TestName;
		bool		Passed;
		void		(*func)(Test *test);

		//Constructor.
		Test(const char *case_name, const char* test_name, void (*func)(Test* test))
			: CaseName(case_name), TestName(test_name), Passed(true), func(func)
		{
			G__VampTestCases__.push_back(this);
		}

	};
}


#define VAMP_TEST(case_name, test_name)\
void case_name ## _ ## test_name(VampEngine::Test *test);\
VampEngine::Test* GLOBAL_ ## case_name ## _ ## test_name = new VampEngine::Test(#case_name, #test_name, case_name ## _ ## test_name);\
void case_name ## _ ## test_name(VampEngine::Test * self)


#define VAMP_TEST_EQUAL(expected, real)\
{\
	if ( (expected) != (real) )\
	{\
		self->Passed = false;\
		VAMP_PRINT_RED("%20s", "[FAILED] ====================> ");\
		VAMP_PRINT_BLUE("%s", self->CaseName.c_str());\
		VAMP_PRINT(".")\
		VAMP_PRINT_CYAN("%s\n", self->TestName.c_str());\
		VAMP_PRINT_YELLOW("\tFile\t  : %s\n\tLine\t  : %d\n\tExpression: (%s) == (%s)\n\n\n\n", __FILE__, __LINE__, #expected, #real);\
	}\
}


#define VAMP_TEST_NOTEQUAL(expected, real)\
{\
	if ( (expected) == (real) )\
	{\
		self->Passed = false;\
		VAMP_PRINT_RED("%20s", "[FAILED] ====================> ");\
		VAMP_PRINT_BLUE("%s", self->CaseName.c_str());\
		VAMP_PRINT(".")\
		VAMP_PRINT_CYAN("%s\n", self->TestName.c_str());\
		VAMP_PRINT_YELLOW("\tFile\t  : %s\n\tLine\t  : %d\n\tExpression: (%s) != (%s)\n\n\n\n", __FILE__, __LINE__, #expected, #real);\
	}\
}


#define VAMP_TEST_TRUE(expected)\
{\
	if ( !(expected) )\
	{\
		self->Passed = false;\
		VAMP_PRINT_RED("%20s", "[FAILED] ====================> ");\
		VAMP_PRINT_BLUE("%s", self->CaseName.c_str());\
		VAMP_PRINT(".")\
		VAMP_PRINT_CYAN("%s\n", self->TestName.c_str());\
		VAMP_PRINT_YELLOW("\tFile\t  : %s\n\tLine\t  : %d\n\tExpression: (%s) == true\n\n\n\n", __FILE__, __LINE__, #expected);\
	}\
}


#define VAMP_TEST_FALSE(expected)\
{\
	if ( (expected) )\
	{\
		self->Passed = false;\
		VAMP_PRINT_RED("%20s", "[FAILED] ====================> ");\
		VAMP_PRINT_BLUE("%s", self->CaseName.c_str());\
		VAMP_PRINT(".")\
		VAMP_PRINT_CYAN("%s\n", self->TestName.c_str());\
		VAMP_PRINT_YELLOW("\tFile\t  : %s\n\tLine\t  : %d\n\tExpression: (%s) != true\n\n\n\n", __FILE__, __LINE__, #expected);\
	}\
}



#ifdef VAMP_TEST_ENTRY

/*
* Syntax: VampTest.exe (Without Parameters) => Run ALL TESTS.
* Syntax: VampTest.exe --list				=> List All Tests.
* Syntax: VampTest.exe --list case_name		=> List All Tests of that specific case.
* Syntax: VampTest.exe case_name			=> Run All Tests of that specific case.
* Syntax: VampTest.exe case_name.test_name	=> Run a specific test.
* Syndax: 
*/
int main(int argc, char** argv)
{

	//Kepp track of failed Tests.
	int failed = 0;
	int runned = 0;


	//Run All The Tests.
	if (argc <= 1)
	{
		for (VampEngine::Test* test : VampEngine::G__VampTestCases__)
		{
			test->func(test);
			test->Passed ? 0 : failed++;
			runned++;

			//Print Success Message.
			if (test->Passed)
			{
				VAMP_PRINT_GREEN("%20s", "[PASSED] ====================> ");
				VAMP_PRINT_BLUE("%s", test->CaseName.c_str());
				VAMP_PRINT(".");
				VAMP_PRINT_CYAN("%s\n\n\n\n", test->TestName.c_str());
			}
		}
	}


	//An extra argument was specified.
	else
	{

		//Get the first parameter of argv.
		std::string input = argv[1];

		//List All Tests.
		if (input == "--list" && argc == 2)
		{
			bool found_at_least_one = false;

			//Go through all test.
			for (VampEngine::Test* test : VampEngine::G__VampTestCases__)
			{
				VAMP_PRINT_BLUE("%s", test->CaseName.c_str());
				VAMP_PRINT(".");
				VAMP_PRINT_CYAN("%s\n", test->TestName.c_str());
				found_at_least_one = true;
			}

			//No Tests Found.
			if (!found_at_least_one)
			{
				VAMP_PRINT_RED("VampTest: No Tests Found!\n");
			}

			//Return and EXIT.
			return 0;
		}


		//List All Tests.
		if (input == "--list" && argc == 3)
		{
			bool found_at_least_one = false;

			//Get the case name.
			std::string case_name = argv[2];

			//Go through all test.
			for (VampEngine::Test* test : VampEngine::G__VampTestCases__)
			{
				if (test->CaseName == case_name)
				{
					VAMP_PRINT_BLUE("%s", test->CaseName.c_str());
					VAMP_PRINT(".");
					VAMP_PRINT_CYAN("%s\n", test->TestName.c_str());
					found_at_least_one = true;
				}
			}

			//No Tests Found.
			if (!found_at_least_one)
				VAMP_PRINT_RED("VampTest: No Tests Found!\n");

			//Return and EXIT.
			return 0;
		}

		//If it does not contain a . => then it is a case.
		if (input.find(".") == std::string::npos)
		{
			//Go through all test.
			for (VampEngine::Test* test : VampEngine::G__VampTestCases__)
			{

				//Run only tests of this case (arvg[1] = input)
				if (test->CaseName == input)
				{
					test->func(test);
					test->Passed ? 0 : failed++;
					runned++;

					//Print Success Message.
					if (test->Passed)
					{
						VAMP_PRINT_GREEN("%20s", "[PASSED] ====================> ");
						VAMP_PRINT_BLUE("%s", test->CaseName.c_str());
						VAMP_PRINT(".");
						VAMP_PRINT_CYAN("%s\n\n\n\n", test->TestName.c_str());
					}
				}
			}
		}

		//Run a specific Test.
		else
		{

			std::string case_name = input.substr(0, input.find_last_of("."));
			std::string test_name = input.substr(input.find_last_of(".") + 1, input.length());

			//Go through all test.
			for (VampEngine::Test* test : VampEngine::G__VampTestCases__)
			{

				//Run only tests of this case (arvg[1] = input)
				if (test->CaseName == case_name && test->TestName == test_name)
				{
					test->func(test);
					test->Passed ? 0 : failed++;
					runned++;

					//Print Success Message.
					if (test->Passed)
					{
						VAMP_PRINT_GREEN("%20s", "[PASSED] ====================> ");
						VAMP_PRINT_BLUE("%s", test->CaseName.c_str());
						VAMP_PRINT(".");
						VAMP_PRINT_CYAN("%s\n\n\n\n", test->TestName.c_str());
					}

					break;
				}
			}
		}
	}

	printf("\n\n");
	VAMP_PRINT("TOTAL : %d\n", runned);
	VAMP_PRINT_RED("FAILED: %d\n", failed);
	VAMP_PRINT_GREEN("PASSED: %d\n", runned - failed);

	//Delete all the tests.
	for (VampEngine::Test* test : VampEngine::G__VampTestCases__) delete test;

	//Print exit message and exit the programm.
	printf("\n\nPress ENTER to exit...");
	std::cin.get();
	return 0;
}
#endif