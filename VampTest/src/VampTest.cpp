#define VAMP_TEST_ENTRY
#include "VampTest.h"


VAMP_TEST(failures , equal)
{
	VAMP_TEST_EQUAL(0, 1);
}

VAMP_TEST(failures, not_equal)
{
	VAMP_TEST_NOTEQUAL(1, 1);
}

VAMP_TEST(failures, tru)
{
	VAMP_TEST_TRUE(0);
}

VAMP_TEST(failures, fals)
{
	VAMP_TEST_FALSE(1);
}



VAMP_TEST(successes, equal)
{
	VAMP_TEST_EQUAL(1, 1);
}

VAMP_TEST(successes, not_equal)
{
	VAMP_TEST_NOTEQUAL(1, 0);
}

VAMP_TEST(successes, tru)
{
	VAMP_TEST_TRUE(1);
}

VAMP_TEST(successes, fals)
{
	VAMP_TEST_FALSE(0);
}